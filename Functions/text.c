#include <SDL/SDL.h>
#include "text.h"
#include <SDL/SDL_image.h>

void initText(Text *t, float x, float y)
{
	t->place_on_screen.x = x;
	t->place_on_screen.y = y;
	t->textcolor.r = 200;
	t->textcolor.g = 50;
	t->textcolor.b = 120;
	t->font = TTF_OpenFont("Fonts/pixo-reto-sp/PixoRetoSP-Regular.ttf", 50);
}
void display_text(Text t, SDL_Surface *screen, char text[])
{
	t.surfaceTexte = TTF_RenderText_Solid(t.font, text, t.textcolor);  // render Text on SurfaceText
	SDL_BlitSurface(t.surfaceTexte, NULL, screen, &t.place_on_screen); // display SurfaceText on screen
}
void free_texte(Text t)
{
	SDL_FreeSurface(t.surfaceTexte);
}
