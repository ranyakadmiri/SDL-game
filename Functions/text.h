#ifndef Texte_H
#define Texte_H
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
typedef struct
{
        SDL_Rect place_on_screen;  // text position on the screen
        TTF_Font *font;            // choosing font  =>  TTF_OpenFont()
        SDL_Surface *surfaceTexte; // TTF_RenderText_Solid()
        SDL_Color textcolor;       // .r , .g , .b , .a

} Text;
void initText(Text *t, float x, float y); // font , color , position
void freeText(Text t);
void display_text(Text t, SDL_Surface *screen, char text[]); // Surface TTF_RenderText_Solid() && SDL_BlitSurface()
void animate_text(Text *t, int *x);
void free_texte(Text t);

#endif
