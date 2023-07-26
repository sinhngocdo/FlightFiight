#pragma once
#ifndef COMMON_FUNCTION_H_
#define COMMON_FUNCTION_H_

#include <iostream>
#include <Windows.h>
#include <SDL.h>
#include <string.h>
#include <SDL_image.h>
#include <SDL_mixer.h>

//Screen
const int WIDTH_BACKGROUND = 4800;
const int HEIGHT_BACKGROUND = 600;
const int SCREEN_WIDTH = 1200;
const int SCREEN_HEIGHT = 600;
const int SCREEN_BPP = 32;
const int SPEED_SCREEN = 2;

//Main
const int POS_X_START_MAIN_OBJ = 100;
const int POS_Y_START_MAIN_OBJ = 200;
const int SPEED_MAIN_OBJ = 10;
const int SPEED_BULLET_MAIN = 20;
const int NUMBER_PLAYER_POWER = 3;

//Threats
const int SPEED_THREAT = 5;
const int NUM_THREAT = 3;
const int SPEED_BULLET_THREATS = 10;
const int VAL_OFFSET_START_POST_THREAT = 400;
const int UNDER_LIMIT_THREAT = 200;

static SDL_Surface* g_screen = NULL;
static SDL_Surface* g_Bground = NULL;
static SDL_Event g_event;

static Mix_Chunk* g_sound_bullet[2];
static Mix_Chunk* g_sound_exp[2];

//background file
static char g_name_bk_ground[] = { "bg4800.png" };

//main file
static char g_name_main_obj[] = { "plane_fly.png" };
static char g_name_exp_main[] = { "exp_main.png" };
static char g_name_bullet_main_laser[] = { "laser.png" };
static char g_name_bullet_main_fire[] = { "sphere.png" };
static char g_name_audio_bullet_main_laser[] = { "Gun+Silencer.wav" };
static char g_name_audio_bullet_main_fire[] = { "Gun+1.wav" };
static char g_name_audio_exp_main[] = { "Bomb+1.wav" };
static char g_name_heart_power[] = { "traITym.png" };
 
//threat file
static char g_name_exp_threats[] = { "exp.png" };
static char g_name_threats[] = { "af1.png" };
static char g_name_bullet_threats[] = { "sphere2.png" };
static char g_name_audio_exp_threats[] = { "Explosion+7.wav" };

namespace SDLCommonFunc {
	SDL_Surface* LoadImage(std::string file_path);
	void ApplySurface(SDL_Surface* src, SDL_Surface* des, int x, int y);
	void ApplySurfaceClip(SDL_Surface* src, SDL_Surface* des, SDL_Rect* clip, int x, int y);
	void CleanUp();
	bool CheckCollision(const SDL_Rect& object_1, const SDL_Rect& object_2);
}


#endif
