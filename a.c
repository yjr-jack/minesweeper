#include <stdio.h>
#include "a.h"
#include <time.h>
#include <stdlib.h>

char c[X][Y];//空
char e[X][Y];//0
char g[X][Y];//计0

void fa(){
    int a, b;
    for (a = 0;a < X;a++){
        for (b = 0; b < Y; b++){
            c[a][b] = '#';//显示
            e[a][b] = 0;//雷
            g[a][b] = 0;//雷数
        }
    }
}

void fb(){
    unsigned int a, b, d, f;
    srand((unsigned)time(NULL));
    a=rand();
    for (b = 0; b < B; b++){
        d=ft(a)%X;
        f=ft(d*b*b)%Y;
        e[d][f]=1;
        a+=a^d;
    }
}
int ft(unsigned int seed){
    srand(seed);
    return rand();
}
void fd(){
    int x, y, a;
    for (x = 0;x < X;x++){
        for (y = 0; y < Y; y++){
            a=0;
            if(y) a+=e[x][y-1];//雷
            if(x) a+=e[x-1][y];
            if(y*x) a+=e[x-1][y-1];
            if(Y-1-y) a+=e[x][y+1];
            if(X-1-x) a+=e[x+1][y];
            if((Y-1-y)*x) a+=e[x-1][y+1];
            if((X-1-x)*y) a+=e[x+1][y-1];
            if((Y-1-y)*(X-1-x)) a+=e[x+1][y+1];
            g[x][y]=a;//雷数
        }
    }
}

void fc(){
    int a, b;
    for (a = Y-1;a > -1;a--){
        if (a<9){
            printf("%-3d", a+1);
        }else {
            printf("%-3d", a+1);
        }
        for (b = 0; b < X; b++){
            if(c[b][a]=='0') printf (" o");
            else printf (" %c", c[b][a]);//棋盘
        }
        printf ("\n");
    }
    printf ("0   ");
    for (a = 1;a<X+1;a++){//底部
        if (a<9){
            printf("%-2d", a);
        }else {
            printf("%-2d", a);
        }
    }
    printf ("\n");
}

int fe(){
    int x, y,z, a, b, m=0;
    while(1){
    for (a = 0;a < X;a++){
        for (b = 0; b < Y; b++){
            m+=e[a][b];//反雷
        }
    }
    if (m==0){
        printf ("win!\n");
        return 0;
    }
    printf ("scanf  (x y): ");
    scanf("%d %d %d", &x, &y, &z);
    if(x>X||y>Y){
        printf ("wrong!\n");
    }else if(z){//有雷非0
        if(e[x-1][y-1]){//是雷
            c[x-1][y-1]='$';
            g[x-1][y-1]='$';
            e[x-1][y-1]=0;
            if (y-1>0) fg_b(x-1, y-1);//y负清零
            if (y-1<Y-1) fg_y(x-1, y-1);//y正清零
            fg(x-1, y-1, x-1, y-1);//x左右
            fc();
            return fe();
        }else{//非雷
            printf ("won!\n"); 
            return 0;
        }
    } else{//无雷0
        if(e[x-1][y-1]){//有雷
            printf ("won!\n"); 
            return 0;
        }else{//非雷
            c[x-1][y-1]=IntToChar(g[x-1][y-1]);//雷数
            if (y-1>0) fg_b(x-1, y-1);//y负清零
            if (y-1<Y-1) fg_y(x-1, y-1);//y正清零
            fg(x-1, y-1, x-1, y-1);//x左右
            fc();
        }
    }
}
}

int fg_a(int a, int b, int x, int y){//x负
    if (a>0 && e[a-1][b]!=1) {
        c[a-1][b]=IntToChar(g[a-1][b]);
        fg_b(a-1, b);
        fg_y(x-1, y);
        return fg_a(a-1, b, x-1, y);
    }
    return 0;
}
int fg_b(int a, int b){//y负向清零
    if (b>0 && e[a][b-1]!=1) {//雷
        c[a][b-1]=IntToChar(g[a][b-1]);
        return fg_b(a, b-1);
    }
    return 0;
}
int fg_x(int a, int b, int x, int y){//x正
    if (x<X-1 && e[x+1][y]!=1) {
        c[x+1][y]=IntToChar(g[x+1][y]);
        fg_b(a+1, b);
        fg_y(x+1, y);
        return fg_x(a+1, b, x+1, y);
    }
    return 0;
}
int fg_y(int x, int y){//y正向清零
    if (y<Y-1 && e[x][y+1]!=1) {//雷
        c[x][y+1]=IntToChar(g[x][y+1]);
        return fg_y(x, y+1);
    }
    return 0;
}
int fg(int a, int b, int x, int y){
    if (a>=0 && e[a][b]!=1) fg_a(a,b,x,y);
    if (x<=X-1 && e[x][y]!=1)  fg_x(a,b,x,y);
    return 0;
}
char IntToChar(int a){
    switch(a){
        case 0: return '0';
        case 1: return '1';
        case 2: return '2';
        case 3: return '3';
        case 4: return '4';
        case 5: return '5';
        case 6: return '6';
        case 7: return '7';
        case 8: return '8';
        default : return '#';
    }
}
