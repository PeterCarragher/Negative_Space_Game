#include "PlayerBlack.h"


PlayerBlack::PlayerBlack(void)
{
}

void PlayerBlack::Init(ALLEGRO_BITMAP *image = 0,int spawnX = 350, int spawnY = 100){
	PlayerWhite::Init(image, spawnX, spawnY);
	SetCollideType(BLACK);
	SetID(PLAYERBLACK);
}

PlayerBlack::~PlayerBlack(void)
{
}
