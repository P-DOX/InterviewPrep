#include "iostream"
#include "map"
using namespace std;

class Node {
    public:
        int key;
        int val;
        int freq;
        Node* next;
        Node* prev;

        Node(int key, int val){
            this->key = key;
            this->val = val;
            this->freq = 1;
            this->next = NULL;
            this->prev = NULL;
        }
};

class LFU {
    public:
        int capacity;
        map<int, pair<Node*, Node*>> flist;
        map<int, Node*> cache;

        LFU(int cap){
            this->capacity = cap;
        }

        void insertToTop(Node* node, pair<Node*, Node*>lst){
            Node* head = lst.first;
            Node* tail = lst.second;

            node->next = head->next;
            head->next->prev = node;
            node->prev = head;
            head->next = node;
        }

        void initialiseMapPos(int pos){
            Node* head = new Node(-1, -1);
            Node* tail = new Node(-1, -1);
            head->next = tail;
            tail->prev = head;
            flist[pos] = {head, tail};
        }

        void deleteLFUNode(int f){
            Node* head = flist[f].first;
            Node* tail = flist[f].second;
            Node* node = tail->prev;
            if(node->key == -1) // head
                return ;
            
            removeNode(node);
            cache.erase(node->key);
        }

        void insertInList(int freq, Node* node){
            if (flist.find(freq) == flist.end())
                initialiseMapPos(freq);

            insertToTop(node, flist[freq]);
           
        }

        void insert(int key, int val){
            if(cache.size() == capacity){
                int minFreq = flist.begin()->first;
                deleteLFUNode(minFreq);
            }

            Node* node = new Node(key, val);
            insertInList(1, node);
            cache[key] = node;
        }

        void removeNode(Node* node){
            Node* pre = node->prev;
            Node* nex = node->next;
            pre->next = nex;
            nex->prev = pre;
        }

        void update(int key, int val){
            if(cache.find(key) == cache.end())
                return ;
            
            Node* node = cache[key];
            node->val = val;
            int freq = node->freq;
            removeNode(node);
            insertInList(freq+1, node);
            node->freq++;
        }

        int get(int key) {
            if(cache.find(key) == cache.end())
                return -1;
            Node* node = cache[key];
            int freq = node->freq;
            removeNode(node);
            insertInList(freq+1, node);
            node->freq++;
            return node->val;
        }

        void printLFU(){
            cout<<"\n====================================================================\n";
            for(auto it = flist.begin(); it!= flist.end(); it++){
                cout<<it->first<<"\n";
                Node* head = it->second.first;
                Node* tail = it->second.second;
                Node* temp = head;
                while(temp != NULL){
                    cout<<"("<<temp->key<<", "<<temp->freq<<") ";
                    temp = temp->next;
                }
                cout<<endl;
            }
        }
};

int main(){
    LFU* lfu = new LFU(3);
    lfu->insert(1, 1);
    lfu->printLFU();
    lfu->insert(2, 2);
    lfu->printLFU();
    cout<<"Get 1 = "<<lfu->get(1)<<endl;
    lfu->printLFU();
    lfu->insert(3, 3);
    lfu->printLFU();
    lfu->insert(4, 4);
    lfu->printLFU();
    lfu->insert(5, 5);
    lfu->printLFU();
    cout<<"Get 4 = "<<lfu->get(4)<<endl;
    lfu->printLFU();
    lfu->insert(6, 6);
    lfu->printLFU();
    cout<<"Get 5 = "<<lfu->get(5)<<endl;
    lfu->printLFU();
}