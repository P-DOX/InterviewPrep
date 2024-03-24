class Node {
    public : 
        int key;
        int value;
        Node* next;
        Node* prev;

        Node(int key, int value){
            this->key = key;
            this->value = value;
        }
};

class LRUCache {
public:
    int size;
    Node* head;
    Node* tail;
    unordered_map<int, Node*>mp;
    
    LRUCache(int capacity) {
        this->head = new Node(-1, -1);
        this->tail = new Node(-1, -1);
        this->size = capacity;   
        this->head->next = this->tail;
        this->tail->prev = this->head; 
    }
    
    void deleteNode(Node* node){
        Node* prevNode = node->prev;
        Node* nextNode = node->next;

        prevNode->next = nextNode;
        nextNode->prev = prevNode;

        delete(node);
    }

    void insertNode(Node* node){
        Node* temp = head->next;
        node->next = temp;
        node->prev = head;
        
        head->next = node;
        temp->prev = node;
    }

    void rearrangeToTop(Node* node){
        Node* prevNode = node->prev;
        Node* nextNode = node->next;
        prevNode->next = nextNode;
        nextNode->prev = prevNode;
        insertNode(node);
    }

    int get(int key) {
        if(mp.find(key) == mp.end())
            return -1;
        Node* node = mp[key];
        rearrangeToTop(node);

        return node->value;
    }
    
    void put(int key, int value) {
        if(mp.find(key) != mp.end()){
            deleteNode(mp[key]);
            mp.erase(key);
        }
        else if(mp.size() == size){
            mp.erase(tail->prev->key);
            deleteNode(tail->prev);
        }

        Node* node = new Node(key, value);
        insertNode(node);
        mp[key] = node;
    }
};