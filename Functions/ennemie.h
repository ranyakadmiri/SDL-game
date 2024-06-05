#ifndef ENNEMIE_H_INCLUDED
#define ENNEMIE_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <stdbool.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_mixer.h>
#include <time.h>
#include "entity.h"

typedef struct
{
	SDL_Surface *ennemie;
	SDL_Rect pos_ennemie;
	SDL_Rect anim_ennemie[70];
	int frame_ennemie;
	int direction;
	int col;
	int type;
	int maxi_left, maxi_right;
	int affich;

} Ennemie;

void init_tab_anim_ennemie(SDL_Rect *clip, Ennemie *e, int nb_frame1);
void initEnnemi(Ennemie *e, char *name, int nb_frame1);
void afficherEnnemi(Ennemie e, SDL_Surface *screen);
void animerEnnemi(Ennemie *e);
void deplacerIA(Ennemie *e, Personne *p);
void update_ennemie(Ennemie *e, Personne *p);
void update_ennemiez(Ennemie *e, Personne *p);

int detect_collision_ennemie(Personne *p, Ennemie *e);

int gerer(Ennemie *e);

#endif
