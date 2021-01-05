#include "use.h"

void draw_text(SDL_Renderer *renderer, TTF_Font *font, SDL_Texture **texture, SDL_Rect *rect, int x, int y, char *text)
{
	int text_width;
	int text_height;
	SDL_Surface *surface;
	SDL_Color textColor = {255, 255, 255, 0};

	surface = TTF_RenderText_Solid(font, text, textColor);
	*texture = SDL_CreateTextureFromSurface(sdl.renderer, surface);

	SDL_FreeSurface(surface);

	text_width = surface->w;
	text_height = surface->h;

	rect->x = x;
	rect->y = y;
	rect->w = text_width;
	rect->h = text_height;
}

int getCenterX(int length, int fontSize)
{
	return (SCREEN_WIDTH / 2) - ((length * fontSize) / 2);
}

SDL_Texture *loadTexture(char *filename)
{
	SDL_Texture *texture;

	texture = IMG_LoadTexture(sdl.renderer, filename);

	return texture;
}

void draw_texture(SDL_Texture *texture, int x, int y)
{
	SDL_Rect textures;

	textures.x = x;
	textures.y = y;

	SDL_QueryTexture(texture, NULL, NULL, &textures.w, &textures.h);

	SDL_RenderCopy(sdl.renderer, texture, NULL, &textures);
}

void key_is_UP(SDL_KeyboardEvent *event)
{
	if (event->repeat == 0)
	{
		if (event->keysym.scancode == SDL_SCANCODE_W)
		{
			input_key.up = 0;
		}
		if (event->keysym.scancode == SDL_SCANCODE_S)
		{
			input_key.down = 0;
		}
		if (event->keysym.scancode == SDL_SCANCODE_A)
		{
			input_key.left = 0;
		}
		if (event->keysym.scancode == SDL_SCANCODE_D)
		{
			input_key.right = 0;
		}
		if (event->keysym.scancode == SDL_SCANCODE_SPACE)
		{
			input_key.space = 0;
		}
		if (event->keysym.scancode == SDL_SCANCODE_ESCAPE)
		{
			input_key.esc = 0;
		}
		if (event->keysym.scancode == SDL_SCANCODE_H)
		{
			input_key.h = 0;
		}
	}
}

void key_is_DOWN(SDL_KeyboardEvent *event)
{
	if (event->repeat == 0)
	{
		if (event->keysym.scancode == SDL_SCANCODE_W)
		{
			input_key.up = 1;
		}
		if (event->keysym.scancode == SDL_SCANCODE_S)
		{
			input_key.down = 1;
		}
		if (event->keysym.scancode == SDL_SCANCODE_A)
		{
			input_key.left = 1;
		}
		if (event->keysym.scancode == SDL_SCANCODE_D)
		{
			input_key.right = 1;
		}
		if (event->keysym.scancode == SDL_SCANCODE_SPACE)
		{
			input_key.space = 1;
		}
		if (event->keysym.scancode == SDL_SCANCODE_ESCAPE)
		{
			input_key.esc = 1;
		}
		if (event->keysym.scancode == SDL_SCANCODE_H)
		{
			input_key.h = 1;
		}
	}
}

void input()
{
	SDL_Event event;

	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_KEYDOWN)
		{
			key_is_DOWN(&event.key);
		}
		else if (event.type == SDL_KEYUP)
		{
			key_is_UP(&event.key);
		}
	}
}