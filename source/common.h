#include <stdlib.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

typedef struct Entity Entity;
typedef struct Texture Texture;

struct Texture
{
	SDL_Texture *texture;
	Texture *other;
};

typedef struct
{
	SDL_Renderer *renderer;
	SDL_Window *window;
	Texture textureHead, *textureTail;
	void (*logic)();
	void (*draw)();
} SDL_Context;

typedef struct
{
	int up;
	int down;
	int left;
	int right;
	int space;
	int esc;
	int h;
} Input;

struct Entity
{
	int x;
	int y;
	int move_x;
	int move_y;
	int width;
	int height;
	int lives;
	char *entity_type;
	SDL_Texture *texture;
	Entity *other;
};

typedef struct
{
	Entity enemyHead, *enemyTail;
	Entity bulletHead, *bulletTail;
	int score;
} Game;