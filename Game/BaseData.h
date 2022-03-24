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

// Screen'size
const int FPS = 20;
const int SCREEN_WIDTH = 960;
const int SCREEN_HEIGHT = 480;
const int SCREEN_BPP = 32;

const int COLOR_KEY_R = 167;
const int COLOR_KEY_G = 175;
const int COLOR_KEY_B = 180;

const int RENDER_DRAW_COLOR = 0xFF;
#define JUMP_VALUE 15
#define GRAVITY_SPEED 2
#define MAX_FALL_SPEED 10
#define BLANK_TILE 0 
#define PLAYER_SPEED 8
#define TILE_SIZE 48
#define MAP_X 20
#define MAP_Y 10

struct Input
{
	int left, right, down_left, down_right, jump, idle;
};

struct Map
{
	int xstart, ystart;
	int	xpos, ypos;
	int tile[MAP_Y][MAP_X];
	const char* file_name;
};
#endif // !BASE_DATA_H
