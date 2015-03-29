#include "GreyFloor.h"


GreyFloor::GreyFloor(void)
{
}

void GreyFloor::Init(ALLEGRO_BITMAP *image = 0, float x = 0, float y = 0, int boundX = 100, int boundY = 100){
	Floor::Init(image, x, y, boundX, boundY);
	SetCollideType(GREY);
}

GreyFloor::~GreyFloor(void)
{
}
