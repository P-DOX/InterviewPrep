#include <iostream>
#include <string>
#include <set>
using namespace std;

class Isubscriber{
    public:
        virtual void notify(string msg) = 0;
};

class User : public Isubscriber {
    private :
        int userId;
    public:
        User(int userId) {
            this->userId = userId;
        }

        void notify(string msg){
            cout<<"USer "<<this->userId<<" has notified with msg : "<<msg<<endl;
        }
};

class Group {
    private:
        set<Isubscriber*> lst;
    public :
        void registerUser(Isubscriber* user){
            lst.insert(user);
        }

        void removeUser(Isubscriber* user){
            lst.erase(user);
        }

        void notify(string msg){
            for(auto user : lst){
                user->notify(msg);
            }
        }

};


int main(){
    Group* grp = new Group();

    User* usr1 = new User(1);
    grp->registerUser(usr1);
    User* usr2 = new User(2);
    grp->registerUser(usr2);
    User* usr3 = new User(3);
    grp->registerUser(usr3);
    User* usr4 = new User(4);
    grp->registerUser(usr4);

    grp->notify("Message notification");

    grp->removeUser(usr1);
    grp->notify("New notification");

}