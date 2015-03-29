#pragma once
#include "GameObject.h"

class background :
	public GameObject
{
public:
	background();
	void Destroy();

	void Update();
	void Render();
	void Init(ALLEGRO_BITMAP *image, int x, int y);

private:
};

