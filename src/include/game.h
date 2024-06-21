#ifndef GAME_H
#define GAME_H
#include <vector>
#include <iostream>
#include <string>
#define BlockWidth 5
#define UP 1
#define LEFT 2
#define DOWN 3
#define RIGHT 4




class field{
    public:
    field(int row, int col, int fieldtype);
    int fieldcolor;
    int Force;
    int fieldtype;//1 for "mountain"; 2 for "lockedcastle"; 3 for "free field"; 4 for "field of player 1"; 5 for "field of player 2";6 for "unlockedcastle" of p1;7 for "unlockedcastle" of p2;
    bool selected;
    int belong;
    void ChangeBelong(int tobelong);
    
    private:
    int row;
    int col;
    
    
    
    
};

class Board {
public:
    Board(int rows, int cols, int player);
    void gameinit(int playernumber);
    void display(int mode) const;
    bool capture(int row, int col, int direction);
    bool move(char direction);
    bool checkgamestate();
    std::vector<std::vector<field>> board;
    int xselect;
    int yselect;
    int player;
    int gamemode;
    int rows;
    int cols;


    bool robotplayermove();


private:
    
    int p1kingx;
    int p1kingy;
    int p2kingx;
    int p2kingy;
    
    
    int robotplayernumber;
    int robotland;

};



#endif