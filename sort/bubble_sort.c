#include <stdio.h>
#include <stdlib.h>

int main()
{
    int enter;
    printf("Please enter the number of string:");
    scanf("%d", &enter);
    int str[enter], a, b, change;
    printf("\nenter %d numbers:", enter);
    for(a=0;a<enter;a++)
        scanf("%d", &str[a]);

    for(a=0;a<enter-1;a++){
        for(b=0;b<enter-1-a;b++){
            if (str[b] > str[b+1]){
                change = str[b];
                str[b] = str[b+1];
                str[b+1] = change;
            }
        }
    }

    for(a=0;a<enter;a++)
        printf("%d ", str[a]);

    return 0;
}
