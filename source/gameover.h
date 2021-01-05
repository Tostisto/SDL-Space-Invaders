#include "common.h"

extern void init_game();
extern void draw_text(SDL_Renderer *renderer, TTF_Font *font, SDL_Texture **texture, SDL_Rect *rect, int x, int y, char *text);
extern void SDL_close();
extern int getCenterX(int length, int fontSize);
extern int read_score();

extern SDL_Context sdl;
extern Input input_key;
extern Game game;