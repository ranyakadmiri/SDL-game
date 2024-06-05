#include "background.h"
#include <SDL/SDL_mixer.h>

void initBackMasque(background *b)
{
	// background
	b->imgback = IMG_Load("Images/Game/mapmask.png");
	b->posback.x = 0;
	b->posback.y = 0;

	// camera
	b->camera.x = 0;
	b->camera.y = 0;
	b->camera.w = SCREEN_W;
	b->camera.h = SCREEN_H;
}

void initBack2(background *b)
{
	// background2
	b->imgback = IMG_Load("Images/Game/map.png");
	b->posback2.x = 0;
	b->posback2.y = 0;
	// camera2
	b->camera2.x = 0;
	b->camera2.y = 0;
	b->camera2.w = SCREEN_W;
	b->camera2.h = SCREEN_H;
	// musique //Chargement de la musique
}

void initialisation_back(background *b)
{
	// initBack(b);
	initBack2(b);
}

void afficheBack(background b, SDL_Surface *ecran)
{
	/* On blitte par-dessus l'écran */
	SDL_BlitSurface(b.imgback, &b.camera, ecran, &b.posback); // affich background sur ecran
}

void afficheBack2(background b, SDL_Surface *ecran)
{
	/* On blitte par-dessus l'écran */
	SDL_BlitSurface(b.imgback, &b.camera2, ecran, &b.posback2);
}
/*void afficher_back(background b, SDL_Surface *ecran)
{
	afficheBack(b,ecran);
	afficheBack2(b,ecran);

}*/

void scrolling(background *b, int direction)
{
	const int speed = 1;
	if (direction == 0)
	{ // rightbac1
		b->camera.x += speed;

		b->camera2.x += speed;
	}
	else if (direction == 1)
	{ // leftbac1
		b->camera.x -= speed;

		b->camera2.x -= speed;
	}
	else if (direction == 4)
	{ // rightbac2
		b->camera2.x += speed;
	}
	else if (direction == 7)
	{ // leftback2
		b->camera2.x -= speed;
	}
	else if (direction == 2)
	{ // leftback2
		b->camera.y -= speed * 3;

		b->camera2.y -= speed * 3;
	}
	else if (direction == 3)
	{ // rightback2
		b->camera.y += speed * 3;

		b->camera2.y += speed * 3;
	}
}
void displayFlower(background b, SDL_Surface *ecran)
{

	SDL_BlitSurface(b.image_flower, &(b.single_flower), ecran, &b.pos_image_flower);
}
void animerBackground(background *b)
{

	if (b->flower_num >= 0 && b->flower_num < 8)
	{
		b->single_flower.x = b->flower_num * b->single_flower.w;
		b->flower_num++;
	}

	if (b->flower_num == 8)
	{
		b->single_flower.x = b->flower_num * b->single_flower.w;
		b->flower_num = 0;
	}
}
