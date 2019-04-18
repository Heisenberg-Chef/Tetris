#pragma once
#include <string.h>
#include "box.h"
#define map_x 50
#define map_y 100
#define BK 30+5

class pattern :protected box
{
public:
	COLORREF array[4][4];
	int type, num_y, num_x,contact_x, contact_y;
////////////////////////////////////

	pattern & operator=(pattern & os);
	pattern();
	pattern(int ctx,int cty,COLORREF k[4][4],int t, int ny,int nx);
	void Drawpat(int i, int j);
	~pattern();
};

