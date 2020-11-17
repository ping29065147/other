#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
    int answer[4], guess[4], enter, x, y, a=0, b=0, t=0;
    srand(time(NULL));

    answer[0] = (rand()%9)+1;
    for(x=1;x<4;x++){
        while(1){
            answer[x] = (rand()%10);
            for(y=0;y<x;y++){
                if (answer[x] == answer[y])
                    break;
            }
            if (y==x)
                break;
        }
    }

    printf("guess a four digit number\n\n");
    for(;;a=0, b=0, t++){
        printf("\n:");
        scanf("%d", &enter);
        for(x=3;x>-1;x--, enter/=10)
            guess[x] = enter%10;

        for(x=0;x<4;x++){
            for(y=0;y<4;y++){
                if (answer[x] == guess[y]){
                    if (x == y)
                        a++;
                    else
                        b++;
                    break;
                }
            }
        }

        printf("\t%dA %dB", a, b);
        if (a==4)
            break;
    }
    printf("\n\nsuccess! %dtimes\n", t+1);

    return 0;
}
