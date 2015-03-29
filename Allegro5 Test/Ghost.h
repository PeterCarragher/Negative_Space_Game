#pragma once
#include "gameobject.h"
class Ghost :
	public GameObject
{
private:
	int lives;
	int animationRow;
	int patrol[2];

public:
	Ghost(void);
	void Init(ALLEGRO_BITMAP *image, int spawnX, int spawnY, int patrol[2]);
	void Update();
	void Render();

	void MoveLeft();
	void MoveRight();
	void Attack();
	void Die();
};

