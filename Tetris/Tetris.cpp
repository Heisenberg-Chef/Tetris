#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <graphics.h>
#include <conio.h>
#include <time.h>
#include <windows.h>
#include "GameBoard.h"

int clk;
static int count = 1;
#define UP 'w'
#define DOWN 's'
#define LEFT 'a'
#define RIGHT 'd'
#define ESC 27
#define BOOM 8
#define Re 13
#define spacebar 32

#define X 8
#define Y 16
#define LINE 5
#define SCREEN_X 600
#define SCREEN_Y 700
#define map_x 50
#define map_y 100
#define BK LINE+bs
// 游戏运行速度,非阻塞时间判定
void start();
bool speed(int lvl,int clk);

int main()
{
	char vk = 0;
	initgraph(SCREEN_X, SCREEN_Y);
	setbkcolor(DARKGRAY);
gameover: 	start();
	vk = _getch();
	int temp = vk - 48;
	if (temp != 1 && temp != 2 && temp != 3 && temp != 4 && temp != 5)
	{
		temp = 1;
	}
	//初始化游戏了！！
	GameBoard game;
	game.init_pat();
	cleardevice();

	while (1)
	{
		if ( count == 0 || (count % 10 == 0 && temp < 0 ) )
		{
			temp++; count++;
		}
		clk = clock();
		while (2)
		{
			if (speed(temp, clk))
			{
				break;
			}

			if (_kbhit())
			{
				vk = _getch();
			}
			else { vk = 0; }

			switch (vk)
			{
			case LEFT:
				game.movex_();
				break;
			case RIGHT:
				game.movex();
				break;
			case UP:
				game.transitpat();
				break;
			case DOWN:
				if (game.GameOn() == false)
				{
					if (game.GameJudgment() == false)
					{
						goto gameover;
					}
					else
					{
						game.Game_init();
						Sleep(50);
					}
				}
				break;
			default:
				break;
			}
			game.GameJudgment();
			Sleep(20);
		}

		if(game.GameOn()== false)
		{
		if (game.GameJudgment() == false)
			{
				goto gameover;
			}
			game.Game_init();
			game.GameJudgment();
		}
	}

	
	return 0;
}

void start()
{
	cleardevice();
	RECT r = { 0,0,600,700 };
	settextcolor(LIGHTRED);
	LOGFONT f;
	gettextstyle(&f);                     // 获取当前字体设置
	f.lfHeight = 40;                      // 设?米痔甯叨任? 48
	_tcscpy_s(f.lfFaceName, _T("黑体"));    // 设置字体为“黑体”(高版本 VC 推荐使用 _tcscpy_s 函数)
	f.lfQuality = ANTIALIASED_QUALITY;    // 设置输出效果为抗锯齿  
	settextstyle(&f);                     // 设置字体样式

	drawtext(_T("请输入难度：\n恩..总共就1-5级，输入1-5就好了\n按其他都默认从1级开始玩哈哈\n每成功放置10个方块升一级。"), &r, DT_CENTER);

}

bool speed(int lvl,int clk)
{
	if ( clock() - clk >= (600 / lvl))
	{
		return true;
	}
	return false;
}
