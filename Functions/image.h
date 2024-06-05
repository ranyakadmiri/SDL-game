#ifndef IMAGE_H
#define IMAGE_H
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
typedef struct
{
	SDL_Rect place_on_screen, img_size;
	SDL_Surface *img_url;
} image;
void init_bg(image *background, char *name);
void display_image(image background, SDL_Surface *screen);
void init_boutton(image *background, char *name, int x, int y);
void init_everything(image *background, image *background_2, image *new_game_1, image *new_game_2, image *option_1, image *option_2, image *resume_1, image *resume_2, image *exit_1, image *exit_2, image *option_bg, image *volume_0, image *volume_25, image *volume_50, image *volume_75, image *volume_100, image *sound_selected, image *screen_selected, image *windowed, image *fullscreen);
void init_menu_to_0(image *new_game_1, image *new_game_2, image *option_1, image *option_2, image *resume_1, image *resume_2, image *exit_1, image *exit_2);
void libere_image(image background);
#endif
