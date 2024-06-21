#include "game.h"
#include <iostream>
#include <random>
#include <ctime>
#include <string>
#include <iomanip>
#include <curses.h>
#include <algorithm>


int myrandom(int n){
		int x;
		x = rand() % n ;
    return x;
}

std::vector<int> generateShuffledVector(int n) {
    std::vector<int> vec;
    vec.reserve(n + 1);  // Optionally reserve space to avoid reallocations
    for (int i = 0; i < n; ++i) {
        vec.push_back(i);
    }
    
    // Shuffle the vector
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(vec.begin(), vec.end(), g);
    
    return vec;
}


Board :: Board (int rows, int cols,int player){
    Board::rows=rows;
    Board::cols=cols;
    Board::player=player;
    field defaultfield(0,0,0);
    std::vector<std::vector<field>> board(rows,std::vector<field>(cols,defaultfield));
    Board::board=board;
    Board::xselect=0;
    Board::yselect=0;
    Board::gamemode=1;//single game
    Board::robotplayernumber=2;
    Board::robotland=1;

    }





void Board::gameinit(int playernumber){
    
    int P1x=myrandom(rows-2)+1;
    int P1y=myrandom(cols-2)+1;
    

    field initP1(P1x,P1y,6);
    board[P1x][P1y]=initP1;
    
    int P2x=myrandom(rows-2)+1;
    int P2y=myrandom(cols-2)+1;
    
    while (P2x == P1x && P2y==P1y){
        P2x=myrandom(rows-2)+1;
        P2y=myrandom(cols-2)+1;
    }
    field initP2(P2x, P2y, 7);
    board[P2x][P2y]=initP2;
    p1kingx=P1x;
    p1kingy=P1y;
    p2kingx=P2x;
    p2kingy=P2y;
    for(int i=0;i<rows;i++){
        for(int j=0;j<cols;j++){
            
            if((i == P1x && j==P1y)||(i == P2x && j==P2y)){
                continue;
            }
            else if(i==0||i==rows-1||j==0||j==cols-1||myrandom(100)<12){
                field Mountain(i,j,1);
                board[i][j]=Mountain;
                continue;
            }
            else if(myrandom(100)<5){
                field Castle(i,j,2);
                board[i][j]=Castle;
                continue;
            }
            else {
                field FreeField(i,j,3);
                board[i][j]=FreeField;
                continue;
                }
        }
        
    }
}

// void Board :: display() const{
//     for (int i=0;i<rows;i++){
//         for(int j=0;j<cols;j++){
//         std::cout << std::left << std::setw(10) << board[i][j].fieldcolor
//                       << std::right << std::setw(5) << board[i][j].Force;
//         }std::cout<<std::endl;
//     }
// }

bool Board::checkgamestate(){
    if (board[p1kingx][p1kingy].belong==2||board[p2kingx][p2kingy].belong==1){
        return 0;
    }
    else return 1;
}

void Board :: display(int mode) const{
    
    init_pair(1, COLOR_BLACK, COLOR_WHITE);  // 创建颜色对，第一个参数是颜色对的索引，后面两个参数分别是前景色和背景色//mountain
    init_pair(2, COLOR_BLACK, COLOR_WHITE);//castle
    init_pair(3,  COLOR_WHITE, COLOR_BLACK); //free field
    init_pair(4, COLOR_RED, COLOR_BLACK );  //p1
    init_pair(5, COLOR_BLUE, COLOR_BLACK ); //p2
    init_pair(6, COLOR_BLACK, COLOR_RED );  //p1 castle
    init_pair(7, COLOR_BLACK,COLOR_BLUE); //p2 castle
    
    if(mode==1)
    {for (int i=0;i<rows;i++){
        for(int j=0;j<cols;j++){
            attron(COLOR_PAIR(board[i][j].fieldcolor));
            std::string string=std::to_string(board[i][j].Force);
            if (i==0||j==0||i==rows-1||j==cols-1) string=" ";
            else if(board[i][j].fieldtype==1) string="M";
            mvprintw(i, BlockWidth*j,"     ");
            mvprintw(i, BlockWidth*j, string.c_str());
            attroff(COLOR_PAIR(board[i][j].fieldcolor));
        }
    }refresh();}
    else if(mode==0){
        
        for (int i=0;i<rows;i++){
        for(int j=0;j<cols;j++){
            
            if(i>0&&i<rows-1&&j>0&&j<cols-1&&(board[i][j].belong==player||board[i-1][j].belong==player||board[i+1][j].belong==player
            ||board[i][j-1].belong==player||board[i][j+1].belong==player||board[i+1][j+1].belong==player||board[i+1][j-1].belong==player||board[i-1][j+1].belong==player||board[i-1][j-1].belong==player))
            {
            attron(COLOR_PAIR(board[i][j].fieldcolor));
            std::string string=std::to_string(board[i][j].Force);
            if (i==0||j==0||i==rows-1||j==cols-1) string=" ";
            else if(board[i][j].fieldtype==1) string="M";
            mvprintw(i, BlockWidth*j,"     ");
            mvprintw(i, BlockWidth*j, string.c_str());
            attroff(COLOR_PAIR(board[i][j].fieldcolor));
            }
            else {attron(COLOR_PAIR(1));
            mvprintw(i, BlockWidth*j,"     ");
            attroff(COLOR_PAIR(1));}
        }
    }refresh();

    }
    
    }

bool Board::capture(int row, int col, int direction){
    int rowtarg=0;
    int coltarg=0;
    switch (direction){
    case UP:{
    rowtarg=row-1;
    coltarg=col;
    break;
    }
    case LEFT:{
    rowtarg=row;
    coltarg=col-1;
    break;
    }
    case DOWN:{
    rowtarg=row+1;
    coltarg=col;
    break;
    }
    case RIGHT:{
    rowtarg=row;
    coltarg=col+1;
    break;
    }
    default:{}
    }
    
    if(board[rowtarg][coltarg].fieldtype!=1 && board[row][col].Force>=1){
        if (board[rowtarg][coltarg].belong==player){
            board[rowtarg][coltarg].Force+=board[row][col].Force-1;
            board[row][col].Force=1;
            yselect=rowtarg;
            xselect=coltarg;
            board[rowtarg][coltarg].selected=1;
            board[row][col].selected=0;
            return 1;
        }
        else{
            
            if(board[row][col].Force-1>board[rowtarg][coltarg].Force){
                board[rowtarg][coltarg].Force=board[row][col].Force-1-board[rowtarg][coltarg].Force;
                board[rowtarg][coltarg].ChangeBelong(player);
                board[row][col].Force=1;
                yselect=rowtarg;
                xselect=coltarg;
                board[rowtarg][coltarg].selected=1;
                board[row][col].selected=0;
                return 1;
                }
            else{
                board[rowtarg][coltarg].Force-=board[row][col].Force-1;
                board[row][col].Force=1;
                return 0;
            }
            }
        
        }
        return 0;
    }

bool Board::move(char direction){
    switch (direction){
    
        case 'w':case 'W':{
            for (int i=0;i<rows;i++){
                    for(int j=0;j<cols;j++){
                        if(board[i][j].selected==1){
                            return(capture(i,j,UP)); 
                        }
                    }
                }
            break;
        }
        case 'a':case 'A':{
            for (int i=0;i<rows;i++){
                    for(int j=0;j<cols;j++){
                        if(board[i][j].selected==1){
                            return(capture(i,j,LEFT)); 
                        }
                    }
                }
            break;
        }
        case 's':case 'S':{
            for (int i=0;i<rows;i++){
                    for(int j=0;j<cols;j++){
                        if(board[i][j].selected==1){
                            return(capture(i,j,DOWN)); 
                        }
                    }
                }
            break;
        }
        case 'd':case 'D':{
            for (int i=0;i<rows;i++){
                    for(int j=0;j<cols;j++){
                        if(board[i][j].selected==1){
                            return(capture(i,j,RIGHT)); 
                        }
                    }
                }
            break;
        }
        default:{
            break;
        }
    }
    return 0;
}

bool Board::robotplayermove(){
    
    int direction=myrandom(4)+1;
    int totleforce=0;
    for (int i=0;i<rows;i++){
        for(int j=0;j<cols;j++){
            if (board[i][j].belong==robotplayernumber) totleforce+=board[i][j].Force;
        }}


    int tendency=totleforce;

        std::vector<int> ivector=generateShuffledVector(rows);
        std::vector<int> jvector=generateShuffledVector(cols);
int i=0;
int j=0;
    for (int m=0;m<rows;m++){
        i=ivector[m];
        for(int n=0;n<cols;n++){
            j=jvector[n];
            if (board[i][j].belong==robotplayernumber&&board[i][j].Force>1){
            
            if(i>0&&i<rows-1&&j>0&&j<cols-1){
                switch (myrandom(4))
                {case 0:{
                if(board[i-1][j].belong==0)
            {tendency=tendency/2+1;direction=UP;}
            else if(board[i+1][j].belong==0)
            {tendency=tendency/2+1;direction=DOWN;}
            else if(board[i][j+1].belong==0)
            {tendency=tendency/2+1;direction=RIGHT;}
            else if(board[i][j-1].belong==0)
            {tendency=tendency/2+1;direction=LEFT;}
            break;}
                case 1:{
                if(board[i+1][j].belong==0)
            {tendency=tendency/2+1;direction=DOWN;}
            else if(board[i][j+1].belong==0)
            {tendency=tendency/2+1;direction=RIGHT;}
            else if(board[i][j-1].belong==0)
            {tendency=tendency/2+1;direction=LEFT;}
            else if(board[i-1][j].belong==0)
            {tendency=tendency/2+1;direction=UP;}
            break;}
                case 2:{
                if(board[i][j+1].belong==0)
            {tendency=tendency/2+1;direction=RIGHT;}    
            else if(board[i][j-1].belong==0)
            {tendency=tendency/2+1;direction=LEFT;}
            else if(board[i-1][j].belong==0)
            {tendency=tendency/2+1;direction=UP;}
            else if(board[i+1][j].belong==0)
            {tendency=tendency/2+1;direction=DOWN;}
            break;}
                case 3:{
                    if(board[i][j-1].belong==0)
                        {tendency=tendency/2+1;direction=LEFT;}  
                        else if(board[i-1][j].belong==0)
                        {tendency=tendency/2+1;direction=UP;}
                        else if(board[i+1][j].belong==0)
                        {tendency=tendency/2+1;direction=DOWN;}
                        else if(board[i][j+1].belong==0)
                        {tendency=tendency/2+1;direction=RIGHT;}  
                        break;
                }
                }

            }
            

            if (myrandom(tendency)+1<=board[i][j].Force){
                
                int rowtarg=0;
                int coltarg=0;
                switch (direction){
                case UP:{
                rowtarg=i-1;
                coltarg=j;
                break;
                }
                case LEFT:{
                rowtarg=i;
                coltarg=j-1;
                break;
                }
                case DOWN:{
                rowtarg=i+1;
                coltarg=j;
                break;
                }
                case RIGHT:{
                rowtarg=i;
                coltarg=j+1;
                break;
                }
                default:{}
                }
                
                if(board[rowtarg][coltarg].fieldtype!=1 && board[i][j].Force>=1){
                    if (board[rowtarg][coltarg].belong==robotplayernumber){
                        board[rowtarg][coltarg].Force+=board[i][j].Force-1;
                        board[i][j].Force=1;
                        return 1;
                    }
                    else{
                        
                        if(board[i][j].Force-1>board[rowtarg][coltarg].Force){
                            board[rowtarg][coltarg].Force=board[i][j].Force-1-board[rowtarg][coltarg].Force;
                            board[rowtarg][coltarg].ChangeBelong(robotplayernumber);robotland++;
                            board[i][j].Force=1;
                            return 1;
                            }
                        else{
                            board[rowtarg][coltarg].Force-=board[i][j].Force-1;
                            board[i][j].Force=1;
                            return 0;
                        }
                        }
                    
                    }
                    else return 0;
            
            }
            
            }
        }}
return 0;
}





field :: field(int row,int col, int fieldtype){
    field::row=row;
    field::col=col;
    field::Force=1;
    field::fieldtype=fieldtype;
    field::fieldcolor=fieldtype;
    field::selected=0;
    switch (fieldtype){
        case 1:{
        field::belong=-1;
        break;}
        case 2:
        {Force=myrandom(20)+40;
        field::belong=0;
        break;}
        case 3:{
        belong=0;
        field::Force=0;
        break;}
        case 5:
        case 7:{
        field::belong=2;
        break;}
        case 4:
        case 6:
        {field::belong=1;
        break;}
        default:{}
    }
    

}
void field::ChangeBelong(int tobelong){
    belong=tobelong;
    if(tobelong==1){
        switch(fieldtype){
        case 5: case 3:{fieldtype=4;
        fieldcolor=4 ;break;}
        case 2:case 7:{fieldtype=6;
        fieldcolor=6;break;}

        
    }
    }
    else if (tobelong==2)
    {switch(fieldtype){
        case 4: case 3:{fieldtype=5;
        fieldcolor=5;break;}
        case 2:case 6: {fieldtype=7;
        fieldcolor=7;break;}
        }
    }
}
