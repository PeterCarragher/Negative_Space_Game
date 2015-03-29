#include "goal.h"


goal::goal(void)
{
}

void goal::Init(ALLEGRO_BITMAP *image = 0, float x = 0, float y = 0, int boundX = 100, int boundY = 100, int collideType = GREY){
	GameObject::Init(x, y ,0,0,0,0,boundX, boundY);
	SetID(GOAL);
	SetAlive(true);
	SetCollidable(true);
	SetCollideType(collideType);

	frameWidth = al_get_bitmap_width(image);
	frameHeight = al_get_bitmap_height(image);

	if(image != 0){
		goal::image = image;
	}
}

void goal::Render(){
	GameObject::Render();

	al_draw_bitmap_region(image, 0, 0, frameWidth, frameHeight, x, y, 0);
}

goal::~goal(void)
{
}
