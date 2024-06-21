#include <vector>
#include <iostream>
#include "game.cpp"
#include <windows.h>
#include <chrono>
#include <curses.h>
#include <string>

// #include <curses.h>
int main() {
    srand((unsigned int)time(NULL));
    int rows=20;
    int cols=20;
    Board board(rows,cols,1);
    board.gameinit(2);
    board.gamemode==1;
    int gameround=1;
    int timeinaround=0;

    
    initscr();            // 初始化curses
    start_color();        // 开启颜色显示
    cbreak();             // 禁用行缓冲
    noecho();             // 禁用回显
    keypad(stdscr, TRUE); // 启用功能键
    mousemask(ALL_MOUSE_EVENTS | REPORT_MOUSE_POSITION, NULL); // 启用所有鼠标事件
    nodelay(stdscr, TRUE);
    MEVENT event;
    int displaymode=1;
    board.display(displaymode);
    std::vector<char> keyboardbuffer(100,0);
    int key=0;

    while(!(GetAsyncKeyState(VK_ESCAPE) & 0x8000)&&board.checkgamestate()){

        

        if(timeinaround==70){
            for (int i=0;i<rows;i++){
                for(int j=0;j<cols;j++){
                    if(board.board[i][j].fieldtype==6||board.board[i][j].fieldtype==7){
                        board.board[i][j].Force++;
                    }
                    else if(gameround%15==0&&(board.board[i][j].fieldtype==4||board.board[i][j].fieldtype==5)){
                        board.board[i][j].Force++;
                    }
                }

            }
        
        if(key>0){
        board.move(keyboardbuffer[0]);
        for(int i=0;i<key;i++){
            keyboardbuffer[i]=keyboardbuffer[i+1];
        }
        key--;
        }
        if(board.gamemode==1){
            board.robotplayermove();
        }

        gameround++;
        board.display(displaymode);
        timeinaround=0;
        }

        int yselect=0;
        int xselect=0;
        int ch = getch();
        if (ch == KEY_MOUSE){
            if (getmouse() & BUTTON1_CLICKED){
                if (nc_getmouse(&event)==OK) {
                    int yselect=event.y;
                    int xselect=event.x/BlockWidth;
                    if(yselect<=rows && yselect>=0 && xselect<=cols && xselect>=0 && board.board[yselect][xselect].belong==board.player){
                        board.board[board.yselect][board.xselect].selected=0;
                        board.board[yselect][xselect].selected=1;
                        board.yselect=yselect;
                        board.xselect=xselect;
                    }
                }
            }
        }
        else if (ch=='w'||ch=='W'||ch=='a'||ch=='A'||ch=='s'||ch=='S'||ch=='d'||ch=='D'){
            keyboardbuffer[key++]=ch;
        }
        else if (ch=='q'||ch=='Q'){
            key=0;
        }

    
    timeinaround++;
    Sleep(1);  
    }    
    
    
    nodelay(stdscr, FALSE);
    init_pair(1, COLOR_YELLOW, COLOR_RED );
    attron(COLOR_PAIR(1));
    mvprintw(rows/2,BlockWidth*((cols-1)/2)-1, "    ");mvprintw(rows/2,BlockWidth*((cols-1)/2)+1, "    ");
    mvprintw(rows/2+1,BlockWidth*((cols-1)/2)-1, "    ");mvprintw(rows/2+1,BlockWidth*((cols-1)/2)+1, "    ");
    mvprintw(rows/2-1,BlockWidth*((cols-1)/2)-1, "    ");mvprintw(rows/2-1,BlockWidth*((cols-1)/2)+1, "    ");
    attroff(COLOR_PAIR(1));
    mvprintw(rows/2,BlockWidth*(cols-1)/2, "GAME OVER!");
    mvprintw(rows/2+1,BlockWidth*(cols-1)/2-5, "PRESS ANY KEY TO EXIT");
    
    if(getch()==1){
    endwin(); // 结束curses模式
    
    return 0;}
}

