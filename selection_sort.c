#include <stdio.h>
#include <stdlib.h>

int main()
{
    int enter;
    printf("Please enter the number of string:");
    scanf("%d", &enter);
    int str[enter], a, b, minimum, change;
    printf("\nenter %d numbers:", enter);
    for(a=0;a<enter;a++)
        scanf("%d", &str[a]);

    for(a=0;a<enter-1;a++){
        minimum = str[a];
        for(b=a+1;b<enter;b++){
            if (str[b] < minimum){
                change = str[a];
                str[a] = str[b];
                str[b] = change;
                minimum = str[b];
            }
        }
    }

    for(a=0;a<enter;a++)
        printf("%d ", str[a]);

    return 0;
}
