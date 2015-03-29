#pragma once

#include "GameObject.h"
#include <math.h>
#include "Globals.h"

class PlayerWhite : public GameObject{
	
private:
	int lives;
	int score;
	int animationRow;
	float gravity;
	int jumpSpeed;
	int spawnX;
	int spawnY;

public:
	PlayerWhite();
	void Destroy();

	bool dying;
	bool jump;
	bool mayJumpAgain;
	bool isOnSolidGround;
	int jumpFramesLeft;
	bool willJumpLeft;
	bool willJumpRight;
	float cameraPosition[2];

	void Init(ALLEGRO_BITMAP *image,int spawnX, int spawnY);
	void Update();
	void Render();

	void MoveUp();
	void MoveDown();
	void MoveLeft();
	void MoveRight();
	void JumpLeft();
	void JumpRight();
	void Jump();
	bool checkMayJumpAgain();
	void dieAnimation();
	
	void ResetAnimation(int position);
	void ResetMovement(int direction);

	int GetLives(){return lives;}
	int GetScore(){return score;}

	int GetVelX(){return velX;}
	int GetVelY(){return velY;}

	int GetWidth(){ return this->frameWidth; }
	int GetHeight(){ return this->frameHeight; }

	void SetVelX(int velX){this->velX = velX;}
	void SetVelY(int velY){this->velY = velY;}

	int GetDirX(){return dirX;}
	int GetDirY(){return dirY;}

	void SetDirX(int dirX){this->dirX = dirX;}
	void SetDirY(int dirY){this->dirY = dirY;}

	void LoseLife(){lives--;}
	void AddPoint(){score++;}

	bool CheckCollisions(GameObject *otherObject);
	void Collided(GameObject *otherObject);

	void CameraUpdate(float *cameraPosition, float PlayerWhiteX, float PlayerWhiteY, int PlayerWhiteWidth, int PlayerWhiteHeight);
};