#pragma once

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

#include "Globals.h"
#include "GameObject.h"
#include "PlayerWhite.h"
#include "Floor.h"
#include "Saw.h"
#include "background.h"
#include "Ghost.h"
#include "PlayerBlack.h"
#include "BlackFloor.h"

#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <iterator>
#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <fstream>


bool keys[] = {false, false, false, false, false, false, false, false, false};

//globals (to main)
PlayerWhite *man;
PlayerBlack *woman;
Floor *grass;
Floor *grass2;
Floor *grass3;
Floor *Grass800;
Floor *Grass400;
BlackFloor *Bfloor;
Saw *saw;
background *city;
Ghost *ghost;


std::list<GameObject *>objects;
std::list<GameObject *>::iterator iter;
std::list<GameObject *>::iterator iter2;

int main(int argc, char **argv){
 
	//SHELL VARIABLES
	bool done = false;
	bool render = false;

	float gameTime = 0;
	int frames = 0;
	int gameFPS = 0;
	int FPS = 60;

	//PROJECT VARIABLES
	man = new PlayerWhite();
	woman = new PlayerBlack();
	grass = new Floor();
	grass2 = new Floor();
	grass3 = new Floor();
	saw = new Saw();
	city = new background();
	ghost = new Ghost();
	Grass400 = new Floor();
	Grass800 = new Floor();
	Bfloor = new BlackFloor();


	ALLEGRO_BITMAP *manSheet = 0;
	ALLEGRO_BITMAP *womanSheet = 0;
	ALLEGRO_BITMAP *grassTile = 0;
	ALLEGRO_BITMAP *grassTile2 = 0;
	ALLEGRO_BITMAP *grassTile3 = 0;
	ALLEGRO_BITMAP *sawImage = 0;
	ALLEGRO_BITMAP *cityImage = 0;
	ALLEGRO_BITMAP *ghostSheet = 0;
	ALLEGRO_BITMAP *Grass800Tile = 0;
	ALLEGRO_BITMAP *Grass400Tile = 0;
	ALLEGRO_BITMAP *Bfloor800x400 = 0;

	//ALLEGRO VARIABLES
	ALLEGRO_DISPLAY *display = 0;
    ALLEGRO_EVENT_QUEUE *event_queue = 0;
    ALLEGRO_TIMER *timer = 0;
	ALLEGRO_FONT *font18;
	ALLEGRO_FONT *font24;
    ALLEGRO_FONT *font36;
	ALLEGRO_TRANSFORM camera;

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

	manSheet = al_load_bitmap("assets/Characters/man_sprite_sheet.png");
	womanSheet = al_load_bitmap("assets/Characters/woman_sprite_sheet.png");
	sawImage = al_load_bitmap("assets/Characters/Enemies/saw.png");
	cityImage = al_load_bitmap("assets/Environment/Backgrounds/city_background.jpg");
	ghostSheet = al_load_bitmap("assets/Characters/Enemies/ghost_sprite_sheet.png");
	Grass400Tile = al_load_bitmap("assets/Environment/Tiles/white/400x50 white.png");
	Grass800Tile = al_load_bitmap("assets/Environment/Tiles/white/800x50 white.png");
	Bfloor800x400 = al_load_bitmap("assets/Environment/Tiles/black/800x400 black.png");

	assert(manSheet);
	assert(sawImage);
	assert(cityImage);
	assert(ghostSheet);

	man->Init(manSheet, 350, 100);
	woman->Init(womanSheet, 350, 100);
	Grass400->Init(Grass400Tile, 170, 180, 200, 25);
	Grass800->Init(Grass800Tile, 80, 338, 400, 25);
	saw->Init(sawImage, 550, 275, 40, 40);
	city->Init(cityImage, -400, -100);
	int patrol[2] = {100, 200};
	ghost->Init(ghostSheet, 150, 270, patrol);
	Bfloor->Init(Bfloor800x400, 400, 500, 400, 200);

	//objects.push_back(city);
	objects.push_back(saw);
	objects.push_back(ghost);
	objects.push_back(Bfloor);
	objects.push_back(Grass400);
	objects.push_back(Grass800);
	objects.push_back(man);
	objects.push_back(woman);
	

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
			switch(ev.keyboard.keycode){
			case ALLEGRO_KEY_ESCAPE:
				done = true;
				break;
			case ALLEGRO_KEY_SPACE:
				keys[SPACE] = true;
				break;
			case ALLEGRO_KEY_LEFT:
				keys[LEFT] = true;
				break;
			case ALLEGRO_KEY_RIGHT:
				keys[RIGHT] = true;
				break;
			case ALLEGRO_KEY_UP:
				keys[UP] = true;
				break;
			case ALLEGRO_KEY_DOWN:
				keys[DOWN] = true;
				break;
			case ALLEGRO_KEY_W:
				keys[W] = true;
				break;
			case ALLEGRO_KEY_S:
				keys[S] = true;
				break;
			case ALLEGRO_KEY_D:
				keys[D] = true;
				break;
			case ALLEGRO_KEY_A:
				keys[A] = true;
				break;
			
			}
		}
		else if(ev.type == ALLEGRO_EVENT_KEY_UP){
			switch(ev.keyboard.keycode){
			case ALLEGRO_KEY_SPACE:
				keys[SPACE] = false;
				break;
			case ALLEGRO_KEY_LEFT:
				if(!man->jump && !man->dying){
					man->ResetMovement(LEFT);
					man->ResetAnimation(LEFT);
				}
				keys[LEFT] = false;
				break;
			case ALLEGRO_KEY_RIGHT:
				if(!man->jump && !man->dying){
					man->ResetMovement(RIGHT);
					man->ResetAnimation(RIGHT);
				}
				keys[RIGHT] = false;
				break;
			case ALLEGRO_KEY_UP:
				keys[UP] = false;
				break;
			case ALLEGRO_KEY_DOWN:
				keys[DOWN] = false;
				break;
			case ALLEGRO_KEY_A:
				if(!woman->jump && !woman->dying){
					woman->ResetMovement(LEFT);
					woman->ResetAnimation(LEFT);
				}
				keys[A] = false;
				break;
			case ALLEGRO_KEY_D:
				if(!woman->jump && !woman->dying){
					woman->ResetMovement(RIGHT);
					woman->ResetAnimation(RIGHT);
				}
				keys[D] = false;
				break;
			case ALLEGRO_KEY_W:
				keys[W] = false;
				break;
			case ALLEGRO_KEY_S:
				keys[S] = false;
				break;
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

			//move man
			if(keys[UP]){
				if(man->checkMayJumpAgain()){
					man->jump = true;
				}
			}

			if(man->dying)
				man->dieAnimation();
			else if(man->jump){
				man->Jump();
				if(man->GetDirX() == 1)
					man->JumpRight();
				else if(man->GetDirX()==-1)
					man->JumpLeft();
			}
			else{
				man->MoveDown();
				if(keys[LEFT])
					man->MoveLeft();
				if(keys[RIGHT])
					man->MoveRight();
				if(keys[LEFT]&& keys[RIGHT]){
					man->ResetMovement(RIGHT);
					man->ResetAnimation(RIGHT);
				}
			}

			//move woman
			if(keys[W]){
				if(woman->checkMayJumpAgain()){
					woman->jump = true;
				}
			}

			if(woman->dying)
				woman->dieAnimation();
			else if(woman->jump){
				woman->Jump();
				if(woman->GetDirX() == 1)
					woman->JumpRight();
				else if(woman->GetDirX()==-1)
					woman->JumpLeft();
			}
			else{
				woman->MoveDown();
				if(keys[A])
					woman->MoveLeft();
				if(keys[D])
					woman->MoveRight();
				if(keys[A]&& keys[D]){
					woman->ResetMovement(RIGHT);
					woman->ResetAnimation(RIGHT);
				}
			}
			
			man->isOnSolidGround = false;
			
			woman->isOnSolidGround = false;

			//move ghost

			//update game objects
			for(iter = objects.begin(); iter!=objects.end(); ++iter){
				(*iter)->Update();
			}
			al_identity_transform(&camera);
			al_translate_transform(&camera, -man->cameraPosition[0], -man->cameraPosition[1]);
			al_use_transform(&camera);

			//collisions
			for(iter = objects.begin(); iter != objects.end(); ++iter){
				if(!(*iter)->Collidable()) continue;

				for(iter2 = iter; iter2!=objects.end(); ++iter2){
					if(!((*iter2)->Collidable())) continue;
					if((*iter)->GetID() == (*iter2)->GetID()) continue;
					if((*iter)->collideType != (*iter2)->collideType) continue;

					if((*iter2)->CheckCollisions(*iter)){
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

	//SHELL OBJECTS
	al_destroy_font(font18);
	al_destroy_font(font24);
	al_destroy_font(font36);
	al_destroy_timer(timer);
	al_destroy_event_queue(event_queue);
	al_destroy_display(display);
  
    return 0;
}

