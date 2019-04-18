#include "GameBoard.h"



GameBoard::GameBoard()
{
	
}

void GameBoard::Game_init()
{
	mark++;
	realx = rand() % (8 - queue[mark].contact_x);//根据X碰撞位置随机出x位置
	realy = 0;//初始化为第一行，Y一定为0；
	//打印工作
	cleardevice();
	GameBoard::DrawBoard();
	//打印当前方块
	queue[mark].pattern::Drawpat(realx, realy);
	//打印下一个方块
	queue[mark + 1].pattern::Drawpat(11, 0);
	if (mark == 9998)
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

		drawtext(_T("你也太能玩了吧？9998个方块？！？！？！"), &r, DT_LEFT);
	}
}

bool GameBoard::GameOn() // true就正常下落，false就说明要更新了。
{
	queue[mark + 1].pattern::Drawpat(11, 0);
	if (queue[mark].contact_y + realy < 16 && !crush_y())
	{
		realy++;
		DrawBoard();
		queue[mark].pattern::Drawpat(realx,realy);
		return true;
	}
	else
	{
		for (int g_y = 0; g_y < 4; g_y++)
		{
			for (int g_x = 0; g_x < 4; g_x++)
			{
				if (queue[mark].array[g_y][g_x] != 0)
				{
					board[realy + g_y][realx + g_x] = queue[mark].array[g_y][g_x];
				}
			}
		}
		
	}
	return false;
}

bool GameBoard::crush_y()
{
	for (int g_y = 0; g_y < 4; g_y++)
	{
		for (int g_x = 0; g_x < 4; g_x++)
		{
			if (queue[mark].array[g_y][g_x] != 0)
			{
				if (board[realy + g_y + 1][realx + g_x] != 0)
				{
					return true;
				}
			}
		}
	}
	return false;
}

bool GameBoard::crush_x()
{
	for (int g_y = 0; g_y < 4; g_y++)
	{
		for (int g_x = 0; g_x < 4; g_x++)
		{
			if (queue[mark].array[g_y][g_x] != 0)
			{
				/////////////////////////////////////////
				if (board[realy + g_y][realx + g_x + 1] != 0 || realx + g_x  + 1 > 7)
				{
					return true;
				}
			}
		}
	}
	return false;
}

bool GameBoard::crush_x_()
{
	for (int g_y = 0; g_y < 4; g_y++)
	{
		for (int g_x = 0; g_x < 4; g_x++)
		{
			if (queue[mark].array[g_y][g_x] != 0)
			{
				///////////////////////////
				if (board[realy + g_y][realx + g_x - 1] != 0 || realx + g_x - 1 < 0)
				{
					return true;
				}
			}
		}
	}
	return false;
}

bool GameBoard::transitck()
{
	for (int g_y = 0; g_y < 4; g_y++)
	{
		for (int g_x = 0; g_x < 4; g_x++)
		{
			if (data[queue[mark].num_y][((queue[mark].num_x + 1) % (queue[mark].type))]
				.array[g_y][g_x] != 0)
			{
				if (board[realy + g_y][realx + g_x] != 0 || realx + g_x > 7 || realx + g_x < 0
					|| realy + g_y > 15)
				{
					return true;
				}
			}
		}
	}
	return false;
}

void GameBoard::movex()
{
	if (!crush_x())
	{
		cleardevice();
		DrawBoard();
		queue[mark + 1].pattern::Drawpat(11, 0);
		realx = realx + 1;
		queue[mark].pattern::Drawpat(realx, realy);
	}
}

void GameBoard::movex_()
{
	if (!crush_x_())
	{
		cleardevice();
		DrawBoard();
		queue[mark + 1].pattern::Drawpat(11, 0);
		realx = realx - 1;
		queue[mark].pattern::Drawpat(realx, realy);
	}

}

//board[realy + g_y][realx + g_x] = queue[mark].array[g_y][g_x];
void GameBoard::transitpat()
{
	if (!transitck())
	{
		queue[mark] = data[queue[mark].num_y][((queue[mark].num_x + 1) % (queue[mark].type))];
		cleardevice();
		DrawBoard();
		queue[mark + 1].pattern::Drawpat(11, 0);
		queue[mark].pattern::Drawpat(realx, realy);
	}
}

GameBoard::~GameBoard()
{

}

void GameBoard::init_pat()
{
	// I
	COLORREF I[4][4] =
	{ {BROWN,0,0,0},
	 {BROWN,0,0,0},
	 {BROWN,0,0,0},
	 {BROWN,0,0,0} };
	data[0][0].pattern::pattern(1, 4, I, 2,0,0);
	// -
	COLORREF I_V[4][4] =
	{ {BROWN,BROWN,BROWN,BROWN},
	 {0,0,0,0},
	 {0,0,0,0},
	 {0,0,0,0} };
	data[0][1].pattern::pattern(4, 1, I_V, 2,0,1);
	/////////////////////////////////////////////////
	//L
	COLORREF L[4][4] =
	{ {YELLOW,0,0,0},
	 {YELLOW,0,0,0},
	 {YELLOW,YELLOW,0,0},
	 {0,0,0,0} };
	data[1][0].pattern::pattern(2, 3, L, 4,1,0);
	//横L
	COLORREF L_A[4][4] =
	{ {YELLOW,YELLOW,YELLOW,0},
	 {YELLOW,0,0,0},
	 {0,0,0,0},
	 {0,0,0,0} };
	data[1][1].pattern::pattern(3, 2, L_A, 4,1,1);
	//下L
	COLORREF L_B[4][4] =
	{ {YELLOW,YELLOW,0,0},
	 {0,YELLOW,0,0},
	 {0,YELLOW,0,0},
	 {0,0,0,0} };
	data[1][2].pattern::pattern(2, 3, L_B, 4,1,2);
	//躺L
	COLORREF L_C[4][4] =
	{ {0,0,YELLOW,0},
	 {YELLOW,YELLOW,YELLOW,0},
	 {0,0,0,0},
	 {0,0,0,0} };
	data[1][3].pattern::pattern(3, 2, L_C, 4,1,3);
	////////////////////////
	//田
	COLORREF O[4][4] =
	{ {CYAN,CYAN,0,0},
	 {CYAN,CYAN,0,0},
	 {0,0,0,0},
	 {0,0,0,0} };
	data[2][0].pattern::pattern(2, 2, O, 1,2,0);
	//////////////////////////
	//反L
	COLORREF VL[4][4] =
	{ {0,LIGHTBLUE,0,0},
	 {0,LIGHTBLUE,0,0},
	 {LIGHTBLUE,LIGHTBLUE,0,0},
	 {0,0,0,0} };
	data[3][0].pattern::pattern(2, 3, VL, 4,3,0);

	COLORREF VL_A[4][4] =
	{ {LIGHTBLUE,0,0,0},
	 {LIGHTBLUE,LIGHTBLUE,LIGHTBLUE,0},
	 {0,0,0,0},
	 {0,0,0,0} };
	data[3][1].pattern::pattern(3, 2, VL_A, 4,3,1);

	COLORREF VL_B[4][4] =
	{ {LIGHTBLUE,LIGHTBLUE,0,0},
	 {LIGHTBLUE,0,0,0},
	 {LIGHTBLUE,0,0,0},
	 {0,0,0,0} };
	data[3][2].pattern::pattern(2, 3, VL_B, 4,3,2);

	COLORREF VL_C[4][4] =
	{ {LIGHTBLUE,LIGHTBLUE,LIGHTBLUE,0},
	 {0,0,LIGHTBLUE,0},
	 {0,0,0,0},
	 {0,0,0,0} };
	data[3][3].pattern::pattern(3, 2, VL_C, 4,3,3);
	/////////////////////////////
	//s
	COLORREF S[4][4] =
	{ {GREEN,0,0,0},
	 {GREEN,GREEN,0,0},
	 {0,GREEN,0,0},
	 {0,0,0,0} };
	data[4][0].pattern::pattern(2, 3, S, 2,4,0);

	COLORREF S_A[4][4] =
	{ {0,GREEN,GREEN,0},
	 {GREEN,GREEN,0,0},
	 {0,0,0,0},
	 {0,0,0,0} };
	data[4][1].pattern::pattern(3, 2, S_A, 2,4,1);

	//2
	COLORREF P2[4][4] =
	{ {MAGENTA,MAGENTA,0,0},
	 {0,MAGENTA,MAGENTA,0},
	 {0,0,0,0},
	 {0,0,0,0} };
	data[5][0].pattern::pattern(3, 2, P2, 2,5,0);

	COLORREF P2_A[4][4] =
	{ {0,MAGENTA,0,0},
	 {MAGENTA,MAGENTA,0,0},
	 {MAGENTA,0,0,0},
	 {0,0,0,0} };
	data[5][1].pattern::pattern(2, 3, P2_A, 2,5,1);

	//T
	COLORREF T[4][4] =
	{ {RED,RED,RED,0},
	 {0,RED,0,0},
	 {0,0,0,0},
	 {0,0,0,0} };
	data[6][0].pattern::pattern(3, 2, T, 4,6,0);

	COLORREF T_A[4][4] =
	{ {0,RED,0,0},
	 {RED,RED,0,0},
	 {0,RED,0,0},
	 {0,0,0,0} };
	data[6][1].pattern::pattern(2, 3, T_A, 4,6,1);

	COLORREF T_B[4][4] =
	{ {0,RED,0,0},
	 {RED,RED,RED,0},
	 {0,0,0,0},
	 {0,0,0,0} };
	data[6][2].pattern::pattern(3, 2, T_B, 4,6,2);

	COLORREF T_C[4][4] =
	{ {RED,0,0,0},
	 {RED,RED,0,0},
	 {RED,0,0,0},
	 {0,0,0,0} };
	data[6][3].pattern::pattern(2, 3, T_C, 4,6,3);

	be_a_queue();
}

void GameBoard::be_a_queue()
{
	srand((unsigned)time(NULL));//随机种子
	for (int countb = 0; countb < 10000; countb++)
	{
		int _rand = rand() % 7;//随机0-6
		temp = data[_rand][0];//取第一个图形作为样本
		temp = data[_rand][rand() % (data[_rand][0].type)];//取随机type种图形
		queue[countb] = temp;
	}
}

void GameBoard::DrawBoard()
{
	for (int j = 0; j < 16; j++)
	{
		for (int i = 0; i < 8; i++)
		{
			box::DrawBox(map_x + i * 35, map_y + j * 35, board[j][i]);
		}
	}
	RECT r = { 400,350,600,550 };
	settextcolor(LIGHTGREEN);
	LOGFONT f;
	gettextstyle(&f);                     // 获取当前字体设置
	f.lfHeight = 22;                      // 设?米痔甯叨任? 48
	_tcscpy_s(f.lfFaceName, _T("黑体"));    // 设置字体为“黑体”(高版本 VC 推荐使用 _tcscpy_s 函数)
	f.lfQuality = ANTIALIASED_QUALITY;    // 设置输出效果为抗锯齿  
	settextstyle(&f);                     // 设置字体样式

	drawtext(_T("w:转换图形\ns:向下\na:<-\nd:->\nESC:退出\nENTER:重新开始\n退格：开挂@.@"), &r, DT_LEFT);
}

bool GameBoard::GameJudgment()
{
	int g_y, g_x;
	//x轴消除
	for (g_y = 15; g_y >= 0; g_y--)
	{

		for (g_x = 0; g_x < 8; g_x++)
		{
			if (board[g_y][g_x] == 0)
			{
				goto S2;
			}
			else
			{
				goto S1;
			}
S1:			NULL;
		}
		//消除一行，所有行下行移动
		for (int j = g_y; j > 0; j--)
		{
			for (int i = 0; i < 8; i++)
			{
				board[j][i] = board[j-1][i];
			}
		}
		g_y++;
S2:		NULL;
	}

	//y轴判定
	for (g_y = 0; g_y < 10; g_y ++)
	{
		if (board[0][g_y] != 0)
		{
			return false;
		}
	}

	return true;
}//正常使用true ，gameover使用false