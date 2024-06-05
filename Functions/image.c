#include "image.h"
void init_bg(image *background, char *name)
{
	background->img_url = IMG_Load(name);
	if (background->img_url == NULL)
	{
		printf("Cannot load image");
		return;
	}
	background->place_on_screen.x = 0;
	background->place_on_screen.y = 0;
	background->img_size.w = background->img_url->w;
	background->img_size.h = background->img_url->h;
	background->img_size.x = 0;
	background->img_size.y = 0;
}
void init_boutton(image *background, char *name, int x, int y)
{
	background->img_url = IMG_Load(name);
	if (background->img_url == NULL)
	{
		printf("Cannot load image");
		return;
	}
	background->place_on_screen.x = x;
	background->place_on_screen.y = y;
	background->img_size.w = background->img_url->w;
	background->img_size.h = background->img_url->h;
	background->img_size.x = 0;
	background->img_size.y = 0;
}
void init_everything(image *background, image *background_2, image *new_game_1, image *new_game_2, image *option_1, image *option_2, image *resume_1, image *resume_2, image *exit_1, image *exit_2, image *option_bg, image *volume_0, image *volume_25, image *volume_50, image *volume_75, image *volume_100, image *sound_selected, image *screen_selected, image *windowed, image *fullscreen)
{
	init_bg(background, "Images/bg_new.png");
	init_bg(background_2, "Images/Game/map.png");
	init_bg(option_bg, "Images/Option Menu/Option_Menu_Final.png");
	init_boutton(volume_0, "Images/Option Menu/Sound(0%).png", 290, 305);
	init_boutton(volume_25, "Images/Option Menu/Sound(25%).png", 290, 305);
	init_boutton(volume_50, "Images/Option Menu/Sound(50%).png", 290, 305);
	init_boutton(volume_75, "Images/Option Menu/Sound(75%).png", 290, 305);
	init_boutton(volume_100, "Images/Option Menu/Sound(100%).png", 290, 308);
	init_boutton(windowed, "Images/Option Menu/windowed.png", 350, 366);
	init_boutton(fullscreen, "Images/Option Menu/full screen.png", 350, 366);
	init_boutton(sound_selected, "Images/Option Menu/Sound Selected.png", 203, 306);
	init_boutton(screen_selected, "Images/Option Menu/screen mode.png", 203, 366);
	init_boutton(new_game_1, "Images/new_game.png", 240, 282);
	init_boutton(option_1, "Images/option.png", 236, 405);
	init_boutton(resume_1, "Images/resume.png", 237, 345);
	init_boutton(exit_1, "Images/exit.png", 230, 464);
	init_boutton(new_game_2, "Images/newgame2.png", 240, 282);
	init_boutton(resume_2, "Images/resume2.png", 237, 345);
	init_boutton(option_2, "Images/option2.png", 236, 405);
	init_boutton(exit_2, "Images/exit2.png", 228, 464);
}
void init_menu_to_0(image *new_game_1, image *new_game_2, image *option_1, image *option_2, image *resume_1, image *resume_2, image *exit_1, image *exit_2)
{
	init_boutton(new_game_1, "Images/new_game.png", -1000, -1000);
	init_boutton(option_1, "Images/option.png", -1000, -1000);
	init_boutton(resume_1, "Images/resume.png", -1000, -1000);
	init_boutton(exit_1, "Images/exit.png", -1000, -1000);
	init_boutton(new_game_2, "Images/newgame2.png", -1000, -1000);
	init_boutton(resume_2, "Images/resume2.png", -1000, -1000);
	init_boutton(option_2, "Images/option2.png", -1000, -1000);
	init_boutton(exit_2, "Images/exit2.png", -1000, -1000);
}
void display_image(image background, SDL_Surface *screen)
{
	SDL_BlitSurface(background.img_url, &background.img_size, screen, &background.place_on_screen);
}
void libere_image(image background)
{
	SDL_FreeSurface(background.img_url);
}
