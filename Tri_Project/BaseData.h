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


static SDL_Window* window = NULL;
static SDL_Renderer* renderer = NULL;
static SDL_Event event;

static TTF_Font* fontText = NULL;
enum Sound
{
	jump_sound,
	collect_sound,
	hitSpike_sound,
	hitRock_sound,
	sound_total
};

static Mix_Chunk* soundEffect[sound_total];
static Mix_Music* game_music = NULL;

// Screen'size
const int FPS = 33;
const int SCREEN_WIDTH = 960;
const int SCREEN_HEIGHT = 528;

#define JUMP_VALUE 16
#define FALL_SPEED 2
#define PLAYER_SPEED 6
#define TILE_SIZE 48
#define TILEMAP_NUM_X 20
#define TILEMAP_NUM_Y 11

struct Input
{
	int left, right, down, jump, idle;
};

enum Game_status {
	NAME,
	INTRO,
	PLAY,
	END,
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
#endif // !BASE_DATA_H