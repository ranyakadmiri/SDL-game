#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_video.h>
#include "perso.h"
#include "image.h"
void init_perso(Personne *p)
{
	p->mat[0][0] = IMG_Load("Pictures/WALKING_RIGHT/STANDING.png");
	p->mat[0][1] = IMG_Load("Pictures/WALKING_RIGHT/WALKING_1.png");
	p->mat[0][2] = IMG_Load("Pictures/WALKING_RIGHT/WALKING_2.png");
	p->mat[1][0] = IMG_Load("Pictures/WALKING LEFT/WALK1.png");
	p->mat[1][1] = IMG_Load("Pictures/WALKING LEFT/WALK2.png");
	p->mat[1][2] = IMG_Load("Pictures/WALKING LEFT/WALK3.png");
	p->mat[2][0] = IMG_Load("Pictures/JUMP RIGHT/JUMP 1.png");
	p->mat[2][1] = IMG_Load("Pictures/JUMP RIGHT/JUMP 2.png");
	p->mat[2][2] = IMG_Load("Pictures/JUMP RIGHT/JUMP 3.png");
	p->mat[2][3] = IMG_Load("Pictures/JUMP RIGHT/JUMP 4.png");
	p->mat[3][0] = IMG_Load("Pictures/JUMP LEFT/JUMP_L 1.png");
	p->mat[3][1] = IMG_Load("Pictures/JUMP LEFT/JUMP_L 2.png");
	p->mat[3][2] = IMG_Load("Pictures/JUMP LEFT/JUMP_L 3.png");
	p->mat[3][3] = IMG_Load("Pictures/JUMP LEFT/JUMP_L 4.png");
	p->screen_pos.x = 50;
	p->screen_pos.y = 300;
	p->size.w = p->mat[0][0]->w;
	p->size.h = p->mat[0][0]->h;
	
	p->size.x = 0;
	p->size.y = 0;
	p->direction = 0;
	p->num = 0;
	p->score = 0;
	p->live = 100;
	p->vitesse = 5;
	p->acceleration = 0;
	p->detection_acceleration = 0;
	p->up = 0;
	p->saut.x = -50;
	p->saut.y = 0;
	p->attack_detection = 0;
}

void afficherPerso(Personne p, SDL_Surface *screen)
{

	SDL_BlitSurface(p.mat[p.direction][p.num], &p.size, screen, &p.screen_pos);
}
void deplacerPerso(Personne *p, Uint32 dt)
{

	double dx, dx_verif;
	dx = ((0.5 * p->acceleration) * (dt * dt)) + (p->vitesse * dt);

	dx = dx - 365;
	if (dx <= 0)
	{
		dx = dx * -1;
		p->acceleration = 0;
	}

	if (p->direction == 0)
	{
		if (p->screen_pos.x + dx <= 1050)
			p->screen_pos.x += dx;
	}
	else if (p->direction == 1)
	{
		if (p->screen_pos.x - dx >= 70)
			p->screen_pos.x -= dx;
	}
	if (p->detection_acceleration == 1)
	{
		p->acceleration += 0.005;
		dx += p->acceleration;
	}
	else if (p->detection_acceleration == -1)
	{
		p->acceleration -= 0.005;
		dx -= p->acceleration;
	}
}
void animerPerso(Personne *p)
{
	if (p->direction == 0 || p->direction == 1)
	{
		if (p->num == 2)
		{
			p->num = 0;
		}
		else
		{
			p->num++;
		}
	}
	else
	{
		if (p->num == 4)
		{
			p->num = 0;
		}
		else
		{
			p->num++;
		}
	}
}
void saut_p(Personne *p, Uint32 dt, int posx_absolu, int posy_absolu)
{
	int diff;
	if (p->up == 1)
	{
		p->saut.x += 2;
		p->screen_pos.x = posx_absolu;
		p->screen_pos.y = posy_absolu;
		p->saut.y = (-0.04 * (p->saut.x * p->saut.x) + 100);
		p->screen_pos.x = p->screen_pos.x + p->saut.x + 50;
		p->screen_pos.y = p->screen_pos.y - p->saut.y;
		if (p->screen_pos.y <= 100)
		{
			while (p->screen_pos.y <= 300)
			{
				p->screen_pos.y = p->screen_pos.y + 20;
			}
		}

		if (p->saut.x >= 50)
		{
			// p->screen_pos.y=posy_absolu;
			p->saut.x = -50;
			// p->up=0;
		}
		// SDL_Delay(10);
	}
}
void jump(Personne *p, int dt, int posinit)
{
	double dx;
	dx = ((0.5 * p->acceleration) * (dt * dt)) + (p->vitesse * dt);
	dx = dx - 100;
	if (p->up == 1)
	{
		if (p->screen_pos.y > 100)
		{
			p->screen_pos.y += dx;
		}
		else if (p->screen_pos.y <= 100)
		{
			while (p->screen_pos.y < 300)
				p->screen_pos.y = p->screen_pos.y - dx;
		}
	}
	p->up = 0;
}
