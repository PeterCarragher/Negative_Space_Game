#include "background.h"

background::background(){}

void background::Init(ALLEGRO_BITMAP *image, int x, int y)
{
	GameObject::Init(x, y,0,0,0,0,0,0);
	SetID(MISC);
	SetCollidable(false);

	background::image = image;
	frameWidth = al_get_bitmap_width(image);
}

void background::Destroy(){
	GameObject::Destroy();
}

void background::Update(){
	GameObject::Update();
}

void background::Render(){
	al_draw_bitmap(image, x, y, 0);
}