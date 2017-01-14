#include <iostream>
#include "ioconsole.hpp"

using namespace std;

const int MAX=25;

typedef int rows [MAX];
typedef rows columns [MAX];
columns map;

int snake_x;
int snake_y;
int direction;
int snake_lenght;
bool finish = 0;
bool stop;
unsigned key_pressed;

void draw_map();
void new_apple();
void move();
void menu();
void time();
void fill_map();
void draw_map();

void new_apple(){
    int apple_x;
    int apple_y;
    do{
        apple_x = aleatorio(MAX-2)+1;
        apple_y = aleatorio(MAX-2)+1;
    }while( map[apple_x][apple_y]!=0);
    map[apple_x][apple_y]=-2;
    cio << cursorxy(apple_x+1, apple_y+1)<<'O';
}

void move(){
    int x = 0;
    int y = 0;
    switch( direction ){
        case 0:
            x = 1;
            break;
        case 1:
            y =- 1;
            break;
        case 2:
            x = -1;
            break;
        case 3:
            y = 1;
            break;
        default: break;
    }
    if( map[snake_x + x][snake_y + y] == 0 || map[snake_x + x][snake_y + y] == 1 ){
        for( int i=0; i<MAX; i++ ){
            for( int j=0; j<MAX; j++ ){
                if( map[i][j]>0 ){
                   map[i][j]--;
                   if( map[i][j]==0 ) cio << cursorxy( i+1, j+1 )<<' ';
                }
            }
        }
        map[snake_x+x][snake_y+y]=snake_lenght;
        cio << cursorxy( snake_x+x+1, snake_y+y+1 )<<char(219);
        snake_x += x;
        snake_y += y;
    }
    else if( map[snake_x+x][snake_y+y] == -2 ){
            if( snake_lenght == (MAX-2)*(MAX-2)+1 ){
                cio << cursorxy( 4, MAX/2 - 1 )<<"WINNER WINNER";
                cio << cursorxy( 4, MAX/2 )<<"CHICKEN DINNER!";
                Sleep(1000);
                stop = true;
            }
            else{
                snake_lenght++;
                map[snake_x+x][snake_y+y]=snake_lenght;
                cio << cursorxy( snake_x+x+1, snake_y+y+1 )<<char(219);
                cio<<cursorxy( MAX+9, 2 )<<snake_lenght - 3;

                new_apple();

                snake_x += x;
                snake_y += y;
            }
    }
    else {
            stop = true;
    }
}

void menu (){
	cio << "Press any key to continue\n"
        << "Press ESC to exit\n\n"
        << "W/UP - move up\n"
        << "A/LEFT - move left\n"
        << "D/RIGHT - move right\n"
        << "S/DOWN - move down\n";

	cio >> key(key_pressed);
	if(key_pressed == KEY_ESC){
        finish = true;
	}
    cio << clear_screen;

}

void fill_map()
{
    for(int i=0;i<MAX;i++)
    {
        for(int j=0;j<MAX;j++)
        {
            if(i==0 || i==(MAX-1)|| j==(MAX-1)||j==0)
                map[i][j]=-1;
            else map[i][j]=0;

        }

    }
}
void draw_map(){
    for(int i=0;i<MAX;i++)
    {
        for(int j=0;j<MAX;j++)
        {
            if(map[i][j]==0){
                cio<<' ';

            }else
            cio<<char(177);

        }
        cio<<endl;
    }
    cio<<cursorxy(MAX+1, 2);
    cio<<" SCORE: 0"<<endl;
}

void time(){

    int apple_x = aleatorio(MAX-2)+1; //aleatorio is a randomizer function
    int apple_y = aleatorio(MAX-2)+1;
    int score =0;

    map[snake_x][snake_y]=3;
    map[snake_x-1][snake_y]=2;
    map[snake_x-2][snake_y]=1;
    cio << cursorxy(snake_x+1, snake_y+1) << char(219);
    cio << cursorxy(snake_x, snake_y+1) << char(219);
    cio << cursorxy(snake_x-1, snake_y+1) << char(219);

    new_apple();

    while(!stop){
        if (cio.kbhit()) {
            cio >> key(key_pressed);
            switch (key_pressed){
                case KEY_ESC:
                    stop=1;
                    break;
                case KEY_UP:
                    if(direction!=3) direction = 1; //up
                    break;
                case KEY_LEFT:
                    if(direction!=0) direction = 2; //left
                    break;
                case KEY_DOWN:
                    if(direction!=1) direction = 3; //down    cio<<no_cursor;

                    break;
                case KEY_RIGHT:
                    if(direction!=2) direction = 0; //right
                    break;
                case 'w':
                    if(direction!=3) direction = 1; //up
                    break;
                case 'a':
                    if(direction!=0) direction = 2; //left
                    break;
                case 's':
                    if(direction!=1) direction = 3; //down
                    break;
                case 'd':
                    if(direction!=2) direction = 0; //right
                    break;
                default:
                    break;
            }
        }
        Sleep(300);
        move();
   }
   cio << cursorxy(1, MAX+1);
}

int main()
{
    cio << no_cursor;

    while(!finish){

        snake_x = MAX/4+3;
        snake_y = MAX/2+2;

        stop=0;
        snake_lenght=3;
        direction=0;

        fill_map();
        menu();
        if(!finish){
            draw_map();
            time();
        }

        Sleep(1000);
        cio << clear_screen;
    }

    return 0;
}


