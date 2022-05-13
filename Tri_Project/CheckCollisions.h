#pragma once
#ifndef CHECK_H
#define CHECK_H
#include "BaseData.h"

bool checkCollision(SDL_Rect a, SDL_Rect b, int A, int B)
{
	//The sides of the rectangles
	int leftA, leftB;
	int rightA, rightB;
	int topA, topB;
	int bottomA, bottomB;

	//Calculate the sides of rect A
	leftA = a.x + A;
	rightA = a.x + a.w - A;
	topA = a.y + A;
	bottomA = a.y + a.h - A;

	//Calculate the sides of rect B
	leftB = b.x + B;
	rightB = b.x + b.w - B;
	topB = b.y + B;
	bottomB = b.y + b.h;
	if (bottomB > topA && rightB > leftA && rightB - b.w < leftA && bottomB - b.w < topA) return true;
	if (bottomB > topA && rightA > leftB && rightA - b.w < leftB && bottomB - b.w < topA) return true;
	if (bottomA > topB && rightB > leftA && rightB - b.w < leftA && bottomA - b.w < topB) return true;
	if (bottomA > topB && rightA > leftB && rightA - b.w < leftB && bottomA - b.w < topB) return true;

	return false;
}

bool checkCollision_spike(SDL_Rect a, SDL_Rect b, int A, int B)
{
	//The sides of the rectangles
	int leftA, leftB;
	int rightA, rightB;
	int topA, topB;
	int bottomA, bottomB;

	//Calculate the sides of rect A
	if (A == 0)
	{
		leftA = a.x;
		rightA = a.x + a.w;
		topA = a.y + 9;
		bottomA = a.y + a.h;

		//Calculate the sides of rect B
	}
	else if( A == 2)
	{
		leftA = a.x+9;
		rightA = a.x + a.w;
		topA = a.y;
		bottomA = a.y + a.h;
	}
	else
	{
		leftA = a.x;
		rightA = a.x + a.w-9;
		topA = a.y;
		bottomA = a.y + a.h;
	}

	leftB = b.x + B;
	rightB = b.x + b.w - B;
	topB = b.y + B;
	bottomB = b.y + b.h;

	if (bottomB > topA && rightB > leftA && rightB - b.w < leftA && bottomB - b.w < topA) return true;
	if (bottomB > topA && rightA > leftB && rightA - b.w < leftB && bottomB - b.w < topA) return true;
	if (bottomA > topB && rightB > leftA && rightB - b.w < leftA && bottomA - b.w < topB) return true;
	if (bottomA > topB && rightA > leftB && rightA - b.w < leftB && bottomA - b.w < topB) return true;

	return false;
}

bool checkCollision_ghost(SDL_Rect a, SDL_Rect b, int A, int B)
{
	//The sides of the rectangles
	int leftA, leftB;
	int rightA, rightB;
	int topA, topB;
	int bottomA, bottomB;

	//Calculate the sides of rect A
	leftA = a.x + A;
	rightA = a.x + a.w - A;
	topA = a.y;
	bottomA = a.y + a.h;

	//Calculate the sides of rect B
	leftB = b.x + B;
	rightB = b.x + b.w - B;
	topB = b.y + B;
	bottomB = b.y + b.h;
	if (bottomB > topA && rightB > leftA && rightB - b.w < leftA && bottomB - b.w < topA) return true;
	if (bottomB > topA && rightA > leftB && rightA - b.w < leftB && bottomB - b.w < topA) return true;
	if (bottomA > topB && rightB > leftA && rightB - b.w < leftA && bottomA - b.w < topB) return true;
	if (bottomA > topB && rightA > leftB && rightA - b.w < leftB && bottomA - b.w < topB) return true;

	return false;
}

bool checkCollision_point(SDL_Rect a, SDL_Rect b, int A, int B)
{
	//The sides of the rectangles
	int leftA, leftB;
	int rightA, rightB;
	int topA, topB;
	int bottomA, bottomB;

	//Calculate the sides of rect A
	leftA = a.x + A;
	rightA = a.x + a.w - A;
	topA = a.y + 2*A;
	bottomA = a.y + a.h;

	//Calculate the sides of rect B
	leftB = b.x + B;
	rightB = b.x + b.w - B;
	topB = b.y + B;
	bottomB = b.y + b.h;
	if (bottomB > topA && rightB > leftA && rightB - b.w < leftA && bottomB - b.w < topA) return true;
	if (bottomB > topA && rightA > leftB && rightA - b.w < leftB && bottomB - b.w < topA) return true;
	if (bottomA > topB && rightB > leftA && rightB - b.w < leftA && bottomA - b.w < topB) return true;
	if (bottomA > topB && rightA > leftB && rightA - b.w < leftB && bottomA - b.w < topB) return true;

	return false;
}

#endif // !CHECK_H
