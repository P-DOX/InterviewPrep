#include <iostream>
#include "vector"
#include <thread>
#include <algorithm>
#include <cstdlib>
#include "unistd.h"

using namespace std;

enum Direction {
    MOVE_LEFT = 4,
    MOVE_RIGHT = 6,
    MOVE_TOP = 8,
    MOVE_DOWN = 2
};

enum SnakeMoveStatus {
    VALID_MOVE,
    INVALID_MOVE
};

class Player {
    public:
        int userId;
        int score;

        Player(int userId) {
            this->userId = userId;
            this->score = 0;
        }
};

class Board {
    public:
        int boardSize;
        pair<int, int> foodPos;
        int snakeLength;
        vector<pair<int, int>>snakePos;
        Direction moveDirection;

        Board(int boardSize){
            this->boardSize = boardSize;
            this->foodPos = {this->boardSize/2, this->boardSize/2};
            this->snakeLength = 1;
            this->snakePos.push_back({0, 0});
            this->moveDirection = MOVE_LEFT;
        }   

        void moveFood() {
            
            while(true){
                int x = (rand() % boardSize) + 1;  
                int y = (rand() % boardSize) + 1;  
                if(find(snakePos.begin(), snakePos.end(), make_pair(x, y)) == snakePos.end()){
                    this->foodPos.first = x;
                    this->foodPos.second = y;
                    break;
                }
            }
            
        }

        void moveToNextPosition(int x, int y){

            if(x == foodPos.first and y == foodPos.second){
                snakeLength++;
                moveFood();
            }

            if(snakeLength == snakePos.size()){
                snakePos.erase(snakePos.begin());
                snakePos.push_back({x, y});
            }
            else {
                snakePos.push_back({x, y});
            }

        }

        SnakeMoveStatus moveSnake() {

            int x = snakePos[snakeLength-1].first;
            int y = snakePos[snakeLength-1].second;
            if(moveDirection == MOVE_TOP){
                if(x < boardSize)
                    x++;
                else    
                    x = 0;
            }
            else if(moveDirection == MOVE_DOWN){
                if(x > 0)
                    x--;
                else    
                    x = boardSize;
            }
            else if(moveDirection = MOVE_LEFT) {
                if(y > 0)
                    y--;
                else    
                    y = boardSize;
            }
            else if(moveDirection == MOVE_RIGHT){
                if(y < boardSize)
                    y++;
                else    
                    y = 0;
            }

            
            if(find(snakePos.begin(), snakePos.end(), make_pair(x, y)) != snakePos.end())
                return INVALID_MOVE;
            else 
                moveToNextPosition(x, y);

            return VALID_MOVE;
        }

        void displayBoard() {
            vector<string>b(boardSize, string("#", boardSize));
            for(int i=0; i<snakePos.size(); i++){
                b[snakePos[i].first][snakePos[i].second] = '*';
            }
        }

};

void getPlayerInput(Board* board) {
    int move;
    vector<int>v = {2, 8, 4, 6};
    move = v[rand() % 4];
    board->moveDirection = (Direction)move;
    cout<<"Changing movement to <<"<<move<<endl;
    sleep(2000000);
    // cout<<"2 : DOWN \n8 : UP \n4 : LEFT \n6 : RIGHT\n";
    // cout<<"Next move : ";
    // cin>>move;
    // if(move == MOVE_DOWN or move == MOVE_LEFT or move == MOVE_RIGHT or move == MOVE_TOP)
    //     board->moveDirection = (Direction)move;
    // else 
    //     cout<<"Invalid move";

}



class Game {
    public:
        Board* board;
        Player* player;

    Game(int boardSize, Player* player) {
        board = new Board(boardSize);
        this->player = player;
    }

    void startGame(){
        while(true) {
            SnakeMoveStatus status = board->moveSnake();
            if(status == INVALID_MOVE){
                cout<<"GAME OVER \n";
                cout<<"SCORE : "<<player->score<<endl;
                return ;
            }
            else {
                player->score++;
            }   

            board->displayBoard();
            sleep(1000000);
        }
    }
};

int main(){
    
    Player* player = new Player(1);
    Game* game = new Game(100, player);

    thread playerThread = thread(getPlayerInput, game->board);
    playerThread.join();

}

