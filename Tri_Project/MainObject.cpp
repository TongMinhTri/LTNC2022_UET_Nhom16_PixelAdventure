#include "MainObject.h"

MainObject::MainObject()
{
	img_run_left = NULL;
	img_run_right = NULL;

	img_idle_left = NULL;
	img_idle_right = NULL;

	img_jump_left = NULL;
	img_jump_right = NULL;

	img_fall_left = NULL;
	img_fall_right = NULL;

	object = NULL;

	rect.x = rect.y = 0;
	rect.w = rect.h = 32;

	frame = 0;
	x_pos = 0;
	y_pos = 384;
	x = y = 0;
	frame_w = frame_h = 0;
	status = IDLE_RIGHT;
	input_type.left = input_type.right = 0;
	input_type.jump = 0;
	input_type.down = 0;
	input_type.idle = 1;
	on_ground = true;
	jump = false;
	setPos(x_pos, y_pos);
	for (int i = 0; i < 12; i++)
	{
		frame_clips[i].w = frame_clips[i].h = 0;
		frame_clips[i].x = frame_clips[i].y = 0;
	}
}

MainObject::~MainObject()
{
}

void MainObject::setIMG(SDL_Renderer* renderer)
{
	img_run_left = LoadIMG("Characters/Mask Dude/Run_left.png", renderer);
	img_run_right = LoadIMG("Characters/Mask Dude/Run_right.png", renderer);

	img_idle_left = LoadIMG("Characters/Mask Dude/Idle_left.png", renderer);
	img_idle_right = LoadIMG("Characters/Mask Dude/Idle_right.png", renderer);

	img_jump_left = LoadIMG("Characters/Mask Dude/Jump_left.png", renderer);
	img_jump_right = LoadIMG("Characters/Mask Dude/Jump_right.png", renderer);

	img_fall_left = LoadIMG("Characters/Mask Dude/Fall_left.png", renderer);
	img_fall_right = LoadIMG("Characters/Mask Dude/Fall_right.png", renderer);

	object = img_idle_right;
}

SDL_Texture* MainObject::LoadIMG(string path, SDL_Renderer* renderer)
{
	SDL_Texture* newTexture = NULL;
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());

	if (loadedSurface != NULL)
	{
		SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));
		newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
		if (newTexture != NULL)
		{
			rect.w = loadedSurface->w;
			rect.h = loadedSurface->h;
		}

		SDL_FreeSurface(loadedSurface);
	}
	frame_w = rect.w / 12;
	frame_h = rect.h;

	return newTexture;
}

// Ham load hinh anh sau moi thao tac di chuyen
// Nguon tham khao: https://www.youtube.com/watch?v=ma-h2RxBBaY&t=508s

void MainObject::showImage(SDL_Renderer* renderer)
{
	if (!on_ground)
	{
		if (status == FALL_RIGHT)
		{
			object = img_fall_right;
		}
		else if (status == FALL_LEFT)
		{
			object = img_fall_left;
		}
		else if (status == JUMP_RIGHT)
		{
			object = img_jump_right;
		}
		else if (status == JUMP_LEFT)
		{
			object = img_jump_left;
		}
	}
	else
	{
		jump = false;
		
		if (status == FALL_RIGHT)
		{
			object = img_idle_right;
			status = IDLE_RIGHT;
		}
		else if (status == FALL_LEFT)
		{
			object = img_idle_left;
			status = IDLE_LEFT;
		}
		else if (status == JUMP_RIGHT)
		{
			object = img_idle_right;
			status = IDLE_RIGHT;

		}
		else if (status == JUMP_LEFT)
		{
			object = img_idle_left;
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

	SDL_Rect* currentClip = &frame_clips[2 * frame / 3];
	
	SDL_Rect renderQuad = { rect.x, rect.y, frame_w, frame_h };
	
	SDL_RenderCopy(renderer, object, currentClip, &renderQuad);

}

void MainObject::handleMovement(SDL_Event event, SDL_Renderer* renderer, Mix_Chunk* soundEffect[])
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
				object = img_run_right;
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
				object = img_run_left;
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
			if (status == IDLE_RIGHT || status == WALK_RIGHT)
			{
				Mix_PlayChannel(-1, soundEffect[jump_sound], 0);
				status = JUMP_RIGHT;
			}
			else if (status == IDLE_LEFT || status == WALK_LEFT)
			{
				Mix_PlayChannel(-1, soundEffect[jump_sound], 0);
				status = JUMP_LEFT;
			}
			else if (status == FALL_RIGHT && jump == false)
			{
				Mix_PlayChannel(-1, soundEffect[jump_sound], 0);        
				status = JUMP_RIGHT;
			}
			else if (status == FALL_LEFT && jump == false)
			{
				Mix_PlayChannel(-1, soundEffect[jump_sound], 0);
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
				object = img_idle_right;
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
				object = img_idle_left;
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
				object = img_fall_right;
			}
			else if (status == JUMP_LEFT)
			{
				status = FALL_LEFT;
				object = img_fall_left;
			}
			input_type.idle = 1;
		}
		break;  
		default:
			break;
		}
	}
}


// Ham chia anh thanh 12 frame

void MainObject::setClips()
{
	if (frame_w > 0 && frame_h > 0)
	{
		for (int i = 0; i < 12; i++)
		{
			frame_clips[i].x = frame_w * i;
			frame_clips[i].y = 0;
			frame_clips[i].w = frame_w;
			frame_clips[i].h = frame_h;
		}
	}
}


// Ham thay doi vi tri cua nhan vat sau moi thao tac di chuyen
// Nguon tham khao: https://www.youtube.com/watch?v=ma-h2RxBBaY&t=508s

void MainObject::updatePlayerPosition(Map& map_data)
{
	x = 0;
	y += FALL_SPEED;

	if (y >= 10)
	{
		y = 10;
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
		if (!jump)
		{
			y = -JUMP_VALUE;
		}
		jump = true;
		on_ground = false;
	}
	checkCollisionS(map_data);
}


// Ham xu ly va cham 
// Nguon tham khao: https://www.youtube.com/watch?v=ma-h2RxBBaY&t=508s

void MainObject::checkCollisionS(Map& map_data)
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

	if (x1 >= 0 && x2 < TILEMAP_NUM_X && y1 >= 0 && y2 < TILEMAP_NUM_Y)
	{
		if (x > 0) //Nhan vat di chuyen sang phai
		{
			if (map_data.tile[y1][x2] != 0 || map_data.tile[y2][x2] != 0)
			{
				x_pos = x2 * TILE_SIZE;
				x_pos -= frame_w + 1;
				x = 0;
			}
		}
		else if (x < 0) //Nhan vat di chuyen sang trai
		{
			if (map_data.tile[y1][x1] != 0 || map_data.tile[y2][x1] != 0)
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

	if (x1 >= 0 && x2 < TILEMAP_NUM_X && y1 >= 0 && y2 < TILEMAP_NUM_Y)
	{
		if (y > 0)
		{
			if (map_data.tile[y2][x1] != 0 || map_data.tile[y2][x2] != 0)
			{
				y_pos = y2 * TILE_SIZE;
				y_pos -= (frame_h + 1);
				y = 0;
				on_ground = true;
			}
		}
		else if (y < 0)
		{
			if (map_data.tile[y1][x1] != 0 || map_data.tile[y1][x2] != 0)
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
	else if (x_pos + frame_w > SCREEN_WIDTH)
	{
		x_pos = SCREEN_WIDTH - frame_w - 1;
	}
	if (y_pos < 0)
	{
		y_pos = 0;
	}
	if (y > 0) on_ground = false;
	y_pos += y;

}

SDL_Rect MainObject::getRect()
{
	test.x = rect.x;
	test.y = rect.y;
	test.w = 32;
	test.h = 32;
	return test;
}

void MainObject::setPos(int x, int y)
{
	rect.x = x;
	rect.y = y;
	x_pos = x;
	y_pos = y;

	object = img_idle_right;
	status = IDLE_RIGHT;
	input_type.left = input_type.right = 0;
	input_type.jump = 0;
	input_type.down = 0;
	input_type.idle = 1;
	on_ground = true;
	jump = false;
}

