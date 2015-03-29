#include "GameObject.h"

GameObject::GameObject(){
	x = 0;
	y = 0;

	velX = 0;
	velY = 0;

	dirX = 0;
	dirY = 0;

	boundX = 0;
	boundY = 0;

	maxFrame = 0;
	curFrame = 0;
	frameCount = 0;
	frameDelay = 0;
	frameWidth = 0;
	frameHeight = 0;
	animationColumns = 0;
	animationDirection = 0;
	animationDirection = 0;

	image = 0;

	alive = true;
	collidable = true;
}

void GameObject::Destroy(){
	if(image != 0){		
		image = 0;

	}
}

void GameObject::Init(float x, float y, float velX, float velY, int dirX, int dirY, int boundX, int boundY){
	this->x = x;
	this->y = y;

	this->velX = velX;
	this->velY = velY;

	this->dirX = dirX;
	this->dirY = dirY;

	this->boundX = boundX;
	this->boundY = boundY;
}

void GameObject::Update(){
	x+=velX*dirX;
	y+=velY*dirY;
}

void GameObject::Render(){
	
}

bool GameObject::CheckCollisions(GameObject *otherObject){
	float oX = otherObject->GetX();
	float oY = otherObject->GetY();

	int obX = otherObject->GetBoundX();
	int obY = otherObject->GetBoundY();

	if(x+boundX > oX-obX && 
	   x-boundX < oX+obX &&
	   y+boundY > oY-obY &&
	   y-boundY < oY+obY){
		   return  true;
	}else{
		return false;
	}
}

void GameObject::Collided(GameObject *otherObject){
}

bool GameObject::Collidable(){
	return alive && collidable;
}

void GameObject::SetCollideType(int type){
	this->collideType = type;
}

int GameObject::GetCollideType(){
	return collideType;
}