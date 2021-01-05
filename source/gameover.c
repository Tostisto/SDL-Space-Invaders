#include "gameover.h"

static void logic();
static void draw();

TTF_Font *game_over_tittle;
TTF_Font *game_over_small_font;
TTF_Font *score_very_small_font;

SDL_Rect gameover_text, play, exit_text;
SDL_Texture *texture_text;

void game_over()
{
	game_over_tittle = TTF_OpenFont("resources/font/dogica.ttf", 80);
	game_over_small_font = TTF_OpenFont("resources/font/dogica.ttf", 30);
	score_very_small_font = TTF_OpenFont("resources/font/dogica.ttf", 20);

	sdl.logic = logic;
	sdl.draw = draw;
}

static void logic()
{
	if (input_key.space)
	{
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

	int x = getCenterX(strlen("GAME OVER"), 80);

	draw_text(sdl.renderer, game_over_tittle, &texture_text, &gameover_text, x, 150, "GAME OVER");
	SDL_RenderCopy(sdl.renderer, texture_text, NULL, &gameover_text);

	x = getCenterX(strlen("Play Again - SPACE"), 30);

	draw_text(sdl.renderer, game_over_small_font, &texture_text, &play, x, 310, "Play Again - SPACE");
	SDL_RenderCopy(sdl.renderer, texture_text, NULL, &play);

	x = getCenterX(strlen("QUIT - ESCAPE"), 30);

	draw_text(sdl.renderer, game_over_small_font, &texture_text, &exit_text, x, 380, "QUIT - ESCAPE");
	SDL_RenderCopy(sdl.renderer, texture_text, NULL, &exit_text);



	int top_score = read_score();

	char score_text[100];
	sprintf(score_text, "Top Score: %03d", top_score);

	x = getCenterX(strlen(score_text), 20);

	draw_text(sdl.renderer, score_very_small_font, &texture_text, &exit_text, x, 560, score_text);
	SDL_RenderCopy(sdl.renderer, texture_text, NULL, &exit_text);

	char player_score_text[100];
	sprintf(player_score_text, "Your Score: %03d", game.score);

	x = getCenterX(strlen(player_score_text), 20);

	draw_text(sdl.renderer, score_very_small_font, &texture_text, &exit_text, x, 600, player_score_text);
	SDL_RenderCopy(sdl.renderer, texture_text, NULL, &exit_text);

}

void game_over_font_close()
{
	TTF_CloseFont(game_over_tittle);
	TTF_CloseFont(game_over_small_font);
	TTF_CloseFont(score_very_small_font);

	SDL_DestroyTexture(texture_text);
}
