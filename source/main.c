#include "main.h"

int main()
{

	memset(&input_key, 0, sizeof(Input));

	sdl.textureTail = &sdl.textureHead;

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL Error: %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}

	if (TTF_Init() == -1)
	{
		printf("SDL_ttf Error: %s\n", TTF_GetError());
		exit(EXIT_FAILURE);
	}

	sdl.window = SDL_CreateWindow("Space Invaders", 100, 100, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
	sdl.renderer = SDL_CreateRenderer(sdl.window, -1, SDL_RENDERER_ACCELERATED);
	IMG_Init(IMG_INIT_PNG);

	SDL_Texture *background;
	background = loadTexture("resources/img/background.png");

	Mix_Init(0);
	Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 1024);

	Mix_Music *music;
	music = Mix_LoadMUS("resources/Audio/audio-hero-911-SIPML-J-0501.mp3");
	Mix_PlayMusic(music, -1);

	menu_init();

	while (1)
	{
		input();

		SDL_RenderCopy(sdl.renderer, background, NULL, NULL);

		sdl.draw();

		sdl.logic();

		SDL_RenderPresent(sdl.renderer);

		SDL_Delay(16);
	}

	Mix_FreeMusic(music);
	Mix_Quit();

	return 0;
}
