#include "BlackFloor.h"


BlackFloor::BlackFloor(void)
{
}


void BlackFloor::Init(ALLEGRO_BITMAP *image = 0, float x = 0, float y = 0, int boundX = 100, int boundY = 100){
	Floor::Init(image, x, y, boundX, boundY);
	SetCollideType(BLACK);
}

BlackFloor::~BlackFloor(void)
{
}
