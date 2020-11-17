#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#define add(x0, y0) ((x0)+(y0))
#define minus(x0, y0) ((x0)-(y0))
#define multiply(x0, y0) ((x0)*(y0))
#define divide(x4, y4) ((x4)/(y4))
#define OUT_STR "\n%s\n%d%c%d="
int hint = 20;
char letter[9];

void boy_girl(void)  //數學排列題目
{
	int g,b,answer,d,totalg1 = 1,totalg2 = 1,totalb = 1,e;
	srand(time(NULL));

	do{
		g=(rand()%9)+1;
		b=(rand()%9)+1;
	}while(g>=b);

	printf("%d男%d女排隊，女生不相鄰，共有幾種排法? ",b,g);
	for(d=b;d>0;d--)
		totalb=totalb*d ;
	for(d=b+1;d>0;d--)
		totalg1=totalg1*d ;
	for(d=b-g+1;d>0;d--)
		totalg2=totalg2*d ;
	answer=totalb*totalg1/totalg2;

	scanf("%d",&e   );
	//printf("answer= %d",answer);
	if (e == answer){
		hint++;
		printf("\n答對了!");
	}
	else
		printf("錯誤");

}
void ranking(int level)  //排行榜，可儲存紀錄
{
	struct namelevel {
		int level;
		char name[20];
	};
	struct namelevel nl[10];
	FILE *fp;
	char name[20], rank_file[20] = "C:c_program.txt";
	int i, j, k, idx = 0;
	memset(nl, 0, 10*sizeof(struct namelevel));

	if ((fp = fopen(rank_file, "r+")) == NULL){
		printf("無法開啟檔案");
		return;
	}
	else{
		for(i = 0; i < 10; i++){
			if(fscanf(fp, "%d%s", &nl[i].level, nl[i].name) == EOF)
				break;
			else
				idx++;
		}
	}
	fclose(fp);
	if (idx == 0){
		printf("\n請輸入您的名字:");
		fflush(stdout);
		scanf("%s", name);
		nl[0].level =  level;
		strcpy(nl[0].name,name);
		idx++;
	}
	else{
		for(i = 0; i < idx+1; i++){
			if (level >= nl[i].level){
				printf("\n請輸入您的名字:");
				fflush(stdout);
				scanf("%s", name);
				if (idx == 10)
					k = idx-2;
				else
					k = idx-1;
				for(j = k; j >= i; j--)
					nl[j+1] = nl[j];
				nl[j+1].level =  level;
				strcpy(nl[j+1].name,name);
				break;
			}
		}
		if (i == 10)
			printf("\n您的成績不足以排入前十名");
	}
	if (idx == 10)
		idx--;

	if((fp = fopen(rank_file, "w")) == NULL)
		printf("無法開啟檔案");
	else{
		for(i = 0; i <= idx; i++){
			fprintf(fp, "%d %s\n", nl[i].level, nl[i].name);
		}
		fclose(fp);
	}

	printf("\n排行榜\n");
	for(i = 0; i <= idx; i++){
		printf("\n第%d名，通過%d關   %s", i+1, nl[i].level, nl[i].name);
	}

#if 0
	printf("\n請輸入您的名字:");
	fflush(stdout);
	scanf("%s", name);
	if((fp = fopen(rank_file, "r+")) == NULL)
		printf("無法開啟檔案");
	else{
		fprintf(fp, "%s  共通過%d關",name, level);
		fclose(fp);
	}
#endif
}

void ab_control(char *first, int end)  //15關後，隨機英文字母(題目的答案)
{
	char ynum[2];
	int i = 2;

	ynum[1]='\0';
again:
	ynum[0] = 'a' + rand()%26;
	if (strchr(first, ynum[0]) == NULL) {  //先給ynum帶入一個字元，判斷first(letter)裡面有沒有跟ynum一樣字元
		strcat(first, ynum);  //如果沒有，則將ynum給first(letter)
		if (i++ < end)  //判斷做的次數
			goto again;
	}
	else
		goto again;
}

/*void abc_control(char *first, int end)
{
	int k;
	static int s = 1, count = 2;
	static char ynum[8];

	if (count <= end){
		ynum[0] = 'a' + rand()%26;
		for (k = 0; k < s; k++){
			if (ynum[k] == *(first + k))
				abc_control(letter, end);
		}
		if (s <= end){
			*(first + s) = ynum[0];
			s++;
			count++;
			abc_control(letter, end);
		}
	}
}*/

void my_math(char *txt, int x, int y, char c, int z0)
{
	char out_string[80];
	int xy0;

	snprintf(out_string, 80, OUT_STR, txt, x, c, y);
	printf(out_string);
	fflush(stdout);
	scanf("%d",&xy0);
	if (xy0 == z0){
		hint++;
		printf("\n答對了!");
	}
	else
		printf("錯誤");
}

void equal_difference(int *a1, int *d1, int *n1, int *an1, float *sn1)
{
	srand(time(NULL));
	*a1 = (rand()%20);
	*d1 = (rand()%10)+1;
	*n1 = (rand()%10)+3;
	*an1 = *a1+(*n1-1)**d1;
	*sn1 = *n1*(*a1+*an1)*0.5;
}

void factorial(void)
{
	int guess6, answer6 = 1, r6;
	int num6, amount6;

	num6 = (rand()%11)+10;
	amount6 = (rand()%9)+2;
	printf("\n1~%d號，取出%d個號碼作排列，共有幾種排法?", num6, amount6);
	fflush(stdout);
	scanf("%d",&guess6);
	for(r6 = 0; r6 < amount6; r6++){
		answer6 *= num6--;
	}
	if (guess6 == answer6){
		hint++;
		printf("\n答對了!");
	}
	else
		printf("錯誤");
}


int main(void)
{

	int guess[4];  //輸入的4位數(千位guess[0],百位guess[1],十位guess[2],個位guess[3])
	int answer[6];  //4位亂數分別存入變數(千位answer[2],百位answer[3],十位answer[4],個位answer[5])
	int q, s;  //判斷對應的變數
	int i, k, o;  //產生亂數用
	int enter, num;  //   輸入的4位數, 次數
	int a, b;  //A B
	int xnum[3];  //產生亂數用的變數(xnum[0],xnum[1],xnum[2])
	int level;
	int out=0; //關卡數用
	char ro, ro1;  //判斷是否繼續
	int r=10;  //猜題數
	int hintx, hinty[10], hint1;
	int kind;
	int x0, y0, z0;  //加法
	int x4, y4;
	int a1, d1, n1, an1, ans_an1;  //等差
	float sn1, ans_sn1;  //等差
	char letter_in[5];  //2 3 4 5
	int end = 4;


	system("color f9");
	printf("                         ____________________________\n");
	printf("                         *幾A幾B是一款真正的解謎遊戲*\n");
	printf("                         ~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	printf("                                  遊戲規則:\n");
	printf("________________________________________________________________________________\n");
	printf("系統會隨機產生一個四位(數字、字母)，如果你輸入的四位(數字、字母)與系統產生的四位(數字、字母)相同、也相同位置，就會有1A，如果相同(數字、字母)但不同位置，則會有1B");
	printf("________________________________________________________________________________\n");
	system("pause");
	printf("                        *系統產生的(數字、字母)不會重複*\n");
	printf("________________________________________________________________________________\n");
	system("pause");
	printf("本遊戲共有20關，前14關為猜數字，第1~7關可猜題數依序為10,9,8,7,6,5,4，會顯示A的位置。第8~14關的猜題數也是10,9,8,7,6,5,4，但不會顯示出A的位置");
	printf("第15~20關為猜字母(小寫)，可猜題數為12，會顯示A的位置。\n");
	printf("________________________________________________________________________________\n");
	system("pause");
	printf("                                  *hint!*\n");
	printf("________________________________________________________________________________\n");
	system("pause");
	printf("每過一關，會進行一次bonus，bonus答對會獲得一個hint\n如果在(猜題數-2)以前就答對，也會獲得1個hint");
	printf("\n你可以花費2個hint來獲得1A(輸入(數字、字母)時，輸入0000即是使用1個hint)，也可以用5個hint來復活\n");
	printf("________________________________________________________________________________\n");
	printf("\n快來挑戰自我吧\n");

	fflush(stdout);
	system("pause");


	for (level = 15; level < 21; level++){  //關卡數(20)

		a = 0;  //重置數值
		b = 0;  //重置數值
		o = 2;  //重置數值
		for (hint1=0; hint1<end; hint1++)  //重置數值
			hinty[hint1] = 0;

		printf("\nlevel %d\n",level);
		printf("\n剩餘hint:%d\n",hint);
		fflush(stdout);
		srand(time(NULL));

		if (level < 15){  //前14關
			answer[2] = (rand()%9)+1 ;  //亂數千位數
			//printf("%d" , answer[2] );  //顯示亂數千位數(方便調整)///////////////////////////////
			answer[0] = 10;
			answer[1] = 10;

			for (k=0; k<3; k++){  //變數(百位0 十位1 個位2)
				while (1){
					xnum[k] = rand()%10;  //以這個變數儲存亂數
					if (xnum[k] != answer[o]){  //判斷是否等於前一個亂數
						if (xnum[k] != answer[o-1]){  //判斷是否等於前兩個亂數
							if (xnum[k] != answer[o-2]){  //判斷是否等於前三個亂數
								answer[o+1] =xnum[k];  //如果這個變數(xnum)都不等於前面的變數，將其值帶入(answer)
								//printf("%d" , answer[o+1] );  //顯示亂數(方便調整)/////////////////////////////////////
								break;
							}
						}
					}
				}
				o++;  //亂數(百位3 十位4 個位5)
			}
		}
		else{  // 15關後
			memset(letter, 0, 9);  //重置數值
			letter[0] = 'a' + rand()%26;
			//printf("%c",letter[2]);
			ab_control(letter, end);
			//for (k = 0; k < end; k++)  ///////////////////////////////////////
			//	printf("%c",letter[k]);
			end++;

		}

		for (num = 1; num <= r; num++){  //總猜題次數
			if (level < 15){
				printf("\n第%d次猜題(剩餘%d次機會)，請猜一個四位數。", num, r-num+1);  //顯示出第幾次猜題
				fflush(stdout);  //使得printf可以在scanf前顯示
				scanf("%d",&enter);  //數入四位整數

				guess[3] = enter%10;  //分離出個位存到guess
				guess[2] = (enter%100)/10;  //分離出十位存到guess
				guess[1] = (enter%1000)/100;  //分離出百位存到guess
				guess[0] = enter/1000;  //分離出千位存到guess

				for (q=0; q<4; q++){  //以答案亂數對應輸入的四位數(千位answer[2],百位answer[3],十位answer[4],個位answer[5])
					if (hint >= 2){
						if (guess[0] == 0 && guess[1] == 0 && guess[2] == 0 && guess[3] == 0){
							hint -= 2;
							printf("\n剩餘hint:%d\n",hint);
							while (1) {
								hintx = (rand()%4);
								//printf("hintx=%d hinty=%d", hintx, hinty[hintx]);
								if (hinty[hintx] != 1)
									break;
							}
							printf("第%d個為%d", hintx+1, answer[hintx+2] );
							hinty[hintx]++;
							num--;
							break;
						}
					}
					s=0;  //
					if (answer[q+2] == guess[q]) {  //判斷有幾A
						a++;  //A加一
						if (level < 8)  //判斷第七關(含)以前，
							printf("A為%d\n",answer[q+2]);  //顯示出A為哪一個
						s=4;  //使不執行以下for迴圈
					}
					for (; s<4; s++){  //(千位guess[0],百位guess[1],十位guess[2],個位guess[3])
						if (s == q) s++;  //使不與A重複判斷
						if (answer[q+2] == guess[s]){  //判斷有幾B
							b++;  //B加一
							s=4;  //使跳出for迴圈
						}
					}
				}
				if (!(guess[0] == 0 && guess[1] == 0 && guess[2] == 0 && guess[3] == 0))
					printf("%dA%dB",a,b);  //顯示出幾A幾B
			}
			else{
				r = 12;
				printf("\n第%d次猜題(剩餘%d次機會)，請猜%d個字母。",num, r-num+1, end-1);
				fflush(stdout);
				scanf("%s", letter_in);
				//printf("%s\n",letter_in);  //(方便調整)
				for (q=0; q<4; q++){
					if (hint >= 2){
						if (letter_in[0] == '0' && letter_in[1] == '0' && letter_in[2] == '0' && letter_in[3] == '0'){
							hint -= 2;
							printf("\n剩餘hint:%d\n",hint);
							while (1) {
								//printf("end = %d", end);
								hintx = rand()%(end-1);
								//printf("hintx=%d hinty=%d", hintx, hinty[hintx]);
								if (hinty[hintx] != 1)
									break;
							}
							printf("第%d個為%c", hintx+1, letter[hintx] );
							hinty[hintx]++;
							num--;
							break;
						}
					}
					s=0;
					if (letter[q] == letter_in[q]) {
						a++;
						printf("A為%c\n",letter[q]);
						s=4;
					}
					for (; s<4; s++){  //(千位guess[0],百位guess[1],十位guess[2],個位guess[3])
						if (s == q) s++;  //使不與A重複判斷
						if (letter[q] == letter_in[s]){  //判斷有幾B
							b++;  //B加一
							s=4;  //使跳出for迴圈
						}
					}
				}
				if (!(letter_in[0] == '0' && letter_in[1] == '0' && letter_in[2] == '0' && letter_in[3] == '0'))
					printf("%dA%dB",a,b);  //顯示出幾A幾B
			}

			if (a == 4){  //判斷是否有四個A
				if (num <= r-2)
					hint++;
				printf("\n\n你贏了！");  //顯示勝利
				fflush(stdout);
				if (level == 20)  //全過則跳出
					break;

				printf("\n*bonus*");
				kind = rand()%7;  //13
				x0 = (rand()%900)+100;
				y0 = (rand()%900)+100;

				switch (kind){
				case 0:
					z0 = add(x0, y0);
					my_math("加法", x0, y0, '+', z0);
					break;
				case 1:
					z0 =minus(x0, y0);
					my_math("減法", x0, y0, '-', z0);
					break;
				case 2:
					z0 =multiply(x0, y0);
					my_math("乘法", x0, y0, '*', z0);
					break;
				case 3:
					x4 = (rand()%9000)+100;
					y4 = (rand()%97)+3;
					z0 =divide(x4, y4);
					my_math("除法(無條件捨去到整數位)", x4, y4, '/', z0);
					break;
				case 4:
					equal_difference( &a1,  &d1,  &n1, &an1, &sn1);
					//printf("a1=%d d=%d n=%d an=%d sn=%.1f\n", a1, d1, n1, an1, sn1);
					printf("\n等差數列a1=%d，d=%d，n=%d。求an及sn(記得寫到小數點第一位):", a1, d1, n1);
					fflush(stdout);
					scanf("%d %f",&ans_an1,&ans_sn1);
					if (ans_an1 == an1 && ans_sn1 == sn1){
						printf("\n答對了");
						hint++;
					}
					else
						printf("錯誤");
					break;
				case 5:
					factorial();
					break;
				case 6:
					boy_girl();
					break;
				}

				printf("\n是否繼續下一關?\n是 請按y\n否 請按n");  //顯示是否繼續下一關
				fflush(stdout);  //使得printf可以在scanf前顯示
				scanf(" %c",&ro);  //輸入英文y或n
				//printf("ro = %c\n", ro);
				//fflush(stdout);
				if (ro == 'n')  //判斷y或n
					out += 1 ;  //out加一
				break;  //跳出迴圈
			}
			if (num == r){  //判斷回答次數是否等於猜題數
				level--;  //這一關沒過
				printf("\n\n挑戰失敗");  //顯示失敗
				printf("\n答案為");  //顯示答案
				if (level < 14){
					for (i=2; i<6;i++)  //從2遞增到5
						printf("%d" , answer[i] );  //顯示答案亂數(千位answer[2],百位answer[3],十位answer[4],個位answer[5])
				}
				else{
					for (i=0; i<4;i++)
						printf("%c" , letter[i] );
				}



				fflush(stdout);  //使得printf正確顯示
				if (hint >= 5){
					printf("\n請問是否復活(hint-5)? (y/n)");
					fflush(stdout);
					scanf(" %c",&ro1);
					if (ro1 == 'y'){
						hint -= 5;
						out--;
						r++;
						num = r + 1;
					}
					//printf("%d",hint);
				}
				out++;  //out加一
			}
			a = 0;  //A數重置
			b = 0;  //B數重置
		}
		if (out == 1)  //判斷OUT是否為1
			break ;  //是的話跳出關卡迴圈
		r--;  //猜題數減一
		if (level == 7)  //判斷是否通過第五關
			r = 10;  //第六關猜題數回到10
		else if (level == 14)
			r = 12;
	}
	if (level == 21)  //總共20關
		level--;
	printf("\n共通過%d關\n",level);  //共通過關卡數
	if (level == 20){  //判斷是否全過
		printf("\n恭喜全部通關!!!");
	}
	else {  //沒全過的話
		printf("\ngame over\n");  //遊戲結束
		fflush(stdout);  //使得printf正確顯示
	}
	ranking(level);
	return 0 ;  //回傳0
}

