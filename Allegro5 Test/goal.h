#pragma once
#include "gameobject.h"

class goal :
	public GameObject
{
public:
	goal(void);

	void Render();
	void Init(ALLEGRO_BITMAP *image, float x, float y, int boundX, int boundY, int collideType);

	~goal(void);
};

