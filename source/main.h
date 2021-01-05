
#include "common.h"

extern void input();
extern void menu_init();
extern SDL_Texture *loadTexture(char *file);

SDL_Context sdl;
Game game;

Input input_key;