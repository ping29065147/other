#include <stdio.h>
#include <stdlib.h>
int all[5][5];
void board(int a, int x, int y)
{
 int i, j;
 char space='_';
 system("cls");

 printf("\t  踩地雷\n\n\t  ");
 for(i=1; i<=5; i++){
  printf("%d ", i);
 }
 printf("\n");
 for(i=1; i<=5; i++){
  printf("\t%d", i);
  for(j=1; j<=5; j++){
   if (all[i][j] == -1){
    if (i == x+1 && j == y+1){
     printf(" %d", a);

    }
    else
     printf(" %c", space);
   }
   else
    printf(" %d", all[i][j]);
  }
  printf("\n");
 }

}

int main()
{
 int place[5][5]{
  2, 9, 2, 1, 1,
  9, 3, 3, 9, 1,
  2, 3, 9, 2, 1,
  9, 3, 2, 1, 0,
  2, 9, 1, 0, 0
 };
 int i, j, enterx, entery, times = 0;

 for(i=1; i<=5; i++){
  for(j=1; j<=5; j++){
   all[i-1][j-1] = -1;
  }
 }

/* for(i=0; i<5; i++){   //歸零
  for(j=0; j<5; j++){
   place[i][j] = 0;
  }
 }
*/

 while(1){

  times++;

  //board(0, -1, -1);
  printf("\n\n\t請輸入座標(x y):");
  scanf("%d %d", &enterx, &entery);
  enterx -= 1;
  entery -= 1;

  if (place[enterx][entery] == 9){
   system("cls");
   printf("\tgame over!!!");
   break;
  }
  else if (place[enterx][entery] == 0){
   board(place[enterx][entery], enterx, entery);
  }
 }
 return 0;
}

