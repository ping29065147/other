#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define boy 21
#define girl 17
#define last_number 40

int main()
{
    int seat[6][7], a, b, x, y;
    srand(time(NULL));

    for(a=0;a<6;a++){
        for(b=0;b<7;b++)
            seat[a][b] = 0;
    }

    for(a=1;a<=last_number;a++){
        if (a==7 || a==28)
            a++;
        while(1){
            x = rand()%6;
            y = rand()%7;
            if (x==0 && y==0)
                continue;
            else if (x==0 && y==6)
                continue;
            else if (x==5 && y==0)
                continue;
            else if (x==5 && y==6)
                continue;

            if (seat[x][y] == 0){
                seat[x][y] = a;
                break;
            }
        }
    }

    for(a=0;a<6;a++){
        for(b=0;b<7;b++){
            printf("%3d ",seat[a][b]);
        }
        printf("\n");
    }

    return 0;
}
