#include "iostream"
#include "string"
#include "vector"
#include "unordered_map"
#include "queue"
#include "set"

using namespace std;

class ContactInfo {
    public :
        string name;
        string phoneNumber;
        int freq;

        ContactInfo(string name, string phoneNumber){
            this->name = name;
            this->phoneNumber = phoneNumber;
            this->freq = 0;
        }
};

class Node {
    public:
        char ch;
        vector<Node*> links;
        vector<ContactInfo*> contacts;
        int numOfContacts;
    
        Node(char ch){
            this->ch = ch;
            this->links.resize(26, NULL);
            this->numOfContacts = 0;
        }
};

class ContactBook {
    public :
        Node* head;
        unordered_map<string, ContactInfo*>phoneList;
        set<pair<int, string>>favourites;
        int favouritesSize;

        ContactBook(int favouritesSize) {
            this->head = new Node('/');
            this->favouritesSize = favouritesSize;
        }

        void insertInTrie(string name, ContactInfo* info){
            Node* curr = head;

            for(char ch : name){
                if(curr->links[ch-'a'] == NULL){
                    curr->links[ch-'a'] = new Node(ch);
                }
                curr = curr->links[ch-'a'];
            }
            curr->contacts.push_back(info);
            curr->numOfContacts += 1;
        }

        vector<ContactInfo*> searchName(string name){
            Node* curr = head;
            
            for(char ch : name){
                if(curr->links[ch-'a'] == NULL)
                    return {};
                curr = curr->links[ch-'a'];
            }
            for(auto it : curr->contacts){
                it->freq += 1;
                updateFavourites(it->freq, it->phoneNumber);
            }
            return curr->contacts;
        }

        string searchNumber(string number){
            ContactInfo* info = phoneList[number];
            info->freq += 1;
            updateFavourites(info->freq, info->phoneNumber);
            return info->name;
        }

        vector<ContactInfo*> getOrderedContacts(){
            vector<ContactInfo*> lst;
            Node* curr = head;
            queue<Node*>q;
            q.push(curr);

            while(q.size()){
                auto top = q.front();   q.pop();

                if(top->numOfContacts){
                    for(auto info : top->contacts)
                        lst.push_back(info);
                }
                
                for(int i=0; i<26; i++){
                    if(top->links[i])
                        q.push(top->links[i]);
                }
            }

            return lst;

        }

        void createContact(string name, string phoneNumber){
            ContactInfo* info = new ContactInfo(name, phoneNumber); 
            phoneList[phoneNumber] = info;

            insertInTrie(name, info);
        }

        void updateFavourites(int freq, string number){
            if(favourites.size() == favouritesSize){
                if(freq <= favourites.begin()->first)
                    return ;
                else 
                    favourites.erase(favourites.begin());
            }

            favourites.insert({freq, number});
        }

        vector<ContactInfo*> getFavourites(){
            vector<ContactInfo*> lst;

            for(auto it : favourites)
                lst.insert(lst.begin(), phoneList[it.second]);
            
            return lst;
        }

};

int main() {
    ContactBook* cb = new ContactBook(5);
    cb->createContact("aman", "3874628374628");
    cb->createContact("aman", "356675775675");
    cb->createContact("gaurav", "43535345");
    cb->createContact("archit", "8968786876");
    cb->createContact("ganesh", "98756456");
    cb->createContact("aman", "839475235");
    cb->createContact("gaurav", "238742742");
    cb->createContact("meetha", "956748646");
    
    vector<ContactInfo*> lst = cb->searchName("aman");
    lst = cb->searchName("gaurav");
    lst = cb->searchName("aman");
    lst = cb->searchName("meetha");
    for(auto it : lst)
        cout<<it->name<<" "<<it->phoneNumber<<" "<<it->freq<<endl;

    
    cout<<"------------------------------------------------------------------\n";
    vector<ContactInfo*> lst1 = cb->getOrderedContacts();
    for(auto it : lst1)
        cout<<it->name<<" "<<it->phoneNumber<<" "<<it->freq<<endl;

    cout<<"------------------------------------------------------------------\n";

    lst = cb->getFavourites();
    for(auto it : lst)
        cout<<it->name<<" "<<it->phoneNumber<<" "<<it->freq<<endl;
        

}