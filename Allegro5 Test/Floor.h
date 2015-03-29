#pragma once

#include "GameObject.h"


class Floor : public GameObject {
public:
	Floor();
	
	void Destroy();

	void Init(ALLEGRO_BITMAP *image, float x, float y, int boundX, int boundY);
	void Update();
	void Render();

	void Collided(int objectID);
	bool CheckCollisions(GameObject *otherObject);

private:

private:



};