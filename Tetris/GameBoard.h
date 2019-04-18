#include "box.h"
#include "pattern.h"
#include <time.h>
#include <stdlib.h>
#define map_x 50
#define map_y 100
#define flag_block_x 
class GameBoard :private pattern
{
public:
	COLORREF board[16][10] = {0};
	pattern data[7][4];
	int realx = 0, realy = 0,mark = -1;
	pattern temp;
	pattern queue[10000];
	unsigned int scores = 0;
///////////////////////////////////////////
	GameBoard();
	void init_pat();
	void Game_init();
	bool GameOn();
	void be_a_queue();
	void transitpat();
	void DrawBoard();
	bool crush_y();
	bool crush_x();
	bool crush_x_();
	bool transitck();
	void movex();
	void movex_();
	bool GameJudgment();
	~GameBoard();
};