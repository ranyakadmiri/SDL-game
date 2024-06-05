/**
 * @file ennemie.c 
 */
#include "ennemie.h"



int 
nb_frame1=12 ,
ennemie_h=245,
ennemie_w=108,
ennemie_y=100,
ennemie_x=100;


void init_tab_anim_ennemie(SDL_Rect *clip,Ennemie *e,int nb_frame1)
{	


for (int j=0;j<nb_frame1; j++)
	{
	clip[j].h=ennemie_h;
	clip[j].w=ennemie_w;
	clip[j].x = j*ennemie_w;
	clip[j].y = 0;
        }


}




void initEnnemi(Ennemie *e,char *name,int nb_frame1)
{

    e->ennemie = IMG_Load(name);

    e->pos_ennemie.x =900;
    e->pos_ennemie.y =250;
    init_tab_anim_ennemie(e->anim_ennemie,e,nb_frame1);
    e->frame_ennemie=0;
    e->direction=0;  
    e->col=0;
    e->affich=1;
    
    
}


void afficherEnnemi(Ennemie e, SDL_Surface *screen)
{
   
   SDL_BlitSurface(e.ennemie,&e.anim_ennemie[e.frame_ennemie], screen, &e.pos_ennemie);
  
  

}


void deplacerIA(Ennemie *e, Personne *p)
{	srand (time(0));
	int diff;
	int maxi_left=300+rand()%300;
	int maxi_right=50+rand()%300;

  	printf("maxleft : %d\tmaxright : %d\n",maxi_left,maxi_right );


if(e->pos_ennemie.x>= maxi_right)
{
e->direction =1;
}
if(e->pos_ennemie.x<=maxi_left)
{
e->direction =0;
}

if(e->direction==1)
{   
	e->pos_ennemie.x-=7;

}
if(e->direction==0)
{
	e->pos_ennemie.x+=7;
}

  diff=e->pos_ennemie.x-p->screen_pos.x;
  
  if (diff<350 && diff>50 ){

e->pos_ennemie.x-=3;
  }

if (diff >-350 && diff < 0){
  
  e->pos_ennemie.x+=3;
  }


}


void animerEnnemi(Ennemie *e)
{   if (e->frame_ennemie >=0 && e->frame_ennemie <(nb_frame1-1)) 
 e->frame_ennemie++;
    if ( e->frame_ennemie ==(nb_frame1-1)) 
       e->frame_ennemie=0;
}



void update_ennemie(Ennemie *e,Personne * p )
{ 	deplacerIA(e,p);
	animerEnnemi(e);
	

}
void update_ennemiez(Ennemie *e,Personne * p)
{ 	
	animerEnnemi(e);
	

}




    
    



int detect_collision_ennemie(Personne * p, Ennemie *e)
{
	

if ((p->screen_pos.x + p->screen_pos. w< e->pos_ennemie. x) || (p->screen_pos.x> e->pos_ennemie. x + e->pos_ennemie. w) ||
(p->screen_pos.y + p->screen_pos.h< e->pos_ennemie. y) || (p->screen_pos.y> e->pos_ennemie. y + e->pos_ennemie. h ))
return 0;
else 
return 1;
 
}

int gerer(Ennemie *e) {
	
	e->affich=0;
	
	return 0; 
}








