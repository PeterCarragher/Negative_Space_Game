#pragma once
#include "PlayerWhite.h"
class PlayerBlack :
	public PlayerWhite
{
public:
	PlayerBlack(void);
	void Init(ALLEGRO_BITMAP *image,int spawnX, int spawnY);
	~PlayerBlack(void);
};

