#include "minimap.h"
#include <SDL/SDL.h>

void init_map(minimap *m)
{
  m->map = IMG_Load("Images/Game/minimap.png");
  m->minijoueur = IMG_Load("Images/Game/persomini.png");
  m->positionmap.x = 400;
  m->positionmap.y = 20;
  m->positionminijoueur.x = 450;
  m->positionminijoueur.y = 245;
}

void MAJMinimap(SDL_Rect posJoueur, minimap *m, SDL_Rect camera, int redimensionnement)
{
  SDL_Rect posJoueurABS; // position absolue de joueur
  posJoueurABS.x = 0;
  posJoueurABS.y = 0; // 560 236
  posJoueurABS.x = posJoueur.x;
  posJoueurABS.y = posJoueur.y;
  m->positionminijoueur.x = (posJoueurABS.x * 560) / 1200 + 400;
  m->positionminijoueur.y = (posJoueurABS.y * 236) / 600 + 85;
}

void afficherminimap(minimap m, SDL_Surface *screen)
{
  SDL_BlitSurface(m.map, NULL, screen, &m.positionmap);
  SDL_BlitSurface(m.minijoueur, NULL, screen, &m.positionminijoueur);
}
