#pragma once
#ifndef BASE_DATA_H
#define BASE_DATA_H

#include <Windows.h>
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <vector>
#include <fstream>
#include <algorithm>

static SDL_Window* window = NULL;
static SDL_Renderer* renderer = NULL;
static SDL_Event event;

enum Sound
{
	jump_sound,
	collect_sound,
	hitSpike_sound,
	hitRock_sound,
	extra_life,
	sound_total
};

static Mix_Chunk* soundEffect[sound_total];
static Mix_Music* game_music = NULL;
static Mix_Music* menu_music = NULL;
static Mix_Music* gameover_music = NULL;
static Mix_Music* victory_music = NULL;
static Mix_Music* pass_music = NULL;

//Globally used font
static TTF_Font* gFont = NULL;
static TTF_Font* gFontN = NULL;
static TTF_Font* fontText = NULL;

// Screen'size
const int FPS = 33;
const int SCREEN_WIDTH = 960;
const int SCREEN_HEIGHT = 528;

#define JUMP_VALUE  16;
#define FALL_SPEED  2;
#define PLAYER_SPEED  6;

#define TILE_SIZE 48
#define TILEMAP_NUM_X 20
#define TILEMAP_NUM_Y 11

struct Input
{
	int left, right, down, jump, idle;
};

enum Game_status {
	MENU,
	MAP_CHOOSING,
	CHARACTER_CHOOSING,
	ENTER_NAME,
	INSTRUCTION,
	PLAY,
	MAP_PASS_ONE,
	MAP_PASS_TWO,
	PLAY2,
	GAME_OVER,
	WIN,
	TOP_SCORE,
};

struct Map
{
	int tile[TILEMAP_NUM_Y][TILEMAP_NUM_X] = {
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5},
		{5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5},
		{5,0,0,0,8,8,8,0,0,0,0,0,0,0,0,0,0,0,0,5},
		{5,0,0,8,0,0,0,8,8,0,5,5,0,5,5,5,0,0,8,5},
		{5,5,0,0,0,0,0,0,0,0,0,0,0,5,0,0,0,8,8,5},
		{5,5,5,5,0,8,8,8,0,0,0,0,0,5,0,5,5,5,5,5},
		{0,0,0,0,0,0,0,0,5,5,5,0,0,5,0,0,0,0,0,5},
		{0,0,0,8,0,0,0,0,0,0,0,0,5,5,0,0,8,0,0,5},
		{0,0,8,8,0,0,0,0,0,0,0,5,6,5,6,0,8,8,0,0},
		{5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5}
	};
};

struct Map2
{
	int tile[TILEMAP_NUM_Y][TILEMAP_NUM_X] = {
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,9,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,9,0,0,0,9,0,0,0,9,0,0,0,0,9},
		{0,0,0,0,0,0,9,9,9,9,9,9,9,9,9,9,9,9,9,9},
		{9,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{9,9,0,0,0,0,9,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9}
	};
};


#endif // !BASE_DATA_H