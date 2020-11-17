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

void boy_girl(void)  //�ƾǱƦC�D��
{
	int g,b,answer,d,totalg1 = 1,totalg2 = 1,totalb = 1,e;
	srand(time(NULL));

	do{
		g=(rand()%9)+1;
		b=(rand()%9)+1;
	}while(g>=b);

	printf("%d�k%d�k�ƶ��A�k�ͤ��۾F�A�@���X�رƪk? ",b,g);
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
		printf("\n����F!");
	}
	else
		printf("���~");

}
void ranking(int level)  //�Ʀ�]�A�i�x�s����
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
		printf("�L�k�}���ɮ�");
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
		printf("\n�п�J�z���W�r:");
		fflush(stdout);
		scanf("%s", name);
		nl[0].level =  level;
		strcpy(nl[0].name,name);
		idx++;
	}
	else{
		for(i = 0; i < idx+1; i++){
			if (level >= nl[i].level){
				printf("\n�п�J�z���W�r:");
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
			printf("\n�z�����Z�����H�ƤJ�e�Q�W");
	}
	if (idx == 10)
		idx--;

	if((fp = fopen(rank_file, "w")) == NULL)
		printf("�L�k�}���ɮ�");
	else{
		for(i = 0; i <= idx; i++){
			fprintf(fp, "%d %s\n", nl[i].level, nl[i].name);
		}
		fclose(fp);
	}

	printf("\n�Ʀ�]\n");
	for(i = 0; i <= idx; i++){
		printf("\n��%d�W�A�q�L%d��   %s", i+1, nl[i].level, nl[i].name);
	}

#if 0
	printf("\n�п�J�z���W�r:");
	fflush(stdout);
	scanf("%s", name);
	if((fp = fopen(rank_file, "r+")) == NULL)
		printf("�L�k�}���ɮ�");
	else{
		fprintf(fp, "%s  �@�q�L%d��",name, level);
		fclose(fp);
	}
#endif
}

void ab_control(char *first, int end)  //15����A�H���^��r��(�D�ت�����)
{
	char ynum[2];
	int i = 2;

	ynum[1]='\0';
again:
	ynum[0] = 'a' + rand()%26;
	if (strchr(first, ynum[0]) == NULL) {  //����ynum�a�J�@�Ӧr���A�P�_first(letter)�̭����S����ynum�@�˦r��
		strcat(first, ynum);  //�p�G�S���A�h�Nynum��first(letter)
		if (i++ < end)  //�P�_��������
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
		printf("\n����F!");
	}
	else
		printf("���~");
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
	printf("\n1~%d���A���X%d�Ӹ��X�@�ƦC�A�@���X�رƪk?", num6, amount6);
	fflush(stdout);
	scanf("%d",&guess6);
	for(r6 = 0; r6 < amount6; r6++){
		answer6 *= num6--;
	}
	if (guess6 == answer6){
		hint++;
		printf("\n����F!");
	}
	else
		printf("���~");
}


int main(void)
{

	int guess[4];  //��J��4���(�d��guess[0],�ʦ�guess[1],�Q��guess[2],�Ӧ�guess[3])
	int answer[6];  //4��üƤ��O�s�J�ܼ�(�d��answer[2],�ʦ�answer[3],�Q��answer[4],�Ӧ�answer[5])
	int q, s;  //�P�_�������ܼ�
	int i, k, o;  //���Ͷüƥ�
	int enter, num;  //   ��J��4���, ����
	int a, b;  //A B
	int xnum[3];  //���ͶüƥΪ��ܼ�(xnum[0],xnum[1],xnum[2])
	int level;
	int out=0; //���d�ƥ�
	char ro, ro1;  //�P�_�O�_�~��
	int r=10;  //�q�D��
	int hintx, hinty[10], hint1;
	int kind;
	int x0, y0, z0;  //�[�k
	int x4, y4;
	int a1, d1, n1, an1, ans_an1;  //���t
	float sn1, ans_sn1;  //���t
	char letter_in[5];  //2 3 4 5
	int end = 4;


	system("color f9");
	printf("                         ____________________________\n");
	printf("                         *�XA�XB�O�@�گu���������C��*\n");
	printf("                         ~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	printf("                                  �C���W�h:\n");
	printf("________________________________________________________________________________\n");
	printf("�t�η|�H�����ͤ@�ӥ|��(�Ʀr�B�r��)�A�p�G�A��J���|��(�Ʀr�B�r��)�P�t�β��ͪ��|��(�Ʀr�B�r��)�ۦP�B�]�ۦP��m�A�N�|��1A�A�p�G�ۦP(�Ʀr�B�r��)�����P��m�A�h�|��1B");
	printf("________________________________________________________________________________\n");
	system("pause");
	printf("                        *�t�β��ͪ�(�Ʀr�B�r��)���|����*\n");
	printf("________________________________________________________________________________\n");
	system("pause");
	printf("���C���@��20���A�e14�����q�Ʀr�A��1~7���i�q�D�ƨ̧Ǭ�10,9,8,7,6,5,4�A�|���A����m�C��8~14�����q�D�Ƥ]�O10,9,8,7,6,5,4�A�����|��ܥXA����m");
	printf("��15~20�����q�r��(�p�g)�A�i�q�D�Ƭ�12�A�|���A����m�C\n");
	printf("________________________________________________________________________________\n");
	system("pause");
	printf("                                  *hint!*\n");
	printf("________________________________________________________________________________\n");
	system("pause");
	printf("�C�L�@���A�|�i��@��bonus�Abonus����|��o�@��hint\n�p�G�b(�q�D��-2)�H�e�N����A�]�|��o1��hint");
	printf("\n�A�i�H��O2��hint����o1A(��J(�Ʀr�B�r��)�ɡA��J0000�Y�O�ϥ�1��hint)�A�]�i�H��5��hint�Ӵ_��\n");
	printf("________________________________________________________________________________\n");
	printf("\n�֨ӬD�Ԧۧڧa\n");

	fflush(stdout);
	system("pause");


	for (level = 15; level < 21; level++){  //���d��(20)

		a = 0;  //���m�ƭ�
		b = 0;  //���m�ƭ�
		o = 2;  //���m�ƭ�
		for (hint1=0; hint1<end; hint1++)  //���m�ƭ�
			hinty[hint1] = 0;

		printf("\nlevel %d\n",level);
		printf("\n�Ѿlhint:%d\n",hint);
		fflush(stdout);
		srand(time(NULL));

		if (level < 15){  //�e14��
			answer[2] = (rand()%9)+1 ;  //�üƤd���
			//printf("%d" , answer[2] );  //��ܶüƤd���(��K�վ�)///////////////////////////////
			answer[0] = 10;
			answer[1] = 10;

			for (k=0; k<3; k++){  //�ܼ�(�ʦ�0 �Q��1 �Ӧ�2)
				while (1){
					xnum[k] = rand()%10;  //�H�o���ܼ��x�s�ü�
					if (xnum[k] != answer[o]){  //�P�_�O�_����e�@�Ӷü�
						if (xnum[k] != answer[o-1]){  //�P�_�O�_����e��Ӷü�
							if (xnum[k] != answer[o-2]){  //�P�_�O�_����e�T�Ӷü�
								answer[o+1] =xnum[k];  //�p�G�o���ܼ�(xnum)��������e�����ܼơA�N��ȱa�J(answer)
								//printf("%d" , answer[o+1] );  //��ܶü�(��K�վ�)/////////////////////////////////////
								break;
							}
						}
					}
				}
				o++;  //�ü�(�ʦ�3 �Q��4 �Ӧ�5)
			}
		}
		else{  // 15����
			memset(letter, 0, 9);  //���m�ƭ�
			letter[0] = 'a' + rand()%26;
			//printf("%c",letter[2]);
			ab_control(letter, end);
			//for (k = 0; k < end; k++)  ///////////////////////////////////////
			//	printf("%c",letter[k]);
			end++;

		}

		for (num = 1; num <= r; num++){  //�`�q�D����
			if (level < 15){
				printf("\n��%d���q�D(�Ѿl%d�����|)�A�вq�@�ӥ|��ơC", num, r-num+1);  //��ܥX�ĴX���q�D
				fflush(stdout);  //�ϱoprintf�i�H�bscanf�e���
				scanf("%d",&enter);  //�ƤJ�|����

				guess[3] = enter%10;  //�����X�Ӧ�s��guess
				guess[2] = (enter%100)/10;  //�����X�Q��s��guess
				guess[1] = (enter%1000)/100;  //�����X�ʦ�s��guess
				guess[0] = enter/1000;  //�����X�d��s��guess

				for (q=0; q<4; q++){  //�H���׶üƹ�����J���|���(�d��answer[2],�ʦ�answer[3],�Q��answer[4],�Ӧ�answer[5])
					if (hint >= 2){
						if (guess[0] == 0 && guess[1] == 0 && guess[2] == 0 && guess[3] == 0){
							hint -= 2;
							printf("\n�Ѿlhint:%d\n",hint);
							while (1) {
								hintx = (rand()%4);
								//printf("hintx=%d hinty=%d", hintx, hinty[hintx]);
								if (hinty[hintx] != 1)
									break;
							}
							printf("��%d�Ӭ�%d", hintx+1, answer[hintx+2] );
							hinty[hintx]++;
							num--;
							break;
						}
					}
					s=0;  //
					if (answer[q+2] == guess[q]) {  //�P�_���XA
						a++;  //A�[�@
						if (level < 8)  //�P�_�ĤC��(�t)�H�e�A
							printf("A��%d\n",answer[q+2]);  //��ܥXA�����@��
						s=4;  //�Ϥ�����H�Ufor�j��
					}
					for (; s<4; s++){  //(�d��guess[0],�ʦ�guess[1],�Q��guess[2],�Ӧ�guess[3])
						if (s == q) s++;  //�Ϥ��PA���ƧP�_
						if (answer[q+2] == guess[s]){  //�P�_���XB
							b++;  //B�[�@
							s=4;  //�ϸ��Xfor�j��
						}
					}
				}
				if (!(guess[0] == 0 && guess[1] == 0 && guess[2] == 0 && guess[3] == 0))
					printf("%dA%dB",a,b);  //��ܥX�XA�XB
			}
			else{
				r = 12;
				printf("\n��%d���q�D(�Ѿl%d�����|)�A�вq%d�Ӧr���C",num, r-num+1, end-1);
				fflush(stdout);
				scanf("%s", letter_in);
				//printf("%s\n",letter_in);  //(��K�վ�)
				for (q=0; q<4; q++){
					if (hint >= 2){
						if (letter_in[0] == '0' && letter_in[1] == '0' && letter_in[2] == '0' && letter_in[3] == '0'){
							hint -= 2;
							printf("\n�Ѿlhint:%d\n",hint);
							while (1) {
								//printf("end = %d", end);
								hintx = rand()%(end-1);
								//printf("hintx=%d hinty=%d", hintx, hinty[hintx]);
								if (hinty[hintx] != 1)
									break;
							}
							printf("��%d�Ӭ�%c", hintx+1, letter[hintx] );
							hinty[hintx]++;
							num--;
							break;
						}
					}
					s=0;
					if (letter[q] == letter_in[q]) {
						a++;
						printf("A��%c\n",letter[q]);
						s=4;
					}
					for (; s<4; s++){  //(�d��guess[0],�ʦ�guess[1],�Q��guess[2],�Ӧ�guess[3])
						if (s == q) s++;  //�Ϥ��PA���ƧP�_
						if (letter[q] == letter_in[s]){  //�P�_���XB
							b++;  //B�[�@
							s=4;  //�ϸ��Xfor�j��
						}
					}
				}
				if (!(letter_in[0] == '0' && letter_in[1] == '0' && letter_in[2] == '0' && letter_in[3] == '0'))
					printf("%dA%dB",a,b);  //��ܥX�XA�XB
			}

			if (a == 4){  //�P�_�O�_���|��A
				if (num <= r-2)
					hint++;
				printf("\n\n�AĹ�F�I");  //��ܳӧQ
				fflush(stdout);
				if (level == 20)  //���L�h���X
					break;

				printf("\n*bonus*");
				kind = rand()%7;  //13
				x0 = (rand()%900)+100;
				y0 = (rand()%900)+100;

				switch (kind){
				case 0:
					z0 = add(x0, y0);
					my_math("�[�k", x0, y0, '+', z0);
					break;
				case 1:
					z0 =minus(x0, y0);
					my_math("��k", x0, y0, '-', z0);
					break;
				case 2:
					z0 =multiply(x0, y0);
					my_math("���k", x0, y0, '*', z0);
					break;
				case 3:
					x4 = (rand()%9000)+100;
					y4 = (rand()%97)+3;
					z0 =divide(x4, y4);
					my_math("���k(�L����˥h���Ʀ�)", x4, y4, '/', z0);
					break;
				case 4:
					equal_difference( &a1,  &d1,  &n1, &an1, &sn1);
					//printf("a1=%d d=%d n=%d an=%d sn=%.1f\n", a1, d1, n1, an1, sn1);
					printf("\n���t�ƦCa1=%d�Ad=%d�An=%d�C�Dan��sn(�O�o�g��p���I�Ĥ@��):", a1, d1, n1);
					fflush(stdout);
					scanf("%d %f",&ans_an1,&ans_sn1);
					if (ans_an1 == an1 && ans_sn1 == sn1){
						printf("\n����F");
						hint++;
					}
					else
						printf("���~");
					break;
				case 5:
					factorial();
					break;
				case 6:
					boy_girl();
					break;
				}

				printf("\n�O�_�~��U�@��?\n�O �Ы�y\n�_ �Ы�n");  //��ܬO�_�~��U�@��
				fflush(stdout);  //�ϱoprintf�i�H�bscanf�e���
				scanf(" %c",&ro);  //��J�^��y��n
				//printf("ro = %c\n", ro);
				//fflush(stdout);
				if (ro == 'n')  //�P�_y��n
					out += 1 ;  //out�[�@
				break;  //���X�j��
			}
			if (num == r){  //�P�_�^�����ƬO�_����q�D��
				level--;  //�o�@���S�L
				printf("\n\n�D�ԥ���");  //��ܥ���
				printf("\n���׬�");  //��ܵ���
				if (level < 14){
					for (i=2; i<6;i++)  //�q2���W��5
						printf("%d" , answer[i] );  //��ܵ��׶ü�(�d��answer[2],�ʦ�answer[3],�Q��answer[4],�Ӧ�answer[5])
				}
				else{
					for (i=0; i<4;i++)
						printf("%c" , letter[i] );
				}



				fflush(stdout);  //�ϱoprintf���T���
				if (hint >= 5){
					printf("\n�аݬO�_�_��(hint-5)? (y/n)");
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
				out++;  //out�[�@
			}
			a = 0;  //A�ƭ��m
			b = 0;  //B�ƭ��m
		}
		if (out == 1)  //�P�_OUT�O�_��1
			break ;  //�O���ܸ��X���d�j��
		r--;  //�q�D�ƴ�@
		if (level == 7)  //�P�_�O�_�q�L�Ĥ���
			r = 10;  //�Ĥ����q�D�Ʀ^��10
		else if (level == 14)
			r = 12;
	}
	if (level == 21)  //�`�@20��
		level--;
	printf("\n�@�q�L%d��\n",level);  //�@�q�L���d��
	if (level == 20){  //�P�_�O�_���L
		printf("\n���ߥ����q��!!!");
	}
	else {  //�S���L����
		printf("\ngame over\n");  //�C������
		fflush(stdout);  //�ϱoprintf���T���
	}
	ranking(level);
	return 0 ;  //�^��0
}

