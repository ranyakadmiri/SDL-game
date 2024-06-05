#include <SDL/SDL.h>

#include <SDL/SDL_image.h>

#include <SDL/SDL_video.h>

#include "Functions/image.h"

#include "Functions/text.h"

#include "Functions/music.h"

#include "Functions/minimap.h"

#include "Functions/temps.h"

#include "Functions/score.h"

#include "Functions/save.h"

#include "Functions/perso.h"

#include "Functions/collisionparfaite.h"

#include "Functions/background.h"

int main()
{
  if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
  {
    printf("error ! %s", SDL_GetError());
  }
  TTF_Init();
  // Inisialisation des variables
  int t_prev = SDL_GetTicks();
  int game_end = 0;
  int text_zone = -1;
  int i = 0, j = 0, k = 0, soundvolume = 4, screenmode = 1, volume = 4;
  SDL_EnableKeyRepeat(100, 10);
  int x_mouse, y_mouse;
  Text t;
  Mix_Music *music;
  Mix_Chunk *son = NULL;
  image bg, bg_2, new_game_1, new_game_2, option_1, option_2, resume_1, resume_2, exit_1, exit_2, option_bg, volume_0, volume_25, volume_50, volume_75, volume_100,
      sound_selected, screen_selected, windowed, fullscreen;
  SDL_Surface *screen;
  SDL_Event event, event_option;
  SDL_Rect camera;
  // creating window
  screen = SDL_SetVideoMode(800, 600, 32, SDL_HWSURFACE | SDL_DOUBLEBUF | SDL_RESIZABLE);
  Personne perso;
  init_perso(&perso);
  int dt;
  minimap m;
  temps te;
  init_map(&m);
  initialiser_temps(&te);
  int valeur_score = 0;
  score s;
  initialiser_score(valeur_score, &s);
  background ba;
  background bm;
  initialisation_back(&ba); // initback
  initBackMasque(&bm);      // pour la collision parfaite

  if (screen == NULL)
  {
    printf("error ! %s", SDL_GetError());
  }
  init_everything(&bg, &bg_2, &new_game_1, &new_game_2, &option_1, &option_2, &resume_1, &resume_2, &exit_1, &exit_2, &option_bg, &volume_0, &volume_25, &volume_50, &volume_75, &volume_100, &sound_selected, &screen_selected, &windowed, &fullscreen);
  // initText(&t,150,200);
  son_continue("music/music.mp3", music);
  display_image(bg, screen);
  display_image(new_game_1, screen);
  display_image(option_1, screen);
  display_image(resume_1, screen);
  display_image(exit_1, screen);
  SDL_Flip(screen);
  while (game_end == 0)
  {
  }
}