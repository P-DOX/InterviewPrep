#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <cstdlib>
using namespace std;

class User {
    public:
        int userId;
        string username;
        User(int userId, string userName) {
            this->userId = userId;
            this->username = userName;
        }
};

class Board {
    public:
        int size;
        map<int, int> snakes;
        map<int, int> ladders;

        Board(int size){
            this->size = size;
        }

        void setSnakes(vector<pair<int, int>> snakePos){
            for(auto snake : snakePos)
                snakes[snake.first] = snake.second;
        }

        void setLadders(vector<pair<int, int>> ladderPos){
            for(auto ladder : ladderPos)
                ladders[ladder.first] = ladder.second;
        }
};

class Game {
    public:
        Board* board;
        vector<pair<User*, int>> players;

        Game(int size, vector<pair<int, int>>snakes, vector<pair<int, int>>ladders, vector<User*> players) {
            board = new Board(size);
            // board->setSnakes(snakes);
            // board->setLadders(ladders);
            for(auto player : players){
                this->players.push_back({player, 0});
            }
        }

        int movePos(int currPos){
            int dieVal = (rand() % 6) + 1;  //roll die
            cout<<dieVal<<endl;
            int newPos = currPos + dieVal;
            if(newPos > board->size)
                return -1;
            else if(board->snakes.find(newPos) != board->snakes.end())
                return board->snakes[newPos];
            else if(board->ladders.find(newPos) != board->ladders.end())
                return board->ladders[newPos];
            else 
                return newPos;
        }

        void startGame(){
            while(true)
                for(auto player : this->players){
                    // if(player.second == board->size)
                    //     continue;

                    cout<<"Player : "<<player.first->username<<" at pos : "<<player.second<<endl;
                    player.second++;
                    // int newPos = movePos(player.second);
                    // if(newPos != -1)
                    //     player.second = newPos;
                    
                    cout<<"NewPos = "<<player.second<<endl;
                    // if(player.second == board->size){
                    //     cout<<player.first->username<<" Won \n";
                    // }
                }
        }
};

int main(){
    User* usr1 = new User(1, "Gaurav");
    User* usr2 = new User(2, "Archit");
    User* usr3 = new User(3, "Ganesh");
    User* usr4 = new User(4, "Meetha Gaurav");
    vector<User*> players = {usr1, usr2, usr3, usr4};

    vector<pair<int, int>>snakes = {{12,2}, {56,23}, {89,2}, {99, 1}};
    vector<pair<int, int>>ladders = {{5,27}, {6,20}, {19,78}, {78, 98}};

    Game* game = new Game(100, snakes, ladders, players);
    // while(true)
        game->startGame();
        game->startGame();
}