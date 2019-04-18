#include "pattern.h"

pattern & pattern::operator=(pattern & os)
{
	if (this == & os)
	{
		return *this;
	}

	for (int j = 0; j < 4; j++)
	{
		for (int i = 0; i < 4; i++)
		{
			array[j][i] = os.array[j][i];
		}
	}
	type = os.type;
	num_y = os.num_y;
	num_x = os.num_x;

	contact_x = os.contact_x;
	contact_y = os.contact_y;
	return *this;
}

pattern::pattern()
{
	for (int temp = 0; temp < 4; temp++)
	{
		for (int temp_ = 0; temp_ < 4; temp_++)
		{
			array[temp][temp_] = 0;
		}
	}
	num_y = num_x = type = contact_x = contact_y = 0;
}


pattern::pattern(int ctx, int cty, COLORREF k[4][4],int t,int ny,int nx)
{
	for (int temp = 0; temp < 4; temp++)
	{
		for(int temp_ = 0;temp_ < 4;temp_ ++)
		{ 
			array[temp][temp_] = k[temp][temp_];
		}	
	}
	type = t;
	num_x = nx;
	num_y = ny;
	contact_x = ctx;
	contact_y = cty;
}

void pattern::Drawpat(int xt, int yt)
{
	for (int j = 0; j < 4; j++)
	{
		for (int i = 0; i < 4; i++)
		{
			if (array[j][i] != 0)
			{
				box::DrawBox(map_x + (i+xt) * 35, map_y + (j+yt) * 35, array[j][i]);
			}
		}
	}
}


pattern::~pattern()
{
	
}

//for (int z = 0; z <= 3; z++)
//{
//	j += BK;
//	for (int c = 0; c <= 3; c++)
//	{
//		if (array[z][c] != 0)
//		{
//
//			pattern::box::box(clr);
//		}
//		i += BK;
//	}
//	i = x;
//}