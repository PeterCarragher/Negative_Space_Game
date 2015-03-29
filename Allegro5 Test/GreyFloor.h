#pragma once
#include "floor.h"
class GreyFloor :
	public Floor
{
public:
	GreyFloor(void);
	void Init(ALLEGRO_BITMAP *image, float x, float y, int boundX, int boundY);
	~GreyFloor(void);
};

