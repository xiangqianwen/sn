// ConsoleApplication4.cpp : 定义控制台应用程序的入口点。
//

#include <Windows.h>
#pragma comment(lib,"Winmm.lib")
#include <conio.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include <time.h>
#include <conio.h>
#include <stdlib.h>
using namespace std;



                                                  //class UNIT
class Unit
{
public:
	const static int KLEFT = 2;
	const static int KUP = 2;
	const static int KWIDTH = 70;
	const static int KHEIGHT = 20;
	int m_iX;
	int m_iY;
	string m_cPic;
	Unit()
	{

	}
	Unit(int x, int y, string pic)
	{
	m_iX = x;
	m_iY = y;
	m_cPic= pic;
    }
	void show();
	void erase();
	static void gotoxy(int x, int y);
};


                                              //UNIT函数
void Unit::show()
{
	gotoxy(m_iX, m_iY);
	cout << m_cPic;
}
void Unit::erase()
{
	gotoxy(m_iX, m_iY);
	cout << " ";
}
void Unit::gotoxy(int m_iX, int m_iY)
{
	HANDLE screen = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD position;    // position 是一个 COORD 结构
	position.X = m_iX;
	position.Y = m_iY;
	//将光标放在那里，然后开始打印
	SetConsoleCursorPosition(screen, position);
}

                                              //用户选项
class choice:public Unit
{
public:
	int i;
	int j;
	int m;
	int n;
	void choice_show();
};
                                                //用户选项函数
void choice::choice_show()
{
	for (i = KLEFT; i <= KWIDTH; i++)
	{
		gotoxy(i, KUP);
		cout << "+";
	}
	for (j = KLEFT; j <= KWIDTH; j++)
	{
		gotoxy(j, KHEIGHT);
		cout << "+";
	}

	for (m = KUP; m <= KHEIGHT; m++)
	{
		gotoxy(KLEFT, m);
		cout << "+";
	}
	for (n = KUP; n <= KHEIGHT; n++)
	{
		gotoxy(KWIDTH, n);
		cout << "+";
	}

	gotoxy(30, 1);
	cout << "<<贪吃蛇游戏>>";
	gotoxy(5, 3);
	cout << "游戏规则:";
	gotoxy(5,5);
	cout << "吃一个食物得一分";
	gotoxy(5, 7);
	cout << "每吃到5个食物则过一关";
	gotoxy(5, 9);
	cout << "碰壁则死，蛇头碰到身体则死";
	gotoxy(5, 11);
	cout << "按回车键开始游戏";
}


                                             //class 框架
class draw:public Unit
{
public:
	int i;
	int j;
	int m;
	int n;
	int y;
	void show3();
};
                                             //框架函数
void draw::show3()
{
	gotoxy(30, 1);
	cout << "<<贪吃蛇游戏>>";
	gotoxy(9, 5);
	cout << "得分:";
	gotoxy(9, 10);
	cout << "第1关";
	for (i = KLEFT; i <= KWIDTH; i++)
	{
		gotoxy(i, KUP);
		cout << "+";
	}
	for (j = KLEFT; j <= KWIDTH; j++)
	{
		gotoxy(j, KHEIGHT);
		cout << "+";
	}

	for (m = KUP; m <= KHEIGHT; m++)
	{
		gotoxy(KLEFT,m );
		cout << "+";
	}
	for (n= KUP; n <= KHEIGHT; n++)
	{
		gotoxy(KWIDTH,n);
		cout << "+";
	}
	for (y = KUP; y <= KHEIGHT; y++)
	{
		gotoxy(KLEFT+20,y);
		cout << "+";
	}

}



                                                 //class 蛇类
class snake :public Unit
{
public:
	int i;
	int j;
	char c;
	int number_food = 0;
	int food = 1;
	int body = 3;
	int key_direct;
	int direct_get=75;
	int direct_before;
	int score=0;
	int snakeX[100];
	int snakeY[100];
	void snake_show1();
	void snake_show2();
	void color(short x);
	void hide_cursor();
	int snake_status();
};

                                              //snake_初始化
void snake ::snake_show1()
{
	//在屏幕中间生成蛇头
	snakeX[0] = (KWIDTH +KLEFT)/ 2;//x坐标为偶数
	snakeY[0] = (KHEIGHT+KUP)/ 2;
	//打印蛇头
	gotoxy(snakeX[0], snakeY[0]);
	cout<<"@";
	for (i = 1; i < body; i++)//生成初试的蛇身
	{
		//蛇身的打印，纵坐标不变，横坐标为上一节蛇身的坐标值+1
		snakeX[i] = snakeX[i - 1] + 1;
		snakeY[i] = snakeY[i - 1];
		gotoxy(snakeX[i], snakeY[i]);
		cout << "@";
	}
	gotoxy(70, 20);
}

                                              //snake和food控制；

void snake::snake_show2()
{
	hide_cursor();
	srand((unsigned)time(NULL));
	m_iX = 22+1 + rand() % (KWIDTH - 22);
	m_iY = KUP + 1 + rand() % (KHEIGHT - 2);
	gotoxy(m_iX, m_iY);
	cout << "$";
	Sleep(100);
	gotoxy(14, 5);
	cout << score;
	while (1)
	{
		    if (snake_status()==2)
			{ 
			break;
			}
	        direct_before = direct_get;//记录前一个按键的方向
			if (_kbhit())//如果用户按下了键盘中的某个键
			{
				//清空缓冲区的字符

				//getch()读取方向键的时候，会返回两次，第一次调用返回0或者224，第二次调用返回的才是实际值
				direct_get = _getch();//第一次调用返回的不是实际值
				direct_get = _getch();//第二次调用返回实际值
			}
			for (i = 0; i < body; i++)
			{
				gotoxy(snakeX[i], snakeY[i]);
				cout << " ";
			}

			for (i = body - 1; i > 0; i--)
			{
				snakeX[i] = snakeX[i - 1];
				snakeY[i] = snakeY[i - 1];
				gotoxy(snakeX[i], snakeY[i]);
				cout << "@";
			}

			if (direct_before == 72 && direct_get == 80)
				direct_get = 72;
			if (direct_before == 80 && direct_get == 72)
				direct_get = 80;
			if (direct_before == 75 && direct_get == 77)
				direct_get = 75;
			if (direct_before == 77 && direct_get == 75)
				direct_get = 77;
			switch (direct_get)
			{
			case 97:
				
					do
					{
						c = getchar();
					} while (c != 'a');
				
				break;
			case 75:
				snakeX[0] -= 1;//往左
				break;
			case 77:
				snakeX[0] += 1;//往右
				break;
			case 72:
				snakeY[0]--;//往上
				break;
			case 80:
				snakeY[0]++;//往下
				break;
			

			}
			color(4);
			gotoxy(snakeX[0], snakeY[0]);
			cout << "@";
			color(7);
			
			switch (score / 5)
			{
			case 0:Sleep(400);
				gotoxy(11, 10);
				cout << "1";
				break;
			case 1:Sleep(370);
				gotoxy(11, 10);
				cout << "2";
				break;
			case 2:Sleep(340);
				gotoxy(11, 10);
				cout << "3";
				break;
			case 3:Sleep(310);
				gotoxy(11, 10);
				cout << "4";
				break;
			case 4:Sleep(280);
				gotoxy(11, 10);
				cout << "5";
				break;
			case 5:Sleep(250);
				gotoxy(11, 10);
				cout << "6";
				break;
			case 6:Sleep(220);
				gotoxy(11, 10);
				cout << "7";
				break;
			case 7:Sleep(190);
				gotoxy(11, 10);
				cout << "8";
				break;
			case 8:Sleep(160);
				gotoxy(11, 10);
				cout << "9 ";
				break;
			}
			if (snakeX[0] == m_iX&&snakeY[0] == m_iY)
			{
				srand((unsigned)time(NULL));
				m_iX = 22 + 1 + rand() % (KWIDTH - 23);
				m_iY = 2 + 1 + rand() % (KHEIGHT - 3);
				gotoxy(m_iX, m_iY);
				cout << "$";
				body++;
				score = body -3;
			    gotoxy(14,5);
			    cout << score;
			}
		}
		system("cls");
		gotoxy(30, 10);
		cout << "游戏结束";
}
	                                       //颜色
void snake::color(short x)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), x);
}
                                           //隐藏光标
void snake::hide_cursor()
{
	HANDLE h_GAME = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cursor_info;
	GetConsoleCursorInfo(h_GAME, &cursor_info);
	cursor_info.bVisible = false;
	SetConsoleCursorInfo(h_GAME, &cursor_info);
}
int snake::snake_status()
{
	if (snakeX[0] == 22 || snakeX[0] == 70 || snakeY[0] == 2 || snakeY[0] == 20)
		return 2;
	//蛇头碰到蛇身，游戏结束
	for (i = 1; i < body; i++)
	{
		if (snakeX[i] == snakeX[0] && snakeY[i] == snakeY[0])
		return 2;
	}
}   


                                               

//main
int main()
{
	PlaySound(TEXT("F:\\QQMusic\\Laura Shigihara - Faster.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP); // 这里是你文件的路径
	string  pic = "@@@";
	Unit stu1(10,10,pic);

	choice stu2;
	stu2.choice_show();
	getchar();
	system("cls");

	draw stu3;
	stu3.show3();

	snake stu4;
	stu4.snake_show1();
	
	stu4.snake_show2();	
	system("pause");
}


	//cfood stu2;
	//stu2.create1();
	//stu2.create_food1();
/*
//class Cfood
class cfood :public Unit
{
public:
int number_food;
void create1();
void create_food1();
void create_food2();
};


//cfood函数
void cfood::create1()
{
//todo;随机生成食物
srand((unsigned)time(NULL));
m_iX = KLEFT + 1 + rand() % (KWIDTH - 2);
m_iY = KUP + 1 + rand() % (KHEIGHT - 2);

}
void cfood::create_food1()
{

gotoxy(m_iX, m_iY);
cout << "$";
}

void cfood::create_food2()
{
srand((unsigned)time(NULL));
m_iX = KLEFT + 1 + rand() % (KWIDTH - 2);
m_iY = KUP + 1 + rand() % (KHEIGHT - 2);
gotoxy(m_iX, m_iY);
cout << "$";
}
*/