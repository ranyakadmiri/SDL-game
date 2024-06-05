#include "collisionparfaite.h"

SDL_Color getpixel(SDL_Surface *pSurface, int x, int y)
{
	SDL_Color color;
	Uint32 col = 0;
	char *pPosition = (char *)pSurface->pixels;
	pPosition += (pSurface->pitch * y);
	pPosition += (pSurface->format->BytesPerPixel * x);
	memcpy(&col, pPosition, pSurface->format->BytesPerPixel);
	SDL_GetRGB(col, pSurface->format, &color.r, &color.g, &color.b);
	return (color);
}
int collisionparfaite(SDL_Surface *psurface, Personne p)
{
	int tabx[7], taby[7], i;
	SDL_Color color1, color;
	color1.r = 0;
	color1.g = 0;
	color1.b = 0;
	tabx[0] = p.screen_pos.x;
	tabx[1] = (p.screen_pos.x) + ((p.size.w) / 2);
	tabx[2] = (p.screen_pos.x + p.size.w);
	tabx[3] = p.screen_pos.x;
	tabx[4] = p.screen_pos.x;
	tabx[5] = (p.screen_pos.x) + ((p.size.w) / 2);
	tabx[6] = (p.screen_pos.x + p.size.w);
	tabx[7] = (p.screen_pos.x + p.size.w);
	taby[0] = p.screen_pos.y;
	taby[1] = p.screen_pos.y;
	taby[2] = p.screen_pos.y;
	taby[3] = (p.screen_pos.y) + ((p.size.h) / 2);
	taby[4] = (p.screen_pos.y + p.size.h);
	taby[5] = (p.screen_pos.y + p.size.h);
	taby[6] = (p.screen_pos.y + p.size.h);
	taby[7] = (p.screen_pos.y) + ((p.size.h) / 2);

	for (i = 0; i < 8; i++)
	{
		color = getpixel(psurface, tabx[i], taby[i]);
		if (color.r == color1.r && color.b == color1.b && color.g == color1.g)
		{
			return i;
		}
	}
	return 10;
}

void collision(SDL_Surface *psurface, Personne *p, int dt)
{
	int i;
	i = collisionparfaite(psurface, *p);
	int dx = ((0.5 * p->acceleration) * (dt * dt)) + (p->vitesse * dt);

	switch (i)
	{
	case 0:
		p->screen_pos.y = p->screen_pos.y + dx;
		break;
	case 1:
		p->screen_pos.y = p->screen_pos.y + dx;
		break;
	case 2:
		p->screen_pos.y = p->screen_pos.y + dx;
		break;
	case 3:
		p->screen_pos.x = p->screen_pos.x + dx;
		break;
	case 4:
		p->screen_pos.y = p->screen_pos.y - dx;
		break;
	case 5:
		p->screen_pos.y = p->screen_pos.y - dx;
		break;
	case 6:
		p->screen_pos.y = p->screen_pos.y - dx;
		break;
	case 7:
		p->screen_pos.x = p->screen_pos.x - dx;
		break;
	}
}
