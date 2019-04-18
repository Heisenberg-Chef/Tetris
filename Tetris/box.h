#pragma once
#include <graphics.h>
#define bs 30

class box
{
protected:
	int x, y;
	COLORREF color;
public:
	box() :x(0), y(0), color(BLACK) {};
	box(int xa, int ya, COLORREF colour);
	void DrawBox(int xa, int ya, COLORREF colour);
	int getx();
	int gety();
	~box();
};

