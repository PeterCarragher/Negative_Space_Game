#include "Floor.h"
Floor::Floor(){}

void Floor::Destroy(){
	GameObject::Destroy();
}

void Floor::Init(ALLEGRO_BITMAP *image = 0, float x = 0, float y = 0, int boundX = 100, int boundY = 100){
	GameObject::Init(x, y ,0,0,0,0,boundX + 4, boundY);
	SetID(FLOOR);
	SetAlive(true);
	SetCollidable(true);
	SetCollideType(WHITE);

	frameWidth = boundX*2;
	frameHeight = boundY*2;

	if(image != 0){
		Floor::image = image;
	}
}

void Floor::Render(){
	GameObject::Render();

	al_draw_bitmap_region(image, x-(frameWidth/2), y-(frameHeight/2), frameWidth, frameHeight, x-(frameWidth/2), y-(frameHeight/2), 0);
}

void Floor::Update(){
	GameObject::Update();
}

bool Floor::CheckCollisions(GameObject *otherObject){
	return GameObject::CheckCollisions(otherObject);
}

void Floor::Collided(int objectID){
}

