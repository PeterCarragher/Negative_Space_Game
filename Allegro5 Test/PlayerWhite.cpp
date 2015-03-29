#include "PlayerWhite.h"
PlayerWhite::PlayerWhite(){}

void PlayerWhite::Destroy(){
	GameObject::Destroy();
}

void PlayerWhite::Init(ALLEGRO_BITMAP *image = 0,int spawnX = 350, int spawnY = 100){
	GameObject::Init(spawnX, spawnY,4,4,0,1,5,32);
	SetID(PLAYERWHITE);
	SetAlive(true);
	SetCollideType(WHITE);

	this->spawnX = spawnX;
	this->spawnY = spawnY;
	lives = 100;
	score = 0;
	jump=false;
	mayJumpAgain = false;
	isOnSolidGround = false;
	willJumpLeft = willJumpRight = false;
	jumpFramesLeft = 0;
	gravity = 1;
	jumpSpeed = 15;
	float cameraPosition[2] = {0,0};
	dying = false;

	frameDelay = 5;
	frameCount = 0;
	maxFrame = 8;
	curFrame = 0;
	frameWidth = 64;
	frameHeight = 64;
	animationColumns = 8;
	animationDirection = 0;

	animationRow = 8;

	if(image != 0){
		PlayerWhite::image = image;
	}
}

void PlayerWhite::Update(){

	GameObject::Update();

	if(x<0){
		x=0;
	}
	else if(x > WIDTH)
		x = WIDTH;
	if(y<=0){
		dirY = 1;
	}
	/*
	else if(y > HEIGHT){
		if(lives>0){
			dieAnimation();
		}
	}*/	

	CameraUpdate(cameraPosition, x, y, frameWidth, frameHeight);
	frameCount++;
}

void PlayerWhite::Render(){
	GameObject::Render();

	int fx = (curFrame % animationColumns) * frameWidth;
	int fy = animationRow * frameHeight;

	al_draw_bitmap_region(image, fx, fy, frameWidth, frameHeight, 
		x - frameWidth/2, y - frameHeight/2, 0);


}

void PlayerWhite::dieAnimation(){
	dying = true;
	velX = 1;
	if(frameCount>=frameDelay){
		frameCount = 0;
		if(dirX == 1){
			if(animationRow!=2){
				animationRow = 2;
				curFrame = 0;
			}
			else if(curFrame == 7){
				LoseLife();
				dying = false;
				if(lives == 0)
					SetAlive(false);
				else{
					x = spawnX;
					y = spawnY;
					ResetAnimation(RIGHT);
					ResetMovement(RIGHT);
				}
			}
			else
				++curFrame;
		}
		else{
			if(animationRow!=11){
				animationRow = 11;
				curFrame = 7;
			}
			else if(curFrame == 0){
				LoseLife();
				dying = false;
				if(lives == 0)
					SetAlive(false);
				else{
					x = spawnX;
					y = spawnY;
					ResetAnimation(LEFT);
					ResetMovement(LEFT);
				}
				
			}
			else
				--curFrame;
		}
	}
}

void PlayerWhite::MoveUp(){
	dirY = -1;
}

void PlayerWhite::MoveDown(){
	dirY = 1;
	if(!isOnSolidGround){
		velY +=gravity;
	}
	else{
		ResetMovement(DOWN);
	}
}

void PlayerWhite::MoveLeft(){
	dirX = -1;
	
	if(frameCount >= frameDelay){
		frameCount = 0;
		//go to start of run animation, if still, or if at end of run animation
		if(animationRow == 8 || (curFrame<=4 && animationRow == 10)){
			animationRow=9;
			curFrame = 3;
		}
		else if((curFrame<=0) && (animationRow == 9)){
			//go to next line of animation
			curFrame = 7;
			animationRow = 10;
		}
		else{
			curFrame--;
		}
	}
}

void PlayerWhite::MoveRight(){
	dirX = 1;
	
	if(frameCount >= frameDelay){
		frameCount = 0;
		//go to start of run animation, if still, or if at end of run animation
		if(animationRow == 8 || (curFrame==3 && animationRow == 1)){
			animationRow=0;
			curFrame = 4;
		}
		else if((curFrame>=7) && (animationRow == 0)){
			//go to next line of animation
			curFrame = 0;
			animationRow = 1;
		}
		else{
			curFrame++;
		}
	}
}

void PlayerWhite::Jump(){
	dirY = 1;
	jump = true;
	isOnSolidGround = false;
	if(mayJumpAgain)
		velY = -jumpSpeed;
	else{
		MoveDown();
	}

	if(isOnSolidGround && !mayJumpAgain){
		ResetMovement(DOWN);
		if(dirX = 1){
			ResetMovement(RIGHT);
			ResetAnimation(RIGHT);
		}
		else if(dirX = -1){
			ResetMovement(LEFT);
			ResetAnimation(LEFT);
		}
		mayJumpAgain = true;
		jump = false;
	}
	else{
		if(dirX == 1){
			animationRow = 5;
			curFrame = 5;
		}
		else if(dirX == -1){
			animationRow = 14;
			curFrame = 2;
		}
	}
	mayJumpAgain = false;
}

bool PlayerWhite::checkMayJumpAgain(){
	if(isOnSolidGround && !jump){
		mayJumpAgain = true;
	}
	else
		mayJumpAgain = false;
	return mayJumpAgain;
}

void PlayerWhite::JumpRight(){
	//animation
	dirX = 1;
	if(frameCount >= frameDelay){
		frameCount = 0;
		if(animationRow != 5){
			animationRow = 5;
			curFrame = 2;
		}
		else if(curFrame == 7){
			willJumpRight = false;
			ResetAnimation(RIGHT);
		}
		else{
		curFrame++;
		}
	}
}
	
void PlayerWhite::JumpLeft(){
	dirX = -1;
	if(frameCount >= frameDelay){
		frameCount = 0;
		if(animationRow != 14){
			animationRow = 14;
			curFrame = 5;
		}
		else if(curFrame == 0){
			willJumpLeft = false;
			ResetAnimation(LEFT);
		}
		else{
		curFrame--;
		}
	}
}		
		
void PlayerWhite::ResetMovement(int direction){
		if(direction == UP){
			dirY = 0;
			velY = 4;
		}
		else if(direction == DOWN){
			dirY = 0;
			velY = 4;
		}
		else if (direction == RIGHT){
			dirX = 0;
			velX = 4;
		}
		else if (direction == LEFT){
			dirX = 0;
			velX = 4;
		}
}

void PlayerWhite::ResetAnimation(int position){
		if(position == UP){
			;
		}
		else if(position == DOWN){
			;
		}
		else if (position == RIGHT){
			curFrame = 0;
			animationRow = 8;
		}
		else if (position == LEFT){
			curFrame = 1;
			animationRow = 8;
		}
}

bool PlayerWhite::CheckCollisions(GameObject *otherObject){
	float oX = otherObject->GetX();
	float oY = otherObject->GetY();

	int obX = otherObject->GetBoundX();
	int obY = otherObject->GetBoundY();

	int oTop = oY-obY;
	int oBottom = oY+obY;
	int oLeft = oX-obX;
	int oRight = oX+obX;

	int top = y-boundY;
	int bottom = y+boundY;
	int left = x-boundX;
	int right = x+boundX;

	if(right > oLeft && 
	   left < oRight &&
	   bottom > oTop &&
	   top < oBottom){

		return  true;
	}else{
		return false;
	}
}

void PlayerWhite::Collided(GameObject *otherObject){
	int objectID = otherObject->GetID();

	float oX = otherObject->GetX();
	float oY = otherObject->GetY();

	int obX = otherObject->GetBoundX();
	int obY = otherObject->GetBoundY();

	int oTop = oY-obY;
	int oBottom = oY+obY;
	int oLeft = oX-obX;
	int oRight = oX+obX;

	int top = y-boundY;
	int bottom = y+boundY;
	int left = x-boundX;
	int right = x+boundX;



	if(objectID == ENEMY){
		if((top<oTop) && (bottom < (oTop+(2*velY)))){
			otherObject->SetAlive(false);
		}
		else
			dieAnimation();
	}
	else if(objectID == FLOOR){
		//Right collision
		if((left < oLeft) && (right < (oLeft + (2*velX)))){
				x-= (right - oLeft); 
		   }
		//Left collision
		if((right > oRight) && (left > (oRight - (2*velX)))){
				x+= (oRight - left);
		   }
		//Bottom collision
		if((top<oTop) && (bottom < (oTop+(2*velY)))){
				y-= (bottom-oTop);
				isOnSolidGround = true;
		   }
		//Top collision
		if((bottom > oBottom) && (top < (oBottom - (2*velY))) && !(((top<oTop) && (bottom < (oTop+(2*velY))))||((left < oLeft) && (right < (oLeft + (2*velX)))))){
				y+=(oBottom-top);
		   }
	}
	else if(objectID == SAW){
		if((std::sqrt(std::pow(right-oX,2)+std::pow(bottom-oY,2)) <= obX) || 
			(std::sqrt(std::pow(left-oX,2)+std::pow(bottom-oY,2)) <= obX) ||
			(std::sqrt(std::pow(right-oX,2)+std::pow(top-oY,2)) <= obX) ||
			(std::sqrt(std::pow(left-oX,2)+std::pow(top-oY,2)) <= obX)){
			dieAnimation();
		}
	}

}

void PlayerWhite::CameraUpdate(float *cameraPosition, float PlayerWhiteX, float PlayerWhiteY, int PlayerWhiteWidth, int PlayerWhiteHeight){
	cameraPosition[0] = (PlayerWhiteX + PlayerWhiteWidth/2)-(WIDTH/2);
	cameraPosition[1] = (PlayerWhiteY + PlayerWhiteWidth/2) - (HEIGHT/2);

	if(cameraPosition[0] < 0)
		cameraPosition[0] = 0;
	if(cameraPosition[1]<0)
		cameraPosition[1] = 0;
}