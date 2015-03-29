#pragma once
#include "floor.h"

class BlackFloor :
	public Floor
{
public:
	BlackFloor(void);

	void Init(ALLEGRO_BITMAP *image, float x, float y, int boundX, int boundY);

	~BlackFloor(void);
};

