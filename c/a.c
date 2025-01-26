void fa(){
    int a, b;
    for (a = 0;a < X;a++){
        for (b = 0; b < Y; b++){
            c[a][b] = 'g';
            e[a][b] = 0;
            g[a][b] = 0;
            h[a][b] = 1;
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
        h[d][f]=0;
        a+=a^d;
    }
}
int ft(unsigned int seed){
    srand(seed);
    return rand();
}
void fc(char D[X][Y]){
    int a, b;
    for (a = Y-1;a > -1;a--){
        if (a<9){
            printf("%-4d", a+1);
        }else {
            printf("%-3d", a+1);
        }
        for (b = 0; b < X; b++){
            printf ("   %c", D[b][a]);
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
void fd(){
    int x, y, a;
    for (x = 0;x < X;x++){
        for (y = 0; y < Y; y++){
            a=0;
            if(y) a+=e[x][y-1];
            if(x) a+=e[x-1][y];
            if(y*x) a+=e[x-1][y-1];
            if(Y-1-y) a+=e[x][y+1];
            if(X-1-x) a+=e[x+1][y];
            if((Y-1-y)*x) a+=e[x-1][y+1];
            if((X-1-x)*y) a+=e[x+1][y-1];
            if((Y-1-y)*(X-1-x)) a+=e[x+1][y+1];
            g[x][y]=a;
        }
    }
}
int fe(){
    int x, y, a, b, m=0;
    for (a = 0;a < X;a++){
        for (b = 0; b < Y; b++){
            m+=h[a][b];
        }
    }
    if (m==0){
        printf ("win!");
        return 0;
    }
    printf ("scanf (x y): ");
    scanf("%d %d", &x, &y);
    if (e[x-1][y-1]==0){
        c[x-1][y-1]=fi(g[x-1][y-1]);
        h[x-1][y-1]=0;
        if (y-1>0) fg_b(x-1, y-1);
        if (y-1<Y-1) fg_y(x-1, y-1);
        fg(x-1, y-1, x-1, y-1);
        fc(c);
        return fe();
    }else {
        printf ("won!\n");
        for (a = 0;a < X;a++){
            for (b = 0; b < Y; b++){
                c[a][b] = fi(e[a][b]);
            }
        }
        fc(c);
        return 0;
    }
}
int fg_a(int a, int b, int x, int y){
    if (a>0 && g[a][b]==0) {
        c[a-1][b]=fi(g[a-1][b]);
        h[a-1][b]=0;
        fg_b(a-1, b);
        fg_y(x-1, y);
        return fg_a(a-1, b, x-1, y);
    }
    return 0;
}
int fg_b(int a, int b){
    if (b>0 && g[a][b]==0) {
        c[a][b-1]=fi(g[a][b-1]);
        h[a][b-1]=0;
        return fg_b(a, b-1);
    }
    return 0;
}
int fg_x(int a, int b, int x, int y){
    if (x<X-1 && g[x][y]==0) {
        c[x+1][y]=fi(g[x+1][y]);
        h[x+1][y]=0;
        fg_b(a+1, b);
        fg_y(x+1, y);
        return fg_x(a+1, b, x+1, y);
    }
    return 0;
}
int fg_y(int x, int y){
    if (y<Y-1 && g[x][y]==0) {
        c[x][y+1]=fi(g[x][y+1]);
        h[x][y+1]=0;
        return fg_y(x, y+1);
    }
    return 0;
}
int fg(int a, int b, int x, int y){
    if (a>=0 && g[a][b]==0) fg_a(a,b,x,y);
    if (x<=X-1 && g[x][y]==0)  fg_x(a,b,x,y);
    return 0;
}
char fi(int a){
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
