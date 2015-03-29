#include "Ghost.h"


Ghost::Ghost(void){}

void Ghost::Init(ALLEGRO_BITMAP *image, int spawnX, int spawnY, int patrol[2]){
	GameObject::Init(spawnX, spawnY, 3, 3, 1, 0, 8, 32);
	SetID(ENEMY);
	SetAlive(true);
	SetCollideType(WHITE);

	lives = 1;
	frameCount = 0;
	frameDelay = 5;
	frameHeight = 64;
	frameWidth = 64;
	animationColumns = 8;
	animationRow = 0;
	curFrame = 0;
	this->patrol[1] = patrol[1];
	this->patrol[0] = patrol[0];

	if(image != 0){
		Ghost::image = image;
	}

}

void Ghost::Update(){
	GameObject::Update();
	if(x <= patrol[0] || x >= patrol[1]){
		dirX = -dirX;
	}
	if(dirX == -1){
		MoveLeft();
	}
	else if(dirX == 1){
		MoveRight();
	}
	frameCount++;
}

void Ghost::Render(){
	GameObject::Render();

	int fx = (curFrame % animationColumns) * frameWidth;
	int fy = animationRow * frameHeight;

	al_draw_bitmap_region(image, fx, fy, frameWidth, frameHeight, x-frameWidth/2, y-frameHeight/2, 0);
}

void Ghost::MoveLeft(){
	if(frameCount>=frameDelay){
		frameCount = 0;
		if(animationRow!=5){
			animationRow = 5;
			curFrame = 7;
		}
		else if(curFrame == 4){
			curFrame = 7;
		}
		else --curFrame;
	}
}

void Ghost::MoveRight(){
	if(frameCount>=frameDelay){
		frameCount = 0;
		if(animationRow!=1){
			animationRow = 1;
			curFrame = 0;
		}
		else if(curFrame == 3)
			curFrame = 0;
		curFrame++;
	}
}

void Ghost::Attack(){

}

void Ghost::Die(){

}
