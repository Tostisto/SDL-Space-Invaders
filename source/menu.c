#include "menu.h"

static void logic();
static void draw();

int enemy_Speed;
int enemy_SpawnSpeed;
int player_lives;
int enemy_lives;

TTF_Font *menu_tittle;
TTF_Font *menu_small_font;

SDL_Rect title, normal_mode, hard_mode, quit;
SDL_Texture *menuTexture;

void menu_init()
{
	menu_tittle = TTF_OpenFont("resources/font/MachineGunk-nyqg.ttf", 120);
	menu_small_font = TTF_OpenFont("resources/font/dogica.ttf", 30);

	sdl.logic = logic;
	sdl.draw = draw;
}

static void logic()
{
	if (input_key.space)
	{
		enemy_Speed = 3;
		enemy_SpawnSpeed = 100;
		player_lives = 3;
		enemy_lives = 2;
		init_game();
	}

	if (input_key.h)
	{
		enemy_Speed = 3;
		enemy_SpawnSpeed = 90;
		player_lives = 2;
		enemy_lives = 3;
		init_game();
	}

	if (input_key.esc)
	{
		SDL_close();
	}
}

static void draw()
{
	SDL_SetRenderDrawColor(sdl.renderer, 0, 0, 0, 255);
	SDL_RenderClear(sdl.renderer);

	int x;

	x = getCenterX(strlen("Space Invaders"), TTF_FontHeight(menu_tittle) / 2.5);

	draw_text(sdl.renderer, menu_tittle, &menuTexture, &title, x, 150, "Space Invaders");
	SDL_RenderCopy(sdl.renderer, menuTexture, NULL, &title);

	x = getCenterX(strlen("Normal Mode - SPACE"), 30);

	draw_text(sdl.renderer, menu_small_font, &menuTexture, &normal_mode, x, 400, "Normal mode - SPACE");
	SDL_RenderCopy(sdl.renderer, menuTexture, NULL, &normal_mode);

	x = getCenterX(strlen("Hard Mode - H"), 30);

	draw_text(sdl.renderer, menu_small_font, &menuTexture, &hard_mode, x, 490, "Hard mode - H");
	SDL_RenderCopy(sdl.renderer, menuTexture, NULL, &hard_mode);

	x = getCenterX(strlen("Quit - ESC"), 30);

	draw_text(sdl.renderer, menu_small_font, &menuTexture, &quit, x, 580, "Quit - ESC");
	SDL_RenderCopy(sdl.renderer, menuTexture, NULL, &quit);
}

void menu_font_close()
{
	TTF_CloseFont(menu_tittle);
	TTF_CloseFont(menu_small_font);
	SDL_DestroyTexture(menuTexture);
}