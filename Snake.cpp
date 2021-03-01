#include "stdafx.h"
#include "Snake.h"


Snake::Snake()
{

}

void snake::snake_show1()
{
	//在屏幕中间生成蛇头
	snakeX[0] = (KWIDTH + KLEFT) / 2;//x坐标为偶数
	snakeY[0] = (KHEIGHT + KUP) / 2;
	//打印蛇头
	gotoxy(snakeX[0], snakeY[0]);
	cout << "@";
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
	m_iX = 22 + 1 + rand() % (KWIDTH - 22);
	m_iY = KUP + 1 + rand() % (KHEIGHT - 2);
	gotoxy(m_iX, m_iY);
	cout << "$";
	Sleep(100);
	gotoxy(14, 5);
	cout << score;
	while (1)
	{
		if (snake_status() == 2)
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
			score = body - 3;
			gotoxy(14, 5);
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



Snake::~Snake()
{
}
