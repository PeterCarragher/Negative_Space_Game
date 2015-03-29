#include "Saw.h"

Saw::Saw(void)
{}

void Saw::Destroy(){
	GameObject::Destroy();
}

void Saw::Init(ALLEGRO_BITMAP *image = 0, int spawnX = 150, int spawnY = 150, int boundX = 130, int boundY = 130) {
	GameObject::Init(spawnX, spawnY,0,0,0,0,boundX, boundY);
	SetID(SAW);
	SetAlive(true);
	SetCollideType(WHITE);

	lives = 1;
	gravity = 1;

	frameDelay = 5;
	frameCount = 0;
	maxFrame = 0;
	curFrame = 0;
	frameWidth = 2*boundX;
	frameHeight = 2*boundY;
	animationColumns = 0;
	animationDirection = 0;

	animationRow = 0;

	if(image != 0){
		Saw::image = image;
	}
}

void Saw::Update(){
	GameObject::Update();
}

void Saw::Render(){
	
	GameObject::Render();
	double angle = (frameCount*ALLEGRO_PI/180);
	al_draw_rotated_bitmap(image, frameWidth/2, frameHeight/2, x, y, angle, 0);
	frameCount++;
	if(frameCount>=360)
		frameCount = 0;
}

bool Saw::CheckCollisions(GameObject *otherObject){
	if (GameObject::CheckCollisions(otherObject)){
		float oX = otherObject->GetX();
		float oY = otherObject->GetY();

		int obX = otherObject->GetBoundX();
		int obY = otherObject->GetBoundY();

		{
			if(std::sqrt(std::pow(x-oX,2)+std::pow(y-oY,2)) != boundX)
				return true; 
			else
				return false;
		}
	}
	else
		return false;
}

void Saw::Collided(GameObject *otherObject){
	
}