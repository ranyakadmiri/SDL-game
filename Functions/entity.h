#ifndef entite_H_INCLUDED 
#define entite_H_INCLUDED

#include <stdio.h>     
#include <stdlib.h>
#include <SDL/SDL.h>
#include <stdbool.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include "perso.h"
#include<time.h>

typedef struct {   
	  

	SDL_Surface *entity; 
	SDL_Rect pos_entity; 
	SDL_Rect anim_entity[70];  // l tab ali fih l les surfaces mta3 kol frame  o kol frame andha indice ( frame_entity )
	int frame_entity;
	int direction;
	int col ;
	int maxi_up,maxi_down;
	int affich;

}entity ;


void init_tab_anim_entity(SDL_Rect* clip,entity *e);   
void initentity (entity *e) ;
void afficherentity(entity e , SDL_Surface *screen);
void animerentity(entity *e);
void update_entity(entity *e);
int detect_collision(Personne *p, entity* e);  
int gestion(entity* e);
void initialiser_perso(Personne *p);
void afficher_perso(Personne p , SDL_Surface *screen);


#endif 
