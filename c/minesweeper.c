#include <stdio.h>
#include "minesweeper.h"
#include <time.h>

char ShowMines[X][Y];
char mine[X][Y];
char MineNumber[X][Y];
char safe[X][Y];

void set(){
    int x, y;
    for (x = 0;x < X;x++){
        for (y = 0; y < Y; y++){
            ShowMines[x][y] = 'g';
            mine[x][y] = 0;
            MineNumber[x][y] = 0;
            safe[x][y] = 1;
        }
    }

    unsigned int seed, a;
    srand((unsigned)time(NULL));
    seed=rand();
    for (a = 0; a < B; a++){
        x=SetSeed(seed)%X;
        y=SetSeed(x*a*a)%Y;
        mine[x][y]=1;
        safe[x][y]=0;
        seed+=seed^x;
    }
}
int SetSeed(unsigned int seed){
    srand(seed);
    return rand();
}

void show(){
    int a, b;
    for (a = Y-1;a > -1;a--){
        if (a<9){
            printf("%-4d", a+1);
        }else {
            printf("%-3d", a+1);
        }
        for (b = 0; b < X; b++){
            printf ("   %c", ShowMines[b][a]);
        }
        printf ("\n");
    }
    printf ("0      ");
    for (a = 1;a<X+1;a++){
        if (a<9){
            printf("%-4d", a);
        }else {
            printf("%-3d", a);
        }
    }
    printf ("\n");
}

void number(){
    int x, y, a;
    for (x = 0;x < X;x++){
        for (y = 0; y < Y; y++){
            a=0;
            if(y) a+=mine[x][y-1];
            if(x) a+=mine[x-1][y];
            if(y*x) a+=mine[x-1][y-1];
            if(Y-1-y) a+=mine[x][y+1];
            if(X-1-x) a+=mine[x+1][y];
            if((Y-1-y)*x) a+=mine[x-1][y+1];
            if((X-1-x)*y) a+=mine[x+1][y-1];
            if((Y-1-y)*(X-1-x)) a+=mine[x+1][y+1];
            MineNumber[x][y]=a;
        }
    }
}

int play(){
    int x, y, a, b, m=0;
    set();
    number();
    show();
    while(1){
        m=0;
        for (a = 0;a < X;a++){
            for (b = 0; b < Y; b++){
                m+=safe[a][b];
            }
        }
        //printf ("%d",m);
        if (m==0){
            printf ("win!\n");
            for (a = 0;a < X;a++){
                for (b = 0; b < Y; b++){
                    ShowMines[a][b] = IntToChar(mine[a][b]);
                }
            }
            show();
            break;
        }
        printf ("> ");
        scanf("%d %d", &x, &y);
        if (mine[x-1][y-1]==0){
            ShowMines[x-1][y-1]=IntToChar(MineNumber[x-1][y-1]);
            safe[x-1][y-1]=0;
            if (y-1>0) clean_b(x-1, y-1);
            if (y-1<Y-1) clean_y(x-1, y-1);
            clean(x-1, y-1, x-1, y-1);
            show();
        }else {
            printf ("won!\n");
            for (a = 0;a < X;a++){
                for (b = 0; b < Y; b++){
                    ShowMines[a][b] = IntToChar(mine[a][b]);
                }
            }
            show();
            break;
        }
    }
    printf("Do you want to continue?(1/0)");
    scanf("%d", &a);
    if(a==1) return play();
    return 0;
}
int clean_a(int a, int b, int x, int y){
    if (a>0 && MineNumber[a][b]==0) {
        ShowMines[a-1][b]=IntToChar(MineNumber[a-1][b]);
        safe[a-1][b]=0;
        clean_b(a-1, b);
        clean_y(x-1, y);
        return clean_a(a-1, b, x-1, y);
    }
    return 0;
}
int clean_b(int a, int b){
    if (b>0 && MineNumber[a][b]==0) {
        ShowMines[a][b-1]=IntToChar(MineNumber[a][b-1]);
        safe[a][b-1]=0;
        return clean_b(a, b-1);
    }
    return 0;
}
int clean_x(int a, int b, int x, int y){
    if (x<X-1 && MineNumber[x][y]==0) {
        ShowMines[x+1][y]=IntToChar(MineNumber[x+1][y]);
        safe[x+1][y]=0;
        clean_b(a+1, b);
        clean_y(x+1, y);
        return clean_x(a+1, b, x+1, y);
    }
    return 0;
}
int clean_y(int x, int y){
    if (y<Y-1 && MineNumber[x][y]==0) {
        ShowMines[x][y+1]=IntToChar(MineNumber[x][y+1]);
        safe[x][y+1]=0;
        return clean_y(x, y+1);
    }
    return 0;
}
int clean(int a, int b, int x, int y){
    if (a>=0 && MineNumber[a][b]==0) clean_a(a,b,x,y);
    if (x<=X-1 && MineNumber[x][y]==0)  clean_x(a,b,x,y);
    return 0;
}
char IntToChar(int a){
    if (a==0) return '0';
    if (a==1) return '1';
    if (a==2) return '2';
    if (a==3) return '3';
    if (a==4) return '4';
    if (a==5) return '5';
    if (a==6) return '6';
    if (a==7) return '7';
    if (a==8) return '8';
}
