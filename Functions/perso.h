#ifndef PERSO_H
#define PERSO_H
typedef struct
{
	SDL_Surface *mat[4][4];
	SDL_Surface *mat_perso_2[4][4];
	SDL_Rect screen_pos;
	SDL_Rect size;
	SDL_Rect saut;
	int up;
	int direction;
	int direction_2;
	int num;
	int num_2;
	int score;
	int live;
	int attack_detection;
	double vitesse;
	double acceleration;
	int detection_acceleration;
} Personne;
void init_perso(Personne *p);
void afficherPerso(Personne p, SDL_Surface *screen);
void deplacerPerso(Personne *p, Uint32 dt);
void animerPerso(Personne *p);
void jump(Personne *P, int dt, int posinit);
void saut_p(Personne *p, Uint32 dt, int posx_absolu, int posy_absolu);
#endif
