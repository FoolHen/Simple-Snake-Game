#include <iostream>
#include "ioconsole.hpp"

using namespace std;

const int MAX=50;

typedef int filas [MAX];
typedef filas columnas [MAX];
columnas mapa;

int snake_x;
int snake_y;
int dir;
int longitud;
bool finish = 0;
bool stop;
unsigned tecla;

void dibujar_mapa();

void nueva_manzana(){
    int manzana_x;
    int manzana_y;
    do{
        manzana_x = aleatorio(MAX-2)+1;
        manzana_y = aleatorio(MAX-2)+1;
    }while(mapa[manzana_x][manzana_y]!=0);
    mapa[manzana_x][manzana_y]=-2;
    cio << cursorxy(manzana_x+1, manzana_y+1)<<'O';
}

void mover(){
    int x=0;
    int y=0;
    switch(dir){
        case 0:
            x=1;
            break;
        case 1:
            y=-1;
            break;
        case 2:
            x=-1;
            break;
        case 3:
            y=1;
            break;
        default: break;
    }
    if(mapa[snake_x+x][snake_y+y]==0){
        for(int i=0;i<MAX;i++){
            for(int j=0;j<MAX;j++){
                if(mapa[i][j]>0){
                   mapa[i][j]--;
                   if (mapa[i][j]==0) cio << cursorxy(i+1, j+1)<<' ';
                }
            }
        }
        mapa[snake_x+x][snake_y+y]=longitud;
        cio << cursorxy(snake_x+x+1, snake_y+y+1)<<char(219);
        snake_x+=x;
        snake_y+=y;
    }
    else if(mapa[snake_x+x][snake_y+y]==-2){
            if(longitud==(MAX-2)*(MAX-2)+1){
                cio << cursorxy(4, MAX/2-1)<<"WINNER WINNER";
                cio << cursorxy(4, MAX/2)<<"CHICKEN DINNER!";
                Sleep(1000);
                stop=true;
            }
            else{
                longitud++;
                mapa[snake_x+x][snake_y+y]=longitud;
                cio << cursorxy(snake_x+x+1, snake_y+y+1)<<char(219);
                cio<<cursorxy(MAX+9, 2)<<longitud-3;

                nueva_manzana();

                snake_x+=x;
                snake_y+=y;
            }

    }
    else {
            stop=true;
    }
}

void menu (){
	cio << "Pulsa cualquier tecla para jugar\n"
        << "Pulsa ESC para salir\n\n"
        <<"W-mover arriba\n"
        <<"A-mover izda\n"
        <<"D-mover derecha\n"
        <<"s-mover abajo\n";

	cio >> key(tecla);
	if(tecla == KEY_ESC){
        finish = true;
	}
    cio << clear_screen;

}

void rellenar_mapa()
{
    for(int i=0;i<MAX;i++)
    {
        for(int j=0;j<MAX;j++)
        {
            if(i==0 || i==(MAX-1)|| j==(MAX-1)||j==0)
                mapa[i][j]=-1;
            else mapa[i][j]=0;

        }

    }
}
void dibujar_mapa(){
    for(int i=0;i<MAX;i++)
    {
        for(int j=0;j<MAX;j++)
        {
            if(mapa[i][j]==0){
                cio<<' ';

            }else
            cio<<char(219);

        }
        cio<<endl;
    }
    cio<<cursorxy(MAX+1, 2);
    cio<<" SCORE: 0"<<endl;
}

void tiempo(){

    int apple_x = aleatorio(MAX-2)+1;
    int apple_y = aleatorio(MAX-2)+1;
    int score =0;

    /*int c = 0;
    for(int i=1; i<MAX-1;i++){
        for(int j=1; j<MAX-1;j++){
            mapa[i][j]=longitud-2;
            cio << cursorxy(i+1, j+1) << char(219);
            longitud++;

        }
    }
    longitud= longitud-2;
    cio<<cursorxy(MAX-1, MAX-1)<<' ';
    mapa[MAX-2][MAX-2]=0;
    snake_x=MAX-3;
    snake_y=MAX-2;
    cio<<cursorxy(MAX-1, MAX-1)<<' ';*/

    mapa[snake_x][snake_y]=3;
    mapa[snake_x-1][snake_y]=2;
    mapa[snake_x-2][snake_y]=1;
    cio << cursorxy(snake_x+1, snake_y+1) << char(219);
    cio << cursorxy(snake_x, snake_y+1) << char(219);
    cio << cursorxy(snake_x-1, snake_y+1) << char(219);

    nueva_manzana();

    while(!stop){
        if (cio.kbhit()) {
            cio >> key(tecla);
            switch (tecla){
                case KEY_ESC:
                    stop=1;
                    break;
                case KEY_UP:
                    if(dir!=3) dir = 1; //arriba
                    break;
                case KEY_LEFT:
                    if(dir!=0) dir = 2; //izquierda
                    break;
                case KEY_DOWN:
                    if(dir!=1) dir = 3; //abajo
                    break;
                case KEY_RIGHT:
                    if(dir!=2) dir = 0; //derecha
                    break;
                case 'w':
                    if(dir!=3) dir = 1; //arriba
                    break;
                case 'a':
                    if(dir!=0) dir = 2; //izquierda
                    break;
                case 's':
                    if(dir!=1) dir = 3; //abajo
                    break;
                case 'd':
                    if(dir!=2) dir = 0; //derecha
                    break;
                default:
                    break;
            }
        }
        //c++;
        Sleep(50);
        mover();
   }
   cio << cursorxy(1, MAX+1);
}

int main()
{
    cio<<no_cursor;

    while(!finish){

        snake_x = MAX/4+3;
        snake_y = MAX/2+2;

        stop=0;
        longitud=3;
        dir=0;

        rellenar_mapa();
        menu();
        if(!finish){
            dibujar_mapa();
            tiempo();

        }

        Sleep(1000);
        cio << clear_screen;
    }

    return 0;
}


