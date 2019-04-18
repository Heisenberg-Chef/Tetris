#include "box.h"

box::box(int xa, int ya,COLORREF colour)
{
	x = xa; y = ya; color = colour;
}

void box::DrawBox(int xa, int ya, COLORREF colour)
{

	setfillcolor(colour);
	solidrectangle(xa, ya ,xa + bs, ya + bs);
}

int box::getx()
{
	return x;
}

int box::gety()
{
	return y;
}

box::~box()
{

}
