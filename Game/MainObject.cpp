#include "MainObject.h"

MainObject::MainObject()
{
	frame = 0;
	x_pos = 0;
	y_pos = SCREEN_HEIGHT - TILE_SIZE - 100;
	x = y = 0;
	frame_w = frame_h = 0;
	status = IDLE_RIGHT;
	input_type.left = input_type.right = 0;
	input_type.jump = 0;
	input_type.down = 0;
	input_type.idle = 1;
	on_ground = false;
	jump = false;

	for (int i = 0; i < 12; i++)
	{
		frame_clip_run[i].w = frame_clip_run[i].h = 0;
		frame_clip_run[i].x = frame_clip_run[i].y = 0;
	}
}

MainObject::~MainObject()
{
}

bool MainObject::LoadIMG(string path, SDL_Renderer* renderer)
{
	bool res = BaseOject::loadImg(path, renderer);
	if (res)
	{
		frame_w = rect.w / 12;
		frame_h = rect.h;
	}

	return res;
}

void MainObject::show(SDL_Renderer* des)
{
	if (!on_ground)
	{
		if (status == FALL_RIGHT)
		{
			LoadIMG("Character/Fall_right.png", des);
		}
		else if (status == FALL_LEFT)
		{
			LoadIMG("Character/Fall_left.png", des);
		}
		else if (status == JUMP_RIGHT)
		{
			LoadIMG("Character/Jump_right.png", des);
		}
		else if (status == JUMP_LEFT)
		{
			LoadIMG("Character/Jump_left.png", des);
		}
	}
	else
	{
		jump = false;
		
		if (status == FALL_RIGHT)
		{
			LoadIMG("Character/Idle_right.png", des);
			status = IDLE_RIGHT;
		}
		else if (status == FALL_LEFT)
		{
			LoadIMG("Character/Idle_left.png", des);
			status = IDLE_LEFT;
		}
		else if (status == JUMP_RIGHT)
		{
			LoadIMG("Character/Idle_right.png", des);
			status = IDLE_RIGHT;

		}
		else if (status == JUMP_LEFT)
		{
			LoadIMG("Character/Idle_left.png", des);
			status = IDLE_LEFT;
		}
	}

	if (input_type.left == 1 || input_type.right == 1 || input_type.idle == 1 || input_type.down || input_type.jump == 1)
	{
		{
			frame++;
		}
	}
	else
	{
		frame = 0;
	}

	if (2 * frame / 3 >= 11)
	{
		frame = 0;
	}
	rect.x = x_pos;
	rect.y = y_pos;

	SDL_Rect* currentClip = &frame_clip_run[2 * frame / 3];
	
	SDL_Rect renderQuad = { rect.x, rect.y, frame_w, frame_h };
	
	SDL_RenderCopy(des, object, currentClip, &renderQuad);

}

void MainObject::handleEvents(SDL_Event event, SDL_Renderer* renderer)
{
	if (event.type == SDL_KEYDOWN)
	{
		switch (event.key.keysym.sym)
		{
		case SDLK_RIGHT:
		{
			status = WALK_RIGHT;
			input_type.right = 1;
			input_type.left = 0;
			input_type.jump = 0;
			input_type.down = 0;
			input_type.idle = 0;
			if (on_ground)
			{
				LoadIMG("Character/Run_right.png", renderer);
			}
			else
			{
				if (jump) status = JUMP_RIGHT;
				else
				{
					status = FALL_RIGHT;
				}
			}
		}
			break;
		case SDLK_LEFT:
		{
			status = WALK_LEFT;
			input_type.left = 1;
			input_type.right = 0;
			input_type.jump = 0;
			input_type.down = 0;
			input_type.idle = 0;
			if (on_ground)
			{
				LoadIMG("Character/Run_left.png", renderer);
			}
			else
			{
				if (jump) status = JUMP_LEFT;
				else
				{
					status = FALL_LEFT;
				}
			}
		}
			break;
		case SDLK_UP:
		{
			input_type.jump = 1;
			jump = true;
			if (status == IDLE_RIGHT)
			{
				status = JUMP_RIGHT;
			}
			else if (status == IDLE_LEFT)
			{
				status = JUMP_LEFT;
			}
			input_type.down = 0;
			input_type.left = 0;
			input_type.right = 0;
			input_type.idle = 0;
		}
			break;
		default:
			break;
		}
	}
	else if (event.type == SDL_KEYUP)
	{
		switch (event.key.keysym.sym)
		{
		case SDLK_RIGHT:
		{
			input_type.right = 0;
			if (on_ground)
			{
				status = IDLE_RIGHT;
				input_type.idle = 1;
				LoadIMG("Character/Idle_right.png", renderer);
			}
			else
			{
				input_type.down = 1;
				status = FALL_RIGHT;
			}
			
		}
		break;
		case SDLK_LEFT:
		{
			input_type.left = 0;
			if (on_ground)
			{
				status = IDLE_LEFT;
				input_type.idle = 1;
				LoadIMG("Character/Idle_left.png", renderer);
			}
			else
			{
				input_type.down = 1;
				status = FALL_LEFT;
			}
		}
		case SDLK_UP:
		{
			input_type.jump = 0;
			if (status == JUMP_RIGHT)
			{
				status = FALL_RIGHT;
				LoadIMG("Character/Fall_right.png", renderer);
			}
			else if (status == JUMP_LEFT)
			{
				status = FALL_LEFT;
				LoadIMG("Character/Fall_left.png", renderer);
			}
			input_type.idle = 1;
		}
		break;  
		default:
			break;
		}
	}
}

void MainObject::setClips()
{
	if (frame_w > 0 && frame_h > 0)
	{
		for (int i = 0; i < 12; i++)
		{
			frame_clip_run[i].x = frame_w * i;
			frame_clip_run[i].y = 0;
			frame_clip_run[i].w = frame_w;
			frame_clip_run[i].h = frame_h;
		}

	}
}

void MainObject::doPlayer(Map& map_data)
{
	x = 0;
	y += 2;

	if (y >= MAX_FALL_SPEED)
	{
		y = MAX_FALL_SPEED;
	}

	if (input_type.left == 1)
	{
		x -= PLAYER_SPEED;
	}
	else if (input_type.right == 1)
	{
		x += PLAYER_SPEED;
	}
	if (input_type.jump == 1)
	{
		if (on_ground)
		{
			y = -JUMP_VALUE;
		}
		on_ground = false;
		input_type.jump = 0;
	}
	checkMap(map_data);
}

void MainObject::checkMap(Map& map_data)
{
	int x1 = 0;
	int x2 = 0;
	int y1 = 0;
	int y2 = 0;

	//Check horizontal
	int height_min = frame_h < TILE_SIZE ? frame_h : TILE_SIZE;
	x1 = (x_pos + x) / TILE_SIZE;
	x2 = (x_pos + x + frame_w - 1) / TILE_SIZE;

	y1 = (y_pos) / TILE_SIZE;
	y2 = (y_pos + height_min - 1) / TILE_SIZE;

	if (x1 >= 0 && x2 < MAP_X && y1 >= 0 && y2 < MAP_Y)
	{
		if (x > 0) //character is moving to right
		{
			if (map_data.tile[y1][x2] != BLANK_TILE || map_data.tile[y2][x2] != BLANK_TILE)
			{
				x_pos = x2 * TILE_SIZE;
				x_pos -= frame_w + 1;
				x = 0;
			}
		}
		else if (x < 0)
		{
			if (map_data.tile[y1][x1] != BLANK_TILE || map_data.tile[y2][x1] != BLANK_TILE)
			{
				x_pos = (x1 + 1) * TILE_SIZE;
				x = 0;
			}
		}
	}

	//Check vertical
	int width_min = frame_w < TILE_SIZE ? frame_w : TILE_SIZE;
	x1 = (x_pos) / TILE_SIZE;
	x2 = (x_pos + width_min) / TILE_SIZE;
	y1 = (y_pos + y) / TILE_SIZE;
	y2 = (y_pos + y + frame_h - 1) / TILE_SIZE;

	if (x1 >= 0 && x2 < MAP_X && y1 >= 0 && y2 < MAP_Y)
	{
		if (y > 0)
		{
			if (map_data.tile[y2][x1] != BLANK_TILE || map_data.tile[y2][x2] != BLANK_TILE)
			{
				y_pos = y2 * TILE_SIZE;
				y_pos -= (frame_h + 1);
				y = 0;
				on_ground = true;
			}
		}
		else if (y < 0)
		{
			if (map_data.tile[y1][x1] != BLANK_TILE || map_data.tile[y1][x2] != BLANK_TILE)
			{
				y_pos = (y1 + 1) * TILE_SIZE;
				y = 0;
			}
		}
	}

	x_pos += x;
	if (x_pos < 0)
	{
		x_pos = 0;
	}
	else if (x_pos + frame_w > map_data.xpos)
	{
		x_pos = map_data.xpos - frame_w - 1;
	}
	if (y_pos < 0)
	{
		y_pos = 0;
	}
	y_pos += y;

}
