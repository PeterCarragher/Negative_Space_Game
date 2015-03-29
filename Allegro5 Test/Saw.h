#pragma once
#include "GameObject.h"
#include <math.h>
class Saw : public GameObject
{
private:
	int lives;
	int animationRow;
	float gravity;

protected:

public:
	Saw();
	void Destroy();

	void Init(ALLEGRO_BITMAP *image, int spawnX, int spawnY,int boundX, int boundY);
	void Update();
	void Render();

	void MoveUp();
	void MoveDown();
	void MoveLeft();
	void MoveRight();
	
	void ResetAnimation(int position);
	void ResetMovement(int direction);

	int GetLives(){return lives;}

	int GetVelX(){return velX;}
	int GetVelY(){return velY;}

	void SetVelX(int velX){this->velX = velX;}
	void SetVelY(int velY){this->velY = velY;}

	int GetDirX(){return dirX;}
	int GetDirY(){return dirY;}

	void SetDirX(int dirX){this->dirX = dirX;}
	void SetDirY(int dirY){this->dirY = dirY;}

	void LoseLife(){lives--;}

	bool CheckCollisions(GameObject *otherObject);
	void Collided(GameObject *otherObject);
};

