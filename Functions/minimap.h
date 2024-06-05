#ifndef minimap_H
#define minimao_H
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

typedef struct
{
    SDL_Surface *map;            // image miniature
    SDL_Surface *minijoueur;     // joueur miniature(pt par exemple)
    SDL_Rect positionmap;        // position minimap
    SDL_Rect positionminijoueur; // position bonhomme
} minimap;
void init_map(minimap *m);
void MAJMinimap(SDL_Rect posJoueur, minimap *m, SDL_Rect camera, int redimensionnement); // calculer la position du bonhomme
void afficherminimap(minimap m, SDL_Surface *screen);
#endif
