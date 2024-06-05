
#include "entity.h"

int
	nb_frame = 7,
	entity_h = 100,
	entity_w = 100,
	entity_y = 100,
	entity_x = 100;

void init_tab_anim_entity(SDL_Rect *clip, entity *e)
{
	for (int j = 0; j < nb_frame; j++)
	{
		clip[j].h = entity_h;
		clip[j].w = entity_w;
		clip[j].x = j * entity_x;
		clip[j].y = 0;
	}
}

void initentity(entity *e)
{

	e->entity = IMG_Load("fire.png");

	e->pos_entity.x = 200;
	e->pos_entity.y = 400;
	init_tab_anim_entity(e->anim_entity, e);
	e->frame_entity = 0;
	e->direction = 0;
	e->col = 0;
	e->affich = 1;
}

void afficherentity(entity e, SDL_Surface *screen)
{

	SDL_BlitSurface(e.entity, &e.anim_entity[e.frame_entity], screen, &e.pos_entity);
}

void animerentity(entity *e)
{
	if (e->frame_entity >= 0 && e->frame_entity < (nb_frame - 1))
		e->frame_entity++;

	if (e->frame_entity == (nb_frame - 1))
		e->frame_entity = 0;
}

void update_entity(entity *e)
{
	// deplacer(e);
	animerentity(e);
}

int detect_collision(Personne *p, entity *e)
{
	if ((p->screen_pos.x + p->size.w < e->pos_entity.x) || (p->screen_pos.x > e->pos_entity.x + e->pos_entity.w) ||
		(p->screen_pos.y + p->size.h < e->pos_entity.y) || (p->screen_pos.y > e->pos_entity.y + e->pos_entity.h))
		return 0;
	else
		return 1;
}

int gestion(entity *e)
{
	e->affich = 0;
	return 0;
}
