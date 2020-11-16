#include <iostream>
#include <vector>
#include <string>
#include <string.h>
#include <fstream>
#include <algorithm>
#include <conio.h>
#include <iomanip>
#include <stdlib.h>
#include <windows.h>
#include <time.h>

using namespace std;

struct user_data{

    int number;  /*系統總使用人數*/
    string name;  /*使用者名稱*/
    string account;  /*使用者帳號*/
    string password;  /*使用者密碼*/
    int login_times;  /*登入次數*/
    int xaxb[2];  /*xaxb輸贏次數 xaxb[0](贏) xaxb[1](輸)*/
    int sudoku[2];  /*數獨輸贏次數 sudoku[0](贏) sudoku[1](輸)*/

};

struct msg_data{

    string user_name;  /*使用者名稱*/
    string message;  /*留言*/

};

string setmeal_data[10] = {"", "Big Mac", "Double Cheeseburger", "Angus Beef Burger"
                            , "Grilled BBQ Chicken Burger", "McChicken", "Chicken McNuggets"
                            , "Spicy Chicken Filet Burger", "Pork Burger with Cheese Sauce", "Filet-O-Fish"};

int setmeal_price[10] = {0, 122, 112, 149, 132, 99, 109, 122, 102, 99};

string drink[10] = {"", "black tea(hot)", "coca-cola", "coca-cola zero", "sprite"
                    , "black tea lemon(cold)", "black tea no-sugar(cold)"
                    , "green tea no-sugar(cold)", "milk tea(cold)", "milk tea(hot)"};

string other[10] = {"", "up size french fries", "up size drink", "up size hamburger"
                    , "add apple pie", "add chicken nuggets", "add hash browns"
                    , "add salad", "add corn soup", "add ice cream"};

int other_price[10] = {0, 15, 10, 20, 29, 39, 29, 39, 39, 15};

struct order_data{

    int mealno;
    int orderno;
    string name;  /*使用者名稱*/
    int setmeal_quantity[10];  /*各主餐數量*/
    int drink_quantity[10];  /*各飲料數量*/
    int other_quantity[10];  /*加點數量*/

};

/*讀取使用者資料庫*/
void read_user_data(vector<user_data> &data);

/*登入*/
void login(vector<user_data> data);

/*註冊*/
void registers(vector<user_data> &data, user_data &current);

/*儲存至memberlist.txt*/
void save_user_data(vector<user_data> &data);

/*顯示主畫面*/
void display(vector<user_data> &data, user_data current);

/*UI處理*/
int MainUI(int choice, user_data current);

/*顯示UI*/
void printUI(int choice, user_data current);

/*訂餐*/
void order(user_data current);
void order_ui(user_data current, order_data &current_order);
void print_order(user_data current, char left[], char right[], int step, order_data current_order);
/*儲存至orderlist.txt*/
void save_order_data(user_data current, order_data current_order);

void get_orders(vector<order_data> &orders, bool &check);
/*查訂單*/
void check_order(user_data current);

/*修改會員資料*/
void modify_user_data(vector<user_data> data, user_data &current);

/*寂寞聊天室*/
void silent_chatroom(user_data current);

/*顯示聊天室*/
void print_chatroom(user_data current, vector<msg_data> msg);

/*玩數獨*/
void play_sudoku(user_data &current);
void ui_sudoku(int data[][9], char left[][9], char right[][9]);
void print_sudoku(int data[][9], char left[][9], char right[][9]);
void get_answer(int count, int data[][9], int answer[][9], user_data &current);
bool right_place(int count, int answer[][9]);

/*猜數字*/
void play_xaxb(user_data &current);
int check_xaxb(int n);
int XAXB(int g,int a);
int input_xaxb();

/*店家登入*/
void McDonald(vector<user_data> data);
bool print_nextorder(vector<user_data> data, int &total, int total_price);
void save_nextorder(vector<user_data> data);
/*店家營收累計*/
int price_nextorder(int total);

/*查詢個人資料*/
void personal_information(user_data current);

/*查詢歷史訂單*/
void order_history(user_data current);


int main()
{
    vector<user_data> data;
    user_data current;

    cout << "歡迎蒞臨麥當勞線上系統\n\n\n";

    read_user_data(data);  /*讀取使用者資料庫*/

    login(data);  /*登入*/

    return 0;
}

/*讀取使用者資料庫*/
void read_user_data(vector<user_data> &data)
{
    ofstream outFile("memberlist.txt", ios::app);  /*如果無memberlist.txt檔案，則新增memberlist.txt*/
    outFile.close();

    user_data input;
    ifstream inFile("memberlist.txt", ios::in);
    if (!inFile){
        cout << "memberlist.txt開啟失敗";
        return;
    }

    while(inFile >> input.number >> input.name >> input.account >> input.password >> input.login_times
            >> input.xaxb[0] >> input.xaxb[1] >> input.sudoku[0] >> input.sudoku[1]){
        data.push_back(input);  /*讀取memberlist.txt，將資料存入data*/
    }
    inFile.close();
}

/*登入*/
void login(vector<user_data> data)
{
start:
    user_data current;
    string account, correct_password, password;
    bool check;  /*檢查帳號及密碼是否合法*/
    int a;
    char input;

    cout << "★★★歡迎進入登錄系統★★★\n\n";
    cout << "請輸入帳號(限定4~16碼、數字、大小寫英文、底線'_')\n如果需要註冊請輸入register\n如果為店家登入請輸入McDonald\n";
    do{
        cout << ": ";
        cin >> account;
        cout << endl;

        if (account == "register"){
            registers(data, current);  /*註冊*/
            break;
        }
        else if (account == "McDonald"){
            McDonald(data);  /*店家登入*/
            system("cls");
            goto start;
        }

        check = true;
        if (account.size()<4 || account.size()>16)  /*判斷帳號是否為4~16碼*/
            check = false;

        for(a=0; a<account.size(); a++){  /*判斷帳號是否為數字、大小寫英文及底線*/
            if (!isalpha(account[a]) && !isdigit(account[a]) && account[a]!='_'){
                check = false;
                break;
            }
        }

        for(a=0; a<data.size(); a++){  /*判斷帳號是否存在*/
            if (account == data[a].account){
                current = data[a];
                break;
            }
        }
        if (a==data.size())
            check = false;

        if (check){
            cout << "請輸入密碼(限定4~10碼、數字、大小寫英文、底線'_')\n";
            do{
                check = true;
                password = "";
                cout << ": ";
                do{
                    input = getch();
                    if (input == '\r')
                        break;

                    cout << "*";  /*防盜(密碼*字號顯示)*/
                    password += input;
                }
                while(1);
                cout << "\n\n";

                if (password.size()<4 || password.size()>10)  /*判斷密碼是否為4~10碼*/
                    check = false;

                for(a=0; a<password.size(); a++){  /*判斷密碼是否為數字、大小寫英文及底線*/
                    if (!isalpha(password[a]) && !isdigit(password[a]) && password[a]!='_'){
                        check = false;
                        break;
                    }
                }

                if (password != current.password)  /*判斷密碼是否正確*/
                    check = false;

                if (check){
                    cout << "已登錄！歡迎您！\n\n";
                    current.login_times++;
                    break;
                }
                else{
                    cout << "密碼輸入錯誤！請重新輸入\n";
                    continue;
                }
            }
            while(1);
            break;
        }
        else{
            cout << "帳號輸入錯誤！請重新輸入\n";
            continue;
        }
    }
    while(1);

    Sleep(1000);  /*暫停1秒*/
    display(data, current);  /*顯示主畫面*/
}

/*註冊*/
void registers(vector<user_data> &data, user_data &current)
{
    bool check;
    int a;
    char input;
    string double_check;

    cout << "★★★歡迎進入註冊系統★★★\n\n";

    current.number = data.size()+1;
    current.login_times = 1;
    current.xaxb[0] = 0;
    current.xaxb[1] = 0;
    current.sudoku[0] = 0;
    current.sudoku[1] = 0;

    cout << "請輸入帳號(限定4~16碼、數字、大小寫英文、底線'_')\n";
    do{
        cout << ": ";
        cin >> current.account;
        cout << endl;

        check = true;
        if (current.account.size()<4 || current.account.size()>16)  /*判斷帳號是否為4~16碼*/
            check = false;

        for(a=0; a<current.account.size(); a++){  /*判斷帳號是否為數字、大小寫英文及底線*/
            if (!isalpha(current.account[a]) && !isdigit(current.account[a]) && current.account[a]!='_'){
                check = false;
                break;
            }
        }

        for(a=0; a<data.size(); a++){  /*判斷帳號是否存在*/
            if (current.account == data[a].account){
                check = false;
                break;
            }
        }

        if (check){
            cout << "請輸入名稱\n: ";
            cin >> current.name;
            cout << endl;

            cout << "請輸入密碼(限定4~10碼、數字、大小寫英文、底線'_')\n";
            do{
                check = true;
                current.password = "";
                cout << ": ";
                do{
                    input = getch();
                    if (input == '\r')
                        break;

                    cout << "*";  /*防盜(密碼*字號顯示)*/
                    current.password += input;
                }
                while(1);
                cout << "\n\n";

                if (current.password.size()<4 || current.password.size()>10)  /*判斷密碼是否為4~10碼*/
                    check = false;

                for(a=0; a<current.password.size(); a++){  /*判斷密碼是否為數字、大小寫英文及底線*/
                    if (!isalpha(current.password[a]) && !isdigit(current.password[a]) && current.password[a]!='_'){
                        check = false;
                        break;
                    }
                }

                if (check){
                    cout << "請再次輸入密碼\n: ";
                    double_check = "";
                    do{
                        input = getch();
                        if (input == '\r')
                            break;

                        cout << "*";
                        double_check += input;
                    }
                    while(1);
                    cout << "\n\n";

                    if (current.password != double_check){
                        cout << "密碼輸入錯誤！請重新輸入\n";
                        continue;
                    }

                    data.push_back(current);
                    cout << "已完成註冊！\n";
                    break;
                }
                else{
                    cout << "密碼輸入不合法！請重新輸入\n";
                    continue;
                }
            }
            while(1);
            break;
        }
        else{
            cout << "帳號輸入不合法或帳號已存在！請重新輸入\n";
            continue;
        }
    }
    while(1);

    for(a=0; a<data.size(); a++)
        data[a].number = current.number;
    save_user_data(data);  /*儲存至memberlist.txt*/
}

/*儲存至memberlist.txt*/
void save_user_data(vector<user_data> &data)
{
    int a;
    ofstream outFile("memberlist.txt", ios::out);

    for(a=0; a<data.size(); a++){
        outFile << data[a].number << " " << data[a].name << " " << data[a].account << " "
            << data[a].password << " " << data[a].login_times << " " << data[a].xaxb[0] << " "
            << data[a].xaxb[1] << " " << data[a].sudoku[0] << " " << data[a].sudoku[1] << endl;
    }
    outFile.close();
}

/*顯示主畫面*/
void display(vector<user_data> &data, user_data current)
{
    int a, choice=1;

    do{
		choice = MainUI(choice, current);
        Sleep(1000);  /*暫停1秒*/
        system("cls");

		switch(choice){
			case 1:
				order(current);  /*訂餐*/
				break;
			case 2:
				check_order(current);  /*查訂單*/
				break;
			case 3:
				modify_user_data(data, current);  /*修改會員資料*/
				break;
			case 4:
				silent_chatroom(current);  /*寂寞聊天室*/
				break;
			case 5:
				play_sudoku(current);  /*玩數獨*/
				break;
			case 6:
				play_xaxb(current);  /*猜數字*/
				break;
            case 7:
                personal_information(current);  /*查詢個人資料*/
                break;
            case 8:
                order_history(current);  /*查詢歷史訂單*/
                break;
			default:
				break;
		}
	}
	while(choice!=0);


    for(a=0; a<data.size(); a++){
        if (data[a].account == current.account)
            data[a] = current;
    }
    save_user_data(data);  /*儲存至memberlist.txt*/
}

/*UI處理*/
int MainUI(int choice, user_data current)
{
    char c, c1;
    do{
		printUI(choice, current);

		c = getch();
		if (c == -32){
			c1 = getch();
			if (c1 == 72)
				choice = (choice+8)%9;
			if (c1 == 80)
				choice = (choice+1)%9;
			if (c1 == 77)
				c = 13;
		}
		if (c>='0' && c<='8')
			choice = c-'0';
		if (c == 0)
			c1 = getch();
	}
	while(c != 13);

	return choice;
}

/*顯示UI*/
void printUI(int choice, user_data current)
{
    int a;
    char left[9],right[9];

    system("cls");

    cout << "\n\n";
    cout << setw(22) << " " << "╔═══╗   ╔═══╗\n";
    cout << setw(20) << " " << "╔═╝ ■╚═╦═╝ ■╚═╗\n";
    cout << setw(20) << " " << "║ ■╥ ■║ ■╥ ■║\n";
    cout << setw(18) << " " << "╔═╝ ■║ ■╨ ■║ ■╚═╗\n";
    cout << setw(18) << " " << "║ ■╔═╩═╗ ■╔═╩═╗ ■║\n";
    cout << setw(18) << " " << "║ ■║   ║ ■║   ║ ■║\n";
    cout << setw(18) << "" << "╚═══╝   ╚═══╝   ╚═══╝\n\n\n\n";

    cout << setw(18) << " " << current.name << "您好，您已登入第" << current.login_times << "次\n\n";
    cout << setw(18) << " " << "★★★歡迎進入麥當勞主系統★★★\n\n";
    for(a=0; a<100; a++)
        cout << "=";
    cout << endl;

    for(a=0; a<9; a++){
		left[a] = ' ';
		right[a] = ' ';
	}
    left[choice]='[';
	right[choice]=']';

    cout << setw(18) << " " << left[1] << "1" << right[1] << " Order" << endl;
	cout << setw(18) << " " << left[2] << "2" << right[2] << " 查訂單" << endl;
	cout << setw(18) << " " << left[3] << "3" << right[3] << " 修改會員資料" << endl;
	cout << setw(18) << " " << left[4] << "4" << right[4] << " 聊天室" << endl;
	cout << setw(18) << " " << left[5] << "5" << right[5] << " 數獨遊戲" << endl;
	cout << setw(18) << " " << left[6] << "6" << right[6] << " 猜數字" << endl;
	cout << setw(18) << " " << left[7] << "7" << right[7] << " 查詢個人資料" << endl;
	cout << setw(18) << " " << left[8] << "8" << right[8] << " 查詢歷史訂單" << endl;
	cout << setw(18) << " " << left[0] << "0" << right[0] << " 離開系統" << endl;

    for(a=0; a<100; a++)
        cout << "=";
}

/*訂餐*/
void order(user_data current)
{
    order_data current_order;
    int a;

    for(a=0; a<=10; a++){
        current_order.setmeal_quantity[a] = 0;
        current_order.drink_quantity[a] = 0;
        current_order.other_quantity[a] = 0;
    }

    order_ui(current, current_order);

    system("cls");
    cout << "已完成order!可在查訂單處查詢!\n\n";
    system("pause");

    current_order.name = current.name;
    save_order_data(current, current_order);  /*儲存至orderlist.txt*/
}

void order_ui(user_data current, order_data &current_order)
{
    char c, c1;
    int a, step;
    int control=0, num;
    char left[9], right[9];

    for(a=0; a<9; a++){
        left[a] = ' ';
        right[a] = ' ';
    }

    for(step=1; step<=3; step++){

        do{

            cout << endl;
            left[control] = '[';
            right[control] = ']';

            print_order(current, left, right, step, current_order);


            c = getch();
            cout << c;
            if (c == -32){
                left[control] = ' ';
                right[control] = ' ';

                c1 = getch();

                if (c1 ==  72)
                    control--;
                else if (c1 == 80)
                    control++;

                if (control < 0)
                    control += 9;
                else if (control > 8)
                    control -= 9;

            }
            else if (c>='0' && c<='9'){
                num = c-'0';
                if (step == 1)
                    current_order.setmeal_quantity[control+1] = num;
                else if (step == 2)
                    current_order.drink_quantity[control+1] = num;
                else
                    current_order.other_quantity[control+1] = num;
            }

            if (c == 0)
                c1 = getch();
        }
        while(c!=13);

        left[control] = ' ';
        right[control] = ' ';
        control = 0;
    }
}

void print_order(user_data current, char left[], char right[], int step, order_data current_order)
{
    int a;

    system("cls");

    cout << "★★★歡迎進入點餐\系統★★★\n\n";
    for(a=0; a<100; a++)
        cout << "=";
    cout << "\n\n";

    if (step == 1){
        for(a=1; a<=9; a++){
            cout << setw(20) << a << "號餐\  " << setw(30) << setmeal_data[a] << "\t$" << setw(4)
             << setmeal_price[a] << "\t\t" << "數量: " << left[a-1] << current_order.setmeal_quantity[a]
             << right[a-1] << endl;
        }
    }
    else if (step == 2){
        for(a=1; a<=9; a++){
            cout << setw(20) << a << "." << setw(30) << drink[a] << "\t$" << setw(4)
             << 33 << "\t\t" << "數量: " << left[a-1] << current_order.drink_quantity[a]
             << right[a-1] << endl;
        }
    }
    else{
        for(a=1; a<=9; a++){
            cout << setw(20) << a << "." << setw(30) << other[a] << "\t$" << setw(4)
             << other_price[a] << "\t\t" << "數量: " << left[a-1] << current_order.other_quantity[a]
             << right[a-1] << endl;
        }
    }



    for(a=0; a<100; a++)
        cout << "=";
    cout << "\n\n";

}

/*儲存至orderlist.txt*/
void save_order_data(user_data current, order_data current_order)
{
    vector<order_data> orders;
    order_data input;
    int a, b;
    bool check=false;

    ofstream outFile("orderlist.txt", ios::app);
    outFile.close();

    get_orders(orders, check);

    if (check){
        current_order.mealno = orders[0].mealno;
        current_order.orderno = orders[0].orderno+1;
    }
    else{
        current_order.mealno = 0;
        current_order.orderno = 1;
    }

    for(a=0; a<orders.size(); a++)
        orders[a].orderno++;
    orders.push_back(current_order);

    ofstream outFile2("orderlist.txt", ios::out);

    for(a=0; a<orders.size(); a++){
        outFile2 << orders[a].mealno << " " << orders[a].orderno << " " << orders[a].name;
        for(b=0; b<=9; b++)
            outFile2 << " " << orders[a].setmeal_quantity[b];
        for(b=0; b<=9; b++)
            outFile2 << " " << orders[a].drink_quantity[b];
        for(b=0; b<=9; b++)
            outFile2 << " " << orders[a].other_quantity[b];
        outFile2 << endl;
    }
    outFile2.close();
}

void get_orders(vector<order_data> &orders, bool &check)
{
    order_data input;
    int a;

    ifstream inFile("orderlist.txt", ios::in);

    while(inFile >> input.mealno){

        check = true;

        inFile >> input.orderno;
        inFile >> input.name;
        for(a=0; a<=9; a++)
            inFile >> input.setmeal_quantity[a];
        for(a=0; a<=9; a++)
            inFile >> input.drink_quantity[a];
        for(a=0; a<=9; a++)
            inFile >> input.other_quantity[a];

        orders.push_back(input);
    }
    inFile.close();
}

/*查訂單*/
void check_order(user_data current)
{
    vector<order_data> orders;
    int a, b, total, count=0;
    bool check=false;

    get_orders(orders, check);

    cout << current.name << "您好:\n";
    cout << "以下是您的訂單:\n";

    for(a=0; a<100; a++)
        cout << "=";
    cout << "\n\n";

    cout << setw(30) << "品項" << setw(10) << "數量" << setw(12) << "價格\n\n";

    for(a=0; a<orders.size(); a++){

        total = 0;
        if (current.name == orders[a].name && a>=orders[a].mealno){

            count++;
            for(b=1; b<=9; b++){
                if (orders[a].setmeal_quantity[b] != 0){
                    cout << setw(30) << setmeal_data[b] << setw(10) << orders[a].setmeal_quantity[b] << setw(10) << setmeal_price[b]*orders[a].setmeal_quantity[b] << endl;
                    total += setmeal_price[b]*orders[a].setmeal_quantity[b];
                }
            }

            for(b=1; b<=9; b++){
                if (orders[a].drink_quantity[b] != 0){
                    cout << setw(30) << drink[b] << setw(10) << orders[a].drink_quantity[b] << setw(10) << 33*orders[a].drink_quantity[b] << endl;
                    total += 33*orders[a].drink_quantity[b];
                }
            }

            for(b=1; b<=9; b++){
                if (orders[a].other_quantity[b] != 0){
                    cout << setw(30) << other[b] << setw(10) << orders[a].other_quantity[b] << setw(10) << other_price[b]*orders[a].other_quantity[b] << endl;
                    other_price[b]*orders[a].other_quantity[b];
                }
            }
            cout << "\n\n" << setw(30) << "total price: " << total << endl;
            for(b=0; b<100; b++)
                cout << "=";
            cout << "\n\n";
        }
    }

    if (!count){
        for(a=0; a<100; a++)
            cout << "=";
        cout << "\n\n";
        cout << "查無訂單!\n\n";
    }

    system("pause");
}

/*修改會員資料*/
void modify_user_data(vector<user_data> data, user_data &current)
{
    string in, double_check;
    char input;
    bool check;
    int a;

    cout << "請輸入舊密碼\n: ";
    do{
        check = true;
        in = "";
        cout << ": ";
        do{
            input = getch();
            if (input == '\r')
                break;

            cout << "*";  /*防盜(密碼*字號顯示)*/
            in += input;
        }
        while(1);
        cout << "\n\n";

        if (in == current.password)
            break;
        else{
            cout << "密碼輸入錯誤！請重新輸入！\n";
        }
    }
    while(1);

    cout << "請輸入新密碼(限定4~10碼、數字、大小寫英文、底線'_')\n";
    do{
        check = true;
        current.password = "";
        cout << ": ";
        do{
            input = getch();
            if (input == '\r')
                break;

            cout << "*";  /*防盜(密碼*字號顯示)*/
            current.password += input;
        }
        while(1);
        cout << "\n\n";

        if (current.password.size()<4 || current.password.size()>10)  /*判斷密碼是否為4~10碼*/
            check = false;

        for(a=0; a<current.password.size(); a++){  /*判斷密碼是否為數字、大小寫英文及底線*/
            if (!isalpha(current.password[a]) && !isdigit(current.password[a]) && current.password[a]!='_'){
                check = false;
                break;
            }
        }

        if (check){
            cout << "請再次輸入密碼\n: ";
            double_check = "";
            do{
                input = getch();
                if (input == '\r')
                    break;

                cout << "*";
                double_check += input;
            }
            while(1);
            cout << "\n\n";

            if (current.password != double_check){
                cout << "密碼輸入錯誤！請重新輸入\n";
                continue;
            }

            data.push_back(current);
            cout << "密碼修改完成！\n";
            system("pause");
            break;
        }
        else{
            cout << "密碼輸入不合法！請重新輸入\n";
            continue;
        }
    }
    while(1);

}

/*寂寞聊天室*/
void silent_chatroom(user_data current)
{
    vector<msg_data> msg;
    msg_data input, leave_message;
    int a;

    ofstream outFile("msg.txt", ios::app);
    outFile.close();

    ifstream inFile("msg.txt", ios::in);
    while(inFile >> input.user_name >> input.message)
        msg.push_back(input);
    inFile.close();

    leave_message.user_name = current.name;
    while(1){
        print_chatroom(current, msg);

        cin >> leave_message.message;
        if (leave_message.message == "leave")
            break;
        else{
            msg.push_back(leave_message);
        }

        system("cls");
    }

    ofstream outFile2("msg.txt", ios::out);
    for(a=0; a<msg.size(); a++)
        outFile2 << msg[a].user_name << " " << msg[a].message << endl;
    outFile2.close();

}

/*顯示聊天室*/
void print_chatroom(user_data current, vector<msg_data> msg)
{
    int a;

    cout << setw(20) << " " << "★★★歡迎進入寂寞聊天室★★★\n\n";
    for(a=0; a<100; a++)
        cout << "=";
    cout << "\n\n";

    for(a=0; a<msg.size(); a++)
        cout << setw(20) << msg[a].user_name << ":  " << msg[a].message << endl;

    for(a=0; a<100; a++)
        cout << "=";
    cout << "\n\n";

    cout << "輸入leave離開\n";
    cout << current.name << ": ";

}

/*玩數獨*/
void play_sudoku(user_data &current)
{
    int data[9][9], data2[9][9], datacpy[9][9], datacpy2[9][9];
    char left[9][9], right[9][9];
    int  a, b, random;

    ifstream inFile("Q1-1.txt", ios::in);
    ifstream inFile2("Q2-1.txt", ios::in);
    for(a=0; a<9; a++){
        for(b=0; b<9; b++){
            inFile >> data[a][b];
            inFile2 >> data2[a][b];
            datacpy[a][b] = data[a][b];
            datacpy2[a][b] = data2[a][b];
            left[a][b] = ' ';
            right[a][b] = ' ';
        }
    }
    inFile.close();
    inFile2.close();

    srand(time(NULL));
    random = rand()%2;

    if (random){
        ui_sudoku(data, left, right);
        get_answer(0, data, datacpy, current);
    }
    else{
        ui_sudoku(data2, left, right);
        get_answer(0, data2, datacpy2, current);
    }

    system("pause");
}

void ui_sudoku(int data[][9], char left[][9], char right[][9])
{
    char c, c1;
    int control[2] = {0, 0};
    int num;

    do{
        cout << endl;

        left[control[0]][control[1]] = '[';
        right[control[0]][control[1]] = ']';

		print_sudoku(data, left, right);

		c = getch();
		cout << c;
		if (c == -32){
            left[control[0]][control[1]] = ' ';
            right[control[0]][control[1]] = ' ';

			c1 = getch();

			if (c1 ==  72)
				control[0]--;
			else if (c1 == 80)
				control[0]++;
            else if (c1 == 75)
                control[1]--;
            else if (c1 == 77)
                control[1]++;

            if (control[0] < 0)
                control[0] += 9;
            else if (control[0] > 8)
                control[0] -= 9;

            if (control[1] < 0)
                control[1] += 9;
            else if (control[1] > 8)
                control[1] -= 9;
		}
		else if (c>='0' && c<='9'){
			num = c-'0';
			if (data[control[0]][control[1]]==0 && num!=0)
                data[control[0]][control[1]] = num;
            if (num==0)
                data[control[0]][control[1]] = 0;
		}

		if (c == 0)
			c1 = getch();
	}
	while(c!=13);
}

void print_sudoku(int data[][9], char left[][9], char right[][9])
{
    int a, b;

    system("cls");

    for(a=0; a<9; a++){
        for(b=0; b<9; b++){
            cout << left[a][b];
            if (data[a][b] == 0)
                cout << "-";
            else
                cout << data[a][b];
            cout << right[a][b] << " ";
        }
        cout << endl;
    }
}

void get_answer(int count, int data[][9], int answer[][9], user_data &current)
{
    int times=0;

    for(int a=0; a<9; a++){
        for(int b=0; b<9; b++){
            if (answer[a][b] != 0)
                times++;
        }
    }
    if (count==81 && times==81){

        count = 0;
        cout << endl;

        for(int a=0; a<9; a++){
            for(int b=0; b<9; b++){
                cout << answer[a][b] << " ";
                if (data[a][b]-answer[a][b] == 0)
                    count++;
            }
            cout << endl;
        }

        if (count == 81){
            cout << "You win!!!\n";
            current.sudoku[0]++;
        }
        else{
            cout << "You lose!!!\n";
            current.sudoku[1]++;
        }

        return;
    }


    int row = count/9;
    int col = count%9;
    int a;

    if (answer[row][col] == 0){
        for(a=0; a<=9; a++){
            answer[row][col] = a;
            if (right_place(count, answer))
                get_answer(count+1, data, answer, current);
        }

        answer[row][col] = 0;
    }
    else
        get_answer(count+1, data, answer, current);
}

bool right_place(int count, int answer[][9])
{
    int row = count/9;
    int col = count%9;
    int a, b;
    int temprow = row/3*3;
    int tempcol = col/3*3;

    for(a=0; a<9; a++){
        if (answer[row][a]==answer[row][col] && a!=col)
            return false;
    }
    for(a=0; a<9; a++){
        if (answer[a][col]==answer[row][col] && a!=row)
            return false;
    }

    for(a=temprow; a<temprow+3; a++){
        for(b=tempcol; b<tempcol+3; b++){
            if (answer[a][b]==answer[row][col] && a!=row && b!=col)
                return false;
        }
    }

    return true;
}

/*猜數字*/
void play_xaxb(user_data &current)
{
    int ans, com_guess, user_guess;
    int P[10000];
    int i, AB1, AB2, j, AB3, q=0;

    cout << "Let's play a XAXB game.\n\n";
    cout << "You and the computer can take turns guessing a four-digit number, and you go first." << endl;
    cout << "First,input the answer you want:";
    cin >> ans;

    while (check_xaxb(ans) == 0){ /*後有定義 0即數字非四位數或有重複*/
        cout << "Type error!!!" << endl;
        cout << "Please input again:";
        cin >> ans;
    }

    system("cls");

    for(i=0;i<10000;i++){
        if (check_xaxb(i) == 1)
            P[i] = 1;
        else
            P[i] = 0;
    }

    do{
        if (AB3!=40){
            user_guess = input_xaxb();
            AB3 = XAXB(user_guess, ans);

            cout << AB3/10 << "A" << AB3%10 << "B" << endl;
            if (AB3==40 && AB1!=40){
                current.xaxb[0]++;
                cout << "\nYou win!!!" << endl;
            }
            if (AB3==40 && AB1==40)
                cout << "\nYou are right but since the computer guessed correctly before you, you lose." << endl;
            if (AB3==40 && AB1!=40)
                cout << "You win but you have to wait for the computer til it guesses correctly.\n\n";
        }

        if (AB1 != 40){
            for(i=0; i<10000; i++)
                if (P[i] == 1)
                    break;

            com_guess = i;
            cout << "computer guess:" << com_guess <<endl;
            AB1 = XAXB(com_guess, ans);
            cout << AB1/10 << "A" << AB1%10 << "B" << endl;

            for(i=0; i<10000; i++){
                if (P[i] == 1){
                    AB2 = XAXB(com_guess, i);
                    if (AB2 != AB1)
                        P[i] = 0;
                }
            }

            if (AB1==40 && AB3!=40){
                    current.xaxb[1]++;
                cout << "\nComputer wins!!!" << endl;
            }
            if (AB1==40 && AB3==40)
                cout << "\nComputer guesses correctly after you so computer loses." << endl;
            if (AB3!=40 && AB1==40)
                cout << "Computer wins but it has to wait for you until you guess correctly.\n\n";

        }
        if(AB1!=40 && AB3!=40)
            q++;
    }
    while(AB1!=40 || AB3!=40);

    cout << "The answer goes correctly at round " << q+1 << endl << endl;

    system("pause");
}

/* Check function will check the correctness of 4-digit number in XAXB
   1->OK 0->Wrong
*/
int check_xaxb(int n)
{
    int a,b,c,d;

    if(n<0 || n>=10000)
        return 0;

    a = n/1000;
    b = n%1000/100;
    c = n%100/10;
    d = n%10;

    if(a==b || a==c || a==d || b==c || b==d || c==d || a==0)
        return 0;
    return 1;
}

int XAXB(int g,int a)
{
    int A=0,B=0;
    int g1,g2,g3,g4,a1,a2,a3,a4;

    g1 = g/1000;
    g2 = g%1000/100;
    g3 = g%100/10;
    g4 = g%10;
    a1 = a/1000;
    a2 = a%1000/100;
    a3 = a%100/10;
    a4 = a%10;

    if (a1 == g1)
        A++;
    if (a2 == g2)
        A++;
    if (a3 == g3)
        A++;
    if (a4 == g4)
        A++;
    if (a1==g2 || a1==g3 || a1==g4)
        B++;
    if (a2==g1 || a2==g3 || a2==g4)
        B++;
    if (a3==g1 || a3==g2 || a3==g4)
        B++;
    if (a4==g1 || a4==g2 || a4==g3)
        B++;

    return A*10+B;
}

int input_xaxb()
{
    int guess;
    do{
        cout << "Please guess:";
        cin >> guess;
        if(check_xaxb(guess) == 0)
            cout << "Type error!!!!!!" << endl;
    }
    while(check_xaxb(guess)==0);

    return guess;
}

/*店家登入*/
void McDonald(vector<user_data> data)
{
    int total, total_price=0;
    char c, c1;

    do{
        if (print_nextorder(data, total, total_price));
        else
            break;

		c = getch();
		if (c == -32){

			c1 = getch();
			if (c1 == 81){
                total_price = price_nextorder(total);  /*店家營收累計*/
                save_nextorder(data);
			}
			else if (c1 == 73)
                return;

		}

	}
	while(1);
}

bool print_nextorder(vector<user_data> data, int &total, int total_price)
{
    system("cls");

    vector<order_data> orders;
    bool check=false;
    int a, b;

    total=0;
    get_orders(orders, check);

    if (orders[0].mealno >= orders[0].orderno){
        cout << "所有訂單已完成!\n\n";
        system("pause");
        return false;
    }

    cout << "待完成訂單:\n";
    cout << "顧客: " << orders[orders[0].mealno].name << endl;
    for(a=0; a<100; a++)
        cout << "=";
    cout << "\n\n";
    cout << setw(30) << "品項" << setw(10) << "數量" << setw(12) << "價格\n\n";

    for(b=1; b<=9; b++){
        if (orders[orders[0].mealno].setmeal_quantity[b] != 0){
            cout << setw(30) << setmeal_data[b] << setw(10) << orders[orders[0].mealno].setmeal_quantity[b] << setw(10) << setmeal_price[b]*orders[orders[0].mealno].setmeal_quantity[b] << endl;
            total += setmeal_price[b]*orders[orders[0].mealno].setmeal_quantity[b];
        }
    }

    for(b=1; b<=9; b++){
        if (orders[orders[0].mealno].drink_quantity[b] != 0){
            cout << setw(30) << drink[b] << setw(10) << orders[orders[0].mealno].drink_quantity[b] << setw(10) << 33*orders[orders[0].mealno].drink_quantity[b] << endl;
            total += 33*orders[orders[0].mealno].drink_quantity[b];
        }
    }

    for(b=1; b<=9; b++){
        if (orders[orders[0].mealno].other_quantity[b] != 0){
            cout << setw(30) << other[b] << setw(10) << orders[orders[0].mealno].other_quantity[b] << setw(10) << other_price[b]*orders[orders[0].mealno].other_quantity[b] << endl;
            other_price[b]*orders[orders[0].mealno].other_quantity[b];
        }
    }
    cout << "\n\n" << setw(30) << "total price: " << total << endl;

    for(b=0; b<100; b++)
        cout << "=";
    cout << "\n\n";

    cout << "店家營收累計: " << total_price << "元\n\n";

    cout << "按PgUp離開\n";
    cout << "按PgDn完成訂單\n";
}

void save_nextorder(vector<user_data> data)
{
    vector<order_data> orders;
    bool check=false;
    int a, b;

    get_orders(orders, check);

    for(a=0; a<orders.size(); a++){
        orders[a].mealno++;
    }

    ofstream outFile("orderlist.txt", ios::out);

    for(a=0; a<orders.size(); a++){
        outFile << orders[a].mealno << " " << orders[a].orderno << " " << orders[a].name;
        for(b=0; b<=9; b++)
            outFile << " " << orders[a].setmeal_quantity[b];
        for(b=0; b<=9; b++)
            outFile << " " << orders[a].drink_quantity[b];
        for(b=0; b<=9; b++)
            outFile << " " << orders[a].other_quantity[b];
        outFile << endl;
    }
    outFile.close();
}

/*店家營收累計*/
int price_nextorder(int total)
{
    int total_price;

    ifstream inFile("price.txt", ios::in);
    inFile >> total_price;
    inFile.close();

    total_price += total;

    ofstream outFile("price.txt", ios::out);
    outFile << total_price;
    outFile.close();

    return total_price;
}

/*查詢個人資料*/
void personal_information(user_data current)
{
    int a;

    system("cls");

    cout << "系統總使用人數為: " << current.number << "人\n\n";

    cout << "您的個人資料如下:\n";
    for(a=0; a<100; a++)
        cout << "=";
    cout << "\n\n";

    cout << setw(20) << " " << setw(15) << left << "姓名" << setw(15) << current.name << endl;
    cout << setw(20) << " " << setw(15) << left << "帳號" << setw(15) << current.account << endl;
    cout << setw(20) << " " << setw(15) << left << "登錄次數" << setw(15) << current.login_times << endl;
    cout << setw(20) << " " << setw(15) << left << "xaxb獲勝次數" << setw(15) << current.xaxb[0] << endl;
    cout << setw(20) << " " << setw(15) << left << "xaxb失敗次數" << setw(15) << current.xaxb[1] << endl;
    cout << setw(20) << " " << setw(15) << left << "數獨獲勝次數" << setw(15) << current.sudoku[0] << endl;
    cout << setw(20) << " " << setw(15) << left << "數獨失敗次數" << setw(15) << current.sudoku[1] << endl;

    for(a=0; a<100; a++)
        cout << "=";
    cout << "\n\n";

    system("pause");
}

/*查詢歷史訂單*/
void order_history(user_data current)
{
    vector<order_data> orders;
    int a, b, total, count=0;
    bool check=false;

    get_orders(orders, check);

    cout << current.name << "您好:\n";
    cout << "以下是您的歷史訂單:\n";

    for(a=0; a<100; a++)
        cout << "=";
    cout << "\n\n";

    cout << setw(30) << "品項" << setw(10) << "數量" << setw(12) << "價格\n\n";

    for(a=0; a<orders.size(); a++){

        total = 0;
        if (current.name == orders[a].name && a<orders[a].mealno){

            count++;
            for(b=1; b<=9; b++){
                if (orders[a].setmeal_quantity[b] != 0){
                    cout << setw(30) << setmeal_data[b] << setw(10) << orders[a].setmeal_quantity[b] << setw(10) << setmeal_price[b]*orders[a].setmeal_quantity[b] << endl;
                    total += setmeal_price[b]*orders[a].setmeal_quantity[b];
                }
            }

            for(b=1; b<=9; b++){
                if (orders[a].drink_quantity[b] != 0){
                    cout << setw(30) << drink[b] << setw(10) << orders[a].drink_quantity[b] << setw(10) << 33*orders[a].drink_quantity[b] << endl;
                    total += 33*orders[a].drink_quantity[b];
                }
            }

            for(b=1; b<=9; b++){
                if (orders[a].other_quantity[b] != 0){
                    cout << setw(30) << other[b] << setw(10) << orders[a].other_quantity[b] << setw(10) << other_price[b]*orders[a].other_quantity[b] << endl;
                    other_price[b]*orders[a].other_quantity[b];
                }
            }
            cout << "\n\n" << setw(30) << "total price: " << total << endl;
            for(b=0; b<100; b++)
                cout << "=";
            cout << "\n\n";
        }
    }

    if (!count){
        for(a=0; a<100; a++)
            cout << "=";
        cout << "\n\n";
        cout << "查無歷史訂單!\n\n";
    }

    system("pause");
}
