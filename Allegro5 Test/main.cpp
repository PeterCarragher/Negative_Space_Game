#pragma once

#define _CRT_SECURE_NO_WARNINGS		
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <assert.h>
#include <list>
#include "NLTmxMap.h"
#include "rapidxml.hpp"

#include "Globals.h"
#include "GameObject.h"
#include "PlayerWhite.h"
#include "Floor.h"
#include "Saw.h"
#include "background.h"
#include "Ghost.h"
#include "PlayerBlack.h"
#include "BlackFloor.h"
#include "GreyFloor.h"
#include "goal.h"

#include <iterator>
#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <fstream>

using namespace std;
using namespace rapidxml;

//globals (to main)
bool keys[] = { false, false, false, false, false, false, false, false, false, false };


std::list<GameObject *>objects;
std::list<GameObject *>::iterator iter;
std::list<GameObject *>::iterator iter2;

static void* loadFile(const char * filename, bool appendNull ) {
    
    FILE* f = fopen(filename, "r" );
    if ( !f ) {
        return 0;
    }
    
    fseek( f, 0, SEEK_END );
    auto length = ftell( f ) + appendNull;
    fseek( f, 0, SEEK_SET );
    
    void* buffer = malloc( length );
    fread( buffer, length, 1, f );
    fclose( f );
    
    if ( appendNull ) {
        ((char*)buffer)[ length-1 ] = 0;
    }
    
    return buffer;
}

int main(int argc, char **argv){
	char *levelPath = "assets/levels/level 3.tmx";
	char *levelImagePath = "assets/levels/levelImages/level 3.png";
	char *xml = (char*) loadFile(levelPath, true);
	NLTmxMap* map = NLLoadTmxMap( xml );
	//std::cout << "width " << map->width << ", height " << map->height << std::endl;
	
	//SHELL VARIABLES
	bool done = false;
	bool render = false;

	float gameTime = 0;
	int frames = 0;
	int gameFPS = 0;
	int FPS = 60;

	//PROJECT VARIABLES

	ALLEGRO_BITMAP *manSheet = 0;
	ALLEGRO_BITMAP *womanSheet = 0;
	ALLEGRO_BITMAP *greyFloor = 0;
	ALLEGRO_BITMAP *whiteFloor = 0;
	ALLEGRO_BITMAP *blackFloor = 0;
	ALLEGRO_BITMAP *manGoal = 0;
	ALLEGRO_BITMAP *womanGoal = 0;
	ALLEGRO_BITMAP *levelImage = 0;

	//ALLEGRO VARIABLES
	ALLEGRO_DISPLAY *display = 0;
    ALLEGRO_EVENT_QUEUE *event_queue = 0;
    ALLEGRO_TIMER *timer = 0;
	ALLEGRO_FONT *font18;
	ALLEGRO_FONT *font24;
    ALLEGRO_FONT *font36;

	//ALLEGRO INIT FUNCTIONS
	if(!al_init()){
		return -1;
    }

	display = al_create_display(WIDTH, HEIGHT);
	if(!display){
		return -1;
	}

	//ADDON INSTALL
	al_init_image_addon();
    al_init_primitives_addon();
    al_init_font_addon();
    al_init_ttf_addon();
	al_install_keyboard();
  
	//PROJECT INIT
    font18 = al_load_font("calibri.ttf", 18, 0);
	font24 = al_load_font("calibri.ttf", 24, 0);
    font36 = al_load_font("calibri.ttf", 36, 0);
	
	vector<ALLEGRO_BITMAP *>images;

	manSheet = al_load_bitmap("assets/Characters/man_sprite_sheet.png");
	womanSheet = al_load_bitmap("assets/Characters/woman_sprite_sheet.png");
	greyFloor = al_load_bitmap("assets/Environment/Tiles/floorTiles/grey.png");
	blackFloor = al_load_bitmap("assets/Environment/Tiles/floorTiles/black.png");
	whiteFloor = al_load_bitmap("assets/Environment/Tiles/floorTiles/white.png");
	manGoal = al_load_bitmap("assets/Environment/Tiles/level tilesets/manGoal.png");
	womanGoal = al_load_bitmap("assets/Environment/Tiles/level tilesets/womanGoal.png");
	levelImage = al_load_bitmap("assets/levels/levelImages/level 3.png");

	images.push_back(manSheet);
	images.push_back(womanSheet);
	images.push_back(greyFloor);
	images.push_back(blackFloor);
	images.push_back(whiteFloor);
	images.push_back(manGoal);
	images.push_back(womanGoal);

	int manSpawnX;
	int womanSpawnX;
	int manSpawnY;
	int womanSpawnY;

	for(auto x:map->groups){
		if(x->name == "whiteob"){
			for(auto tile:x->objects){
				Floor *thistile = new Floor();
				thistile->Init(levelImage, (tile->x + ((tile->width)/2)), (tile->y + ((tile->height)/2)), (tile->width)/2, (tile->height)/2);
				objects.push_back(thistile);
			}
		}
		else if(x->name == "blackob"){
			for(auto tile:x->objects){
				BlackFloor *thistile = new BlackFloor();
				thistile->Init(levelImage, (tile->x + ((tile->width)/2)), (tile->y + ((tile->height)/2)), (tile->width)/2, (tile->height)/2);
				objects.push_back(thistile);
			}
		}
		else if(x->name == "greyob"){
			for(auto tile:x->objects){
				GreyFloor *thistile = new GreyFloor();
				thistile->Init(levelImage, (tile->x + ((tile->width)/2)), (tile->y + ((tile->height)/2)), (tile->width)/2, (tile->height)/2);
				objects.push_back(thistile);
			}
		}
		else if(x->name == "whitespawn")
			for(auto tile:x->objects){
				manSpawnX = tile->x + 34;
				manSpawnY = tile->y + 34;
			}
		else if(x->name == "blackspawn")
			for(auto tile:x->objects){
				womanSpawnX = tile->x + 34;
				womanSpawnY = tile->y + 34;
			}
		else if(x->name == "whitegoal"){
			for(auto tile:x->objects){
				goal *Goal = new goal();
				Goal->Init(manGoal, tile->x, tile->y, al_get_bitmap_width(manGoal)/2, al_get_bitmap_height(manGoal)/2, WHITE);
				objects.push_back(Goal);
			}
		}
		else if(x->name == "blackgoal"){
			for(auto tile:x->objects){
				goal *Goal = new goal();
				Goal->Init(womanGoal, tile->x, tile->y, al_get_bitmap_width(womanGoal)/2, al_get_bitmap_height(womanGoal)/2, BLACK);
				objects.push_back(Goal);
			}
		}
	}

	PlayerBlack* black = new PlayerBlack();
	PlayerWhite* white = new PlayerWhite();
	black->Init(womanSheet, manSpawnX, manSpawnY);
	white->Init(manSheet, manSpawnX, manSpawnY);
	objects.push_back(black);
	objects.push_back(white);

	ALLEGRO_TRANSFORM camera;

	//TIMER INIT AND STARTUP
	event_queue = al_create_event_queue();
	timer = al_create_timer(1.0/FPS);

	al_register_event_source(event_queue, al_get_timer_event_source(timer));
    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_keyboard_event_source());

    al_start_timer(timer);
	gameTime = al_current_time();

	while(!done){

		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);

		//INPUT
		if(ev.type == ALLEGRO_EVENT_KEY_DOWN){
			switch (ev.keyboard.keycode){
			case ALLEGRO_KEY_ESCAPE:
				done = true;
				break;
			case ALLEGRO_KEY_A:
				keys[LEFT] = true;
				break;
			case ALLEGRO_KEY_D:
				keys[RIGHT] = true;
				break;
			case ALLEGRO_KEY_W:
				keys[UP] = true;
				break;
			case ALLEGRO_KEY_S:
				keys[DOWN] = true;
			case ALLEGRO_KEY_R:
				white->SetX((float)manSpawnX);
				white->SetY((float)manSpawnY);
				black->SetX((float)womanSpawnX);
				black->SetY((float)womanSpawnY);
				black->cameraPosition[0] = 0;
				black->cameraPosition[1] = 0;
			}
		}
		else if (ev.type == ALLEGRO_EVENT_KEY_UP){
			switch (ev.keyboard.keycode){
			case ALLEGRO_KEY_A:
				keys[LEFT] = false;
			case ALLEGRO_KEY_D:
				keys[RIGHT] = false;
			case ALLEGRO_KEY_W:
				keys[UP] = false;
			case ALLEGRO_KEY_S:
				keys[DOWN] = false;
			}

		}
		
		//GAME UPDATE
		else if(ev.type == ALLEGRO_EVENT_TIMER){
			render = true;

			//UPDATE FPS
			frames++;
			if(al_current_time() - gameTime >= 1){
				gameTime = al_current_time();
				gameFPS = frames;
				frames = 0;
			}

			black->CameraUpdate(black->cameraPosition, black->GetX(), black->GetY(), black->GetWidth(), black->GetHeight());
			int camX = black->cameraPosition[0];
			int camY = black->cameraPosition[1];
			al_identity_transform(&camera);
			al_translate_transform(&camera, 0, -camY);
			al_use_transform(&camera);

			if (keys[LEFT]) {
				black->MoveLeft();
				white->MoveLeft();
			}
			if (keys[RIGHT]) {
				black->MoveRight();
				white->MoveRight();
			}
			if (!keys[LEFT] && !keys[RIGHT]) { 
				black->ResetMovement(LEFT);
				white->ResetMovement(LEFT);
				black->ResetAnimation(LEFT); 
				white->ResetAnimation(LEFT);
			}
			/*
			if (keys[UP]){
				if (black->checkMayJumpAgain())
					black->Jump();
				else if (!black->isOnSolidGround){
					black->MoveDown();
				}
				if (white->checkMayJumpAgain())
					white->Jump();
				else if (!white->isOnSolidGround){
					white->MoveDown();
				}
			}
			*/
			
			//update game objects
			for(iter = objects.begin(); iter!=objects.end(); ++iter){
				(*iter)->Update();
			}

			//collisions
			for(iter = objects.begin(); iter != objects.end(); ++iter){
				if(!(*iter)->Collidable()) continue;

				for(iter2 = iter; iter2!=objects.end(); ++iter2){
					if((*iter)->GetCollideType() - (*iter2)->GetCollideType() != 0) continue;
					else if(!((*iter2)->Collidable())) continue;
					else if((*iter)->GetID() == (*iter2)->GetID()) continue;
					else if((*iter2)->CheckCollisions(*iter)){
						(*iter)->Collided(*iter2);
						(*iter2)->Collided(*iter);
					}
				}
			}

			//cull the dead
			for(iter = objects.begin(); iter != objects.end();){
				if(!(*iter)->GetAlive()){
					delete (*iter);
					iter = objects.erase(iter);
				}
				else
					iter++;
			}

		}

		//RENDER

		if(render && al_is_event_queue_empty(event_queue)){
			render = false;
			al_draw_textf(font18, al_map_rgb(255,255,255), 5, 5, 0, "FPS: %i", gameFPS);
			
			//BEGIN PROJECT RENDER
			//render game objects
			for(iter = objects.begin(); iter!=objects.end(); ++ iter){
				(*iter)->Render();
			}
			
			//FLIP BUFFERS
			al_flip_display();
			al_clear_to_color(al_map_rgb(51,153,255));
		}
	}

	//DESTROY PROJECT OBJECTS
	//destroy game objects
	for(iter = objects.begin(); iter!=objects.end(); iter){
		(*iter)->Destroy();
		delete(*iter);
		iter = objects.erase(iter);
	}

	for(auto x:images){
		al_destroy_bitmap(x);
	}

	//SHELL OBJECTS
	al_destroy_font(font18);
	al_destroy_font(font24);
	al_destroy_font(font36);
	al_destroy_timer(timer);
	al_destroy_event_queue(event_queue);
	al_destroy_display(display);
  
    return 0;
}

