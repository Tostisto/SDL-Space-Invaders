#include "game.h"

void logic();
void draw();

void player_init();
void player_control();
void player_check();

void enemy();
void enemy_spawn();
void draw_enemy();
void enemy_lives_draw(Entity *enemy);

void bullet();
void shot_bullet();
int bullet_hit(Entity *bullet);
void draw_bullet();

void game_borders();
int player_health(Entity *enemy);
void draw_stats();

Entity *player;
SDL_Texture *player_texture;
SDL_Texture *enemy_texture;
SDL_Texture *bullet_texture;

Mix_Chunk *shot;
Mix_Chunk *explosion;
Mix_Chunk *gameover;

TTF_Font *font;
SDL_Rect score, lives;
SDL_Texture *texture;

int spawn_speed;
int reload;

void logic()
{
	player_control();

	player_check();

	enemy();

	enemy_spawn();

	bullet();

	game_borders();
}

void init_game()
{
	sdl.logic = logic;
	sdl.draw = draw;

	player_texture = loadTexture("resources/img/player.png");
	enemy_texture = loadTexture("resources/img/enemy.png");
	bullet_texture = loadTexture("resources/img/bullet.png");

	shot = Mix_LoadWAV("resources/Audio/fire.wav");
	explosion = Mix_LoadWAV("resources/Audio/explosion.wav");
	gameover = Mix_LoadWAV("resources/Audio/gameover.wav");

	font = TTF_OpenFont("resources/font/dogica.ttf", 25);

	memset(&game, 0, sizeof(Game));
	memset(&input_key, 0, sizeof(Input));

	game.enemyTail = &game.enemyHead;
	game.bulletTail = &game.bulletHead;

	player_init();
}

void player_init()
{
	player = calloc(1, sizeof(Entity));

	game.enemyTail->other = player;
	game.enemyTail = player;

	player->texture = player_texture;
	SDL_QueryTexture(player->texture, NULL, NULL, &player->width, &player->height);

	player->x = SCREEN_WIDTH / 2;
	player->y = SCREEN_HEIGHT / 1.2;

	player->lives = player_lives;
	player->entity_type = "player";
}

void player_control()
{
	player->move_x = player->move_y = 0;

	if (input_key.up)
	{
		player->move_y = -10;
	}

	if (input_key.down)
	{
		player->move_y = 10;
	}

	if (input_key.left)
	{
		player->move_x = -10;
	}
	if (input_key.right)
	{
		player->move_x = 10;
	}
	if (input_key.space && reload <= 0)
	{
		shot_bullet();
		Mix_PlayChannel(-1, shot, 0);
	}
	if (input_key.esc)
	{
		SDL_close();
	}
}

void enemy()
{
	Entity *enemy, *prev;

	prev = &game.enemyHead;

	for (enemy = game.enemyHead.other; enemy != NULL; enemy = enemy->other)
	{
		enemy->x += enemy->move_x;
		enemy->y += enemy->move_y;

		if (enemy != player && (enemy->y - 100 > SCREEN_HEIGHT || enemy->lives == 0 || player_health(enemy)))
		{
			if (enemy == game.enemyTail)
			{
				game.enemyTail = prev;
			}
			prev->other = enemy->other;
			free(enemy);
			enemy = prev;
		}
		prev = enemy;
	}
}

void enemy_spawn()
{
	Entity *enemy;

	spawn_speed--;

	if (spawn_speed <= 0)
	{
		enemy = calloc(1, sizeof(Entity));

		game.enemyTail->other = enemy;
		game.enemyTail = enemy;

		srand(time(NULL));
		enemy->x = rand() % (SCREEN_WIDTH - 100);

		enemy->y = 0;
		enemy->texture = enemy_texture;
		SDL_QueryTexture(enemy->texture, NULL, NULL, &enemy->width, &enemy->height);

		enemy->move_y = enemy_Speed;

		enemy->entity_type = "enemy";
		enemy->lives = enemy_lives;
		spawn_speed = enemy_SpawnSpeed;
	}
}

void shot_bullet()
{
	Entity *bullet;

	bullet = calloc(1, sizeof(Entity));

	game.bulletTail->other = bullet;
	game.bulletTail = bullet;
	bullet->x = player->x;
	bullet->y = player->y;
	bullet->move_y = -15;
	bullet->texture = bullet_texture;
	SDL_QueryTexture(bullet->texture, NULL, NULL, &bullet->width, &bullet->height);

	bullet->x += (player->width / 2) - (bullet->width / 2);

	reload = 10;
}

void bullet()
{
	Entity *bullet, *prev;

	prev = &game.bulletHead;

	for (bullet = game.bulletHead.other; bullet != NULL; bullet = bullet->other)
	{
		bullet->y += bullet->move_y;

		if (bullet_hit(bullet) || bullet->y < -bullet->y)
		{
			if (bullet == game.bulletTail)
			{
				game.bulletTail = prev;
			}
			prev->other = bullet->other;
			free(bullet);
			bullet = prev;
		}
		prev = bullet;
	}
}

int min(int a, int b)
{
	return (a < b) ? a : b;
}

int max(int a, int b)
{
	return (a > b) ? a : b;
}

int collision_entity(Entity *entity1, Entity *entity2)
{
	return (min(entity1->y + entity1->height, entity2->y + entity2->height) > max(entity1->y, entity2->y)) && (min(entity1->x + entity1->width, entity2->x + entity2->width) > max(entity1->x, entity2->x));
}

int player_health(Entity *enemy)
{
	if (collision_entity(player, enemy))
	{
		player->lives--;

		Mix_PlayChannel(-1, explosion, 0);

		return 1;
	}

	if (enemy->y > SCREEN_HEIGHT)
	{
		player->lives--;

		return 1;
	}

	return 0;
}

void write_score(int score)
{
	FILE *file;
	file = fopen("gameData/data", "wb");
	fprintf(file, "%d", score);
	fclose(file);
}

int read_score()
{
	FILE *file;
	int score;
	file = fopen("gameData/data", "rb");
	fscanf(file, "%d", &score);
	fclose(file);
	return score;
}

void player_check()
{
	if (player->lives < 1)
	{
		if(game.score > read_score())
		{
			write_score(game.score);
		}

		game_over();

		Mix_PlayChannel(-1, gameover, 0);
	}

	if (reload > 0)
	{
		reload--;
	}
}

int bullet_hit(Entity *bullet)
{
	Entity *enemy;

	for (enemy = game.enemyHead.other; enemy != NULL; enemy = enemy->other)
	{
		if (collision_entity(bullet, enemy))
		{
			if (enemy->entity_type == "enemy")
			{
				enemy->lives--;

				if (enemy->lives == 0)
				{
					Mix_PlayChannel(-1, explosion, 0);

					game.score += 10;
				}
				return 1;
			}
		}
	}
	return 0;
}

void game_borders()
{
	if (player->x < 0)
	{
		player->x = 0;
	}

	if (player->y < 0)
	{
		player->y = 0;
	}

	if (player->x > SCREEN_WIDTH - player->width)
	{
		player->x = SCREEN_WIDTH - player->width;
	}

	if (player->y > SCREEN_HEIGHT - player->height)
	{
		player->y = SCREEN_HEIGHT - player->height;
	}
}

void draw_enemy()
{
	Entity *enemy;

	for (enemy = game.enemyHead.other; enemy != NULL; enemy = enemy->other)
	{
		draw_texture(enemy->texture, enemy->x, enemy->y);

		if (enemy->entity_type == "enemy")
		{
			enemy_lives_draw(enemy);
		}
	}
}

void enemy_lives_draw(Entity *enemy)
{
	float max_width = 91;
	float max_height = 12;

	SDL_Rect lives_background = {
		.x = enemy->x,
		.y = enemy->y - 30,
		.w = max_width,
		.h = max_height};

	SDL_SetRenderDrawColor(sdl.renderer, 255, 0, 0, 0);
	SDL_RenderFillRect(sdl.renderer, &lives_background);
	SDL_RenderDrawRect(sdl.renderer, &lives_background);

	SDL_Rect lives = {
		.x = enemy->x,
		.y = enemy->y - 30};

	int health_percentage = (enemy->lives * 100) / enemy_lives;

	lives.w = health_percentage * (max_width / 100.0);

	lives.h = max_height;

	SDL_SetRenderDrawColor(sdl.renderer, 0, 255, 0, 0);
	SDL_RenderFillRect(sdl.renderer, &lives);
	SDL_RenderDrawRect(sdl.renderer, &lives);
}

void draw_bullet()
{
	Entity *bullet;

	for (bullet = game.bulletHead.other; bullet != NULL; bullet = bullet->other)
	{
		draw_texture(bullet->texture, bullet->x, bullet->y);
	}
}

void draw_stats()
{
	char text_score[20];
	char text_lives[20];

	sprintf(text_score, "Score: %03d", game.score);
	sprintf(text_lives, "Lives: %03d", player->lives);

	draw_text(sdl.renderer, font, &texture, &score, 10, 10, text_score);
	SDL_RenderCopy(sdl.renderer, texture, NULL, &score);

	draw_text(sdl.renderer, font, &texture, &lives, 10, 50, text_lives);
	SDL_RenderCopy(sdl.renderer, texture, NULL, &lives);
}

void draw()
{
	draw_enemy();

	draw_bullet();

	draw_stats();
}

void game_font_close()
{
	TTF_CloseFont(font);

	SDL_DestroyTexture(texture);
}

void game_sound_close()
{
	Mix_FreeChunk(shot);

	Mix_FreeChunk(explosion);

	Mix_FreeChunk(gameover);

	Mix_CloseAudio();

	Mix_Quit();
}

void SDL_close()
{
	game_over_font_close();

	menu_font_close();

	game_font_close();

	TTF_Quit();

	game_sound_close();

	SDL_DestroyRenderer(sdl.renderer);

	SDL_DestroyWindow(sdl.window);

	SDL_Quit();

	exit(0);
}