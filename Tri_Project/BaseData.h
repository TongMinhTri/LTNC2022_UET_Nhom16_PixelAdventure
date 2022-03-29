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
const int FPS = 30;
const int SCREEN_WIDTH = 960;
const int SCREEN_HEIGHT = 480;

#define JUMP_VALUE 15
#define FALL_SPEED 2
#define PLAYER_SPEED 5
#define TILE_SIZE 48
#define TILEMAP_NUM_X 20
#define TILEMAP_NUM_Y 10

struct Input
{
	int left, right, down, jump, idle;
};

struct Map
{
	int tile[TILEMAP_NUM_Y][TILEMAP_NUM_X] = { 
		{5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5},
		{5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5},
		{5,0,0,0,8,8,8,0,0,0,0,0,0,0,0,0,0,0,0,5},
		{5,0,0,8,0,0,0,8,8,0,5,5,0,5,5,5,0,0,8,5},
		{5,5,0,0,0,0,0,0,0,0,0,0,0,5,0,0,0,8,8,5},
		{5,5,5,5,0,8,8,0,0,0,0,0,0,5,0,5,5,5,5,5},
		{0,0,0,0,0,0,0,8,5,5,5,0,0,5,0,0,0,0,0,5},
		{0,0,0,8,0,0,0,0,0,0,0,0,5,5,0,0,8,0,0,5},
		{0,0,8,8,0,0,0,0,0,0,0,5,6,5,6,0,8,8,0,0},
		{5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5}
	};
};
#endif // !BASE_DATA_H
