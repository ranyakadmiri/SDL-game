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

#include "Functions/entete.h"

#include "Functions/ennemie.h"

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

  tic tictoc;
  int coup;
  int continuer = 1;
  int joueur;
  initialisation(&tictoc);
  int a, b;
  int an;

  SDL_Surface *lost;
  SDL_Rect pos_lost;
  lost = IMG_Load("gameover.png");
  pos_lost.x = 100;
  pos_lost.y = 200;
  entity e;
  Ennemie en;
  initentity(&e);
  initEnnemi(&en, "ennemiN.png", 12);

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
    // last_val = i;
    if (j == 4)
    {
      affichage(tictoc, screen);
      SDL_Flip(screen);
      if (tictoc.tour < 9 && atilganer(tictoc.tabsuivi) == 0)
      {
        if ((tictoc.tour + joueur) % 2 == 0) // tour du PC
        {
          calcul_coup(tictoc.tabsuivi);
          tictoc.tour++;
        }
        else
        {
          SDL_WaitEvent(&event);
          switch (event.type)
          {
          case SDL_QUIT:
            continuer = 0;
            break;
          case SDL_MOUSEBUTTONUP:
            a = event.button.x / 190;
            b = event.button.y / 190;
            coup = 3 * b + a;
            if (tictoc.tabsuivi[coup] == 0)
            {
              tictoc.tour++;
              tictoc.tabsuivi[coup] = -1;
            }
            break;
          }
        }
      }
      else
      {
        Resultat(tictoc, screen);
        SDL_Delay(2000);
        initialisation(&tictoc);
        j = 0;
      }
    }
    else if (j == 2)
    {
      animerBackground(&ba);
      afficheBack2(ba, screen);
      MAJMinimap(perso.screen_pos, &m, camera, 20);
      afficherminimap(m, screen);
      afficher_temps(&te, screen);
      afficher_score(&s, screen, valeur_score);
      afficherPerso(perso, screen);
      afficherentity(e, screen);
      afficherEnnemi(en, screen);
      t_prev = SDL_GetTicks();
      if (detect_collision(&perso, &e))
      {
        SDL_BlitSurface(lost, NULL, screen, &pos_lost);
      }
      while (SDL_PollEvent(&event))
      {
        switch (event.type)
        {
        case SDL_QUIT:
          game_end = 1;
          break;
        case SDL_KEYDOWN:

          switch (event.key.keysym.sym)
          {
          case SDLK_ESCAPE:
            save(valeur_score);
            j = 1;

            break;
          case SDLK_RIGHT: // walking right
            SDL_Delay(80);
            dt = SDL_GetTicks() - t_prev;
            perso.direction = 0;
            deplacerPerso(&perso, dt);
            animerPerso(&perso);
            if (collisionparfaite(screen, perso) == 10)
            {
              scrolling(&ba, 0); // scrollingymin;
              scrolling(&bm, 0);
            }

            animerBackground(&ba);
            afficheBack2(ba, screen);
            MAJMinimap(perso.screen_pos, &m, camera, 20);
            afficherminimap(m, screen);
            afficher_temps(&te, screen);
            afficher_score(&s, screen, valeur_score);
            collision(screen, &perso, dt);
            afficherPerso(perso, screen);
            update_entity(&e);
            update_ennemie(&en, &perso);
            if (detect_collision(&perso, &e))
              a = gestion(&e);
            afficherentity(e, screen);
            if (detect_collision_ennemie(&perso, &en))
              an = gerer(&en);

            afficherEnnemi(en, screen);

            SDL_Flip(screen);
            break;
          case SDLK_LEFT: // walking left
            SDL_Delay(80);
            dt = SDL_GetTicks() - t_prev;
            perso.direction = 1;
            deplacerPerso(&perso, dt);
            animerPerso(&perso);
            animerBackground(&ba);
            afficheBack2(ba, screen);
            MAJMinimap(perso.screen_pos, &m, camera, 20);
            afficherminimap(m, screen);
            afficher_temps(&te, screen);
            afficher_score(&s, screen, valeur_score);
            collision(screen, &perso, dt);
            afficherPerso(perso, screen);
            update_entity(&e);
            update_ennemie(&en, &perso);
            if (detect_collision(&perso, &e))
              a = gestion(&e);
            afficherentity(e, screen);
            if (detect_collision_ennemie(&perso, &en))
              an = gerer(&en);

            afficherEnnemi(en, screen);

            SDL_Flip(screen);
            if (collisionparfaite(screen, perso) == 10)
            {
              scrolling(&ba, 1); // scrolllingysar;
              scrolling(&bm, 1);
            }

            break;
          case SDLK_LSHIFT: // sprint
            perso.detection_acceleration = 1;
            deplacerPerso(&perso, dt);
            animerPerso(&perso);
            SDL_Delay(80);
            animerBackground(&ba);
            afficheBack2(ba, screen);
            MAJMinimap(perso.screen_pos, &m, camera, 20);
            afficherminimap(m, screen);
            afficher_temps(&te, screen);
            afficher_score(&s, screen, valeur_score);
            collision(screen, &perso, dt);
            afficherPerso(perso, screen);
            update_entity(&e);
            update_ennemie(&en, &perso);
            if (detect_collision(&perso, &e))
              a = gestion(&e);
            afficherentity(e, screen);
            if (detect_collision_ennemie(&perso, &en))
              an = gerer(&en);

            afficherEnnemi(en, screen);

            SDL_Flip(screen);

            break;
          case SDLK_a: // deccelaration
            perso.detection_acceleration = -1;
            deplacerPerso(&perso, dt);
            // animerPerso (&perso);
            SDL_Delay(80);
            animerBackground(&ba);
            afficheBack2(ba, screen);
            MAJMinimap(perso.screen_pos, &m, camera, 20);
            afficherminimap(m, screen);
            afficher_temps(&te, screen);
            afficher_score(&s, screen, valeur_score);
            collision(screen, &perso, dt);
            afficherPerso(perso, screen);
            update_entity(&e);
            update_ennemie(&en, &perso);
            if (detect_collision(&perso, &e))
              a = gestion(&e);
            afficherentity(e, screen);
            if (detect_collision_ennemie(&perso, &en))
              an = gerer(&en);

            afficherEnnemi(en, screen);

            SDL_Flip(screen);

            break;
          case SDLK_SPACE: // saut

            if (perso.screen_pos.y != 200)
            {
              if (collisionparfaite(screen, perso) == 10)
              {
                scrolling(&ba, 2); // scrollingymin;
                scrolling(&bm, 2);
              }
            }
            else if (perso.screen_pos.y <= 200)
            {
              if (collisionparfaite(screen, perso) == 10)
              {
                scrolling(&ba, 3); // scrollingymin;
                scrolling(&bm, 3);
              }
            }

            perso.up = 1;
            dt = SDL_GetTicks() - t_prev;
            if (perso.direction == 0)
              perso.direction = 2;
            else if (perso.direction == 1)
              perso.direction = 3;
            SDL_Delay(80);
            jump(&perso, dt, perso.screen_pos.y);
            deplacerPerso(&perso, dt);
            animerBackground(&ba);
            afficheBack2(ba, screen);
            MAJMinimap(perso.screen_pos, &m, camera, 20);
            afficherminimap(m, screen);
            afficher_temps(&te, screen);
            afficher_score(&s, screen, valeur_score);
            collision(screen, &perso, dt);
            afficherPerso(perso, screen);
            update_entity(&e);
            update_ennemie(&en, &perso);
            if (detect_collision(&perso, &e))
              a = gestion(&e);
            afficherentity(e, screen);
            if (detect_collision_ennemie(&perso, &en))
              an = gerer(&en);

            afficherEnnemi(en, screen);

            SDL_Flip(screen);
            SDL_Delay(10);
            break;
          case SDLK_LCTRL: // saut parabolique
            SDL_Delay(80);
            perso.up = 1;
            if (perso.direction == 0)
              perso.direction = 2;
            else if (perso.direction == 1)
              perso.direction = 3;
            dt = SDL_GetTicks() - t_prev;
            saut_p(&perso, dt, perso.screen_pos.x, perso.screen_pos.y);
            deplacerPerso(&perso, dt);
            animerBackground(&ba);
            afficheBack2(ba, screen);
            MAJMinimap(perso.screen_pos, &m, camera, 20);
            afficherminimap(m, screen);
            afficher_temps(&te, screen);
            afficher_score(&s, screen, valeur_score);
            collision(screen, &perso, dt);
            afficherPerso(perso, screen);
            update_entity(&e);
            update_ennemie(&en, &perso);
            if (detect_collision(&perso, &e))
              a = gestion(&e);
            afficherentity(e, screen);
            if (detect_collision_ennemie(&perso, &en))
              an = gerer(&en);

            afficherEnnemi(en, screen);

            SDL_Flip(screen);
            break;
          case SDLK_q: // attack
            dt = SDL_GetTicks() - t_prev;
            perso.attack_detection = 1;
            if (perso.direction == 0)
              perso.direction = 4;
            else if (perso.direction == 1)
              perso.direction = 5;
            animerPerso(&perso);
            animerBackground(&ba);
            afficheBack2(ba, screen);
            MAJMinimap(perso.screen_pos, &m, camera, 20);
            afficherminimap(m, screen);
            afficher_temps(&te, screen);
            afficher_score(&s, screen, valeur_score);
            collision(screen, &perso, dt);
            afficherPerso(perso, screen);
            update_entity(&e);
            update_ennemie(&en, &perso);
            if (detect_collision(&perso, &e))
              a = gestion(&e);
            afficherentity(e, screen);
            if (detect_collision_ennemie(&perso, &en))
              an = gerer(&en);

            afficherEnnemi(en, screen);

            SDL_Flip(screen);
            perso.score += 1;
            break;
          }
          break;
        }
      }

      collision(screen, &perso, dt);
      afficherPerso(perso, screen);
      update_entity(&e);
      update_ennemie(&en, &perso);
      if (detect_collision(&perso, &e))
        a = gestion(&e);

      if (a)
      {
        afficherentity(e, screen);
      }

      if (detect_collision_ennemie(&perso, &en))
        an = gerer(&en);

      if (an)
      {
        afficherEnnemi(en, screen);
      }
      else
      {
      }

      SDL_Flip(screen);
      continue;
    }
    SDL_PollEvent(&event);

    switch (event.type)
    {
    case SDL_QUIT:
      game_end = 1;
      break;
    case SDL_MOUSEMOTION:
      x_mouse = event.button.x;
      y_mouse = event.button.y;
      if (j == 0)
      {
        if ((x_mouse > 240 && x_mouse < 452) && (y_mouse >= 285 && y_mouse <= 329))
        {
          i = 1;
          // son_bref("music/running.wav",son);
          display_image(new_game_2, screen);
          display_image(resume_1, screen);
          display_image(option_1, screen);
          display_image(exit_1, screen);
          SDL_Flip(screen);
        }
        else if ((x_mouse >= 240 && x_mouse <= 452) && (y_mouse >= 348 && y_mouse <= 394))
        {
          i = 2;
          // son_bref("music/running.wav",son);
          display_image(new_game_1, screen);
          display_image(resume_2, screen);
          display_image(exit_1, screen);
          display_image(option_1, screen);
          SDL_Flip(screen);
        }
        else if ((x_mouse >= 240 && x_mouse <= 452) && (y_mouse >= 410 && y_mouse <= 453))
        {
          i = 3;
          // son_bref("music/running.wav",son);
          display_image(new_game_1, screen);
          display_image(resume_1, screen);
          display_image(option_2, screen);
          display_image(exit_1, screen);
          SDL_Flip(screen);
        }
        else if ((x_mouse >= 240 && x_mouse <= 452) && (y_mouse >= 468 && y_mouse <= 513))
        {
          i = 4;
          // son_bref("music/running.wav",son);
          display_image(new_game_1, screen);
          display_image(resume_1, screen);
          display_image(option_1, screen);
          display_image(exit_2, screen);
          SDL_Flip(screen);
        }
        else
        {

          display_image(new_game_1, screen);
          display_image(resume_1, screen);
          display_image(option_1, screen);
          display_image(exit_1, screen);
          SDL_Flip(screen);
        }
      }
      break;
    case SDL_MOUSEBUTTONDOWN:
      if (i == 1)
      {
        j = 2;
        init_perso(&perso);
        afficheBack2(ba, screen);
        if (screenmode == 1)
          screen = SDL_SetVideoMode(1200, 600, 32, SDL_HWSURFACE | SDL_DOUBLEBUF | SDL_RESIZABLE);
        else
          screen = SDL_SetVideoMode(1200, 600, 32, SDL_HWSURFACE | SDL_DOUBLEBUF | SDL_RESIZABLE | SDL_FULLSCREEN);
        init_menu_to_0(&new_game_1, &new_game_2, &option_1, &option_2, &resume_1, &resume_2, &exit_1, &exit_2);
        son_bref("music/running.wav", son);
        SDL_Flip(screen);
      }
      else if (i == 4)
      {
        game_end = 1;
      }
      else if (i == 3)
      {
        j = 1;

        init_menu_to_0(&new_game_1, &new_game_2, &option_1, &option_2, &resume_1, &resume_2, &exit_1, &exit_2);
        display_image(option_bg, screen);

        if (screenmode == 1)
        {
          screen = SDL_SetVideoMode(800, 600, 32, SDL_HWSURFACE | SDL_DOUBLEBUF | SDL_RESIZABLE);
          display_image(option_bg, screen);

          display_image(windowed, screen);

          SDL_Flip(screen);
        }
        else if (screenmode == 2)
        {
          screen = SDL_SetVideoMode(800, 600, 32, SDL_HWSURFACE | SDL_DOUBLEBUF | SDL_RESIZABLE | SDL_FULLSCREEN);
          display_image(option_bg, screen);

          display_image(fullscreen, screen);
          SDL_Flip(screen);
        }
        if (soundvolume == 0)
        {
          display_image(volume_0, screen);
          SDL_Flip(screen);
        }
        else if (soundvolume == 1)
        {
          display_image(volume_25, screen);
          SDL_Flip(screen);
        }
        else if (soundvolume == 2)
        {
          display_image(volume_50, screen);
          SDL_Flip(screen);
        }
        else if (soundvolume == 3)
        {
          display_image(volume_75, screen);
          SDL_Flip(screen);
        }
        else if (soundvolume == 4)
        {
          display_image(volume_100, screen);
          SDL_Flip(screen);
        }
        SDL_Flip(screen);
      }

      break;
    case SDL_KEYDOWN:

      switch (event.key.keysym.sym)
      {
      case SDLK_l:
        if (j == 0)
          j = 4;
      case SDLK_RETURN:
        if (i == 1)
        {
          j = 2;
          init_perso(&perso);
          afficheBack2(ba, screen);

          if (screenmode == 1)
            screen = SDL_SetVideoMode(1200, 600, 32, SDL_HWSURFACE | SDL_DOUBLEBUF | SDL_RESIZABLE);
          else
            screen = SDL_SetVideoMode(1200, 600, 32, SDL_HWSURFACE | SDL_DOUBLEBUF | SDL_RESIZABLE | SDL_FULLSCREEN);
          init_menu_to_0(&new_game_1, &new_game_2, &option_1, &option_2, &resume_1, &resume_2, &exit_1, &exit_2);
          son_bref("music/running.wav", son);
          SDL_Flip(screen);
        }
        else if (i == 4)
        {
          game_end = 1;
        }
        else if (i == 3)
        {
          j = 1;

          init_menu_to_0(&new_game_1, &new_game_2, &option_1, &option_2, &resume_1, &resume_2, &exit_1, &exit_2);
          display_image(option_bg, screen);

          if (screenmode == 1)
          {
            screen = SDL_SetVideoMode(800, 600, 32, SDL_HWSURFACE | SDL_DOUBLEBUF | SDL_RESIZABLE);
            display_image(option_bg, screen);

            display_image(windowed, screen);

            SDL_Flip(screen);
          }
          else if (screenmode == 2)
          {
            screen = SDL_SetVideoMode(800, 600, 32, SDL_HWSURFACE | SDL_DOUBLEBUF | SDL_RESIZABLE | SDL_FULLSCREEN);
            display_image(option_bg, screen);

            display_image(fullscreen, screen);
            SDL_Flip(screen);
          }
          if (soundvolume == 0)
          {
            display_image(volume_0, screen);
            SDL_Flip(screen);
          }
          else if (soundvolume == 1)
          {
            display_image(volume_25, screen);
            SDL_Flip(screen);
          }
          else if (soundvolume == 2)
          {
            display_image(volume_50, screen);
            SDL_Flip(screen);
          }
          else if (soundvolume == 3)
          {
            display_image(volume_75, screen);
            SDL_Flip(screen);
          }
          else if (soundvolume == 4)
          {
            display_image(volume_100, screen);
            SDL_Flip(screen);
          }
          SDL_Flip(screen);
        }

        break;
      case SDLK_DOWN:
        if (i < 4 && j == 0)
          i++;
        else if (j == 0)
          i = 1;
        if (k < 2 && j == 1)
          k++;
        else if (j == 1)
          k = 1;

        break;
      case SDLK_UP:
        if (i > 1 && j == 0)
          i--;
        else if (j == 0)
          i = 4;
        if (k > 1 && j == 1)
          k--;
        else if (j == 1)
          k = 2;

        break;
      case SDLK_RIGHT:
        if ((j == 1) && (k == 1))
        {
          if ((soundvolume < 4))
          {
            soundvolume++;
          }
          else
          {
            soundvolume = 4;
          }
        }
        if ((j == 1) && (k == 2) && (screenmode < 2) && (soundvolume > 0))
          screenmode++;
        else if ((j == 1) && (k == 2) && (screenmode > 2) && (soundvolume > 0))
          screenmode = 1;

        break;

      case SDLK_LEFT:

        if ((j == 1) && (k == 1) && (soundvolume > 0) && (screenmode > 0))
        {
          soundvolume--;
        }
        else if ((j == 1) && (k == 1) && (soundvolume < 0) && (screenmode > 0))
        {
          soundvolume = 0;
        }
        if ((j == 1) && (k == 2) && (screenmode > 1) && (soundvolume > 0))
        {

          screenmode--;
        }
        else if ((j == 1) && (k == 2) && (soundvolume < 0) && (screenmode > 0))
        {

          screenmode = 2;
        }

        break;
      case SDLK_ESCAPE:
        if (j == 2)
          save(valeur_score);
        if (screenmode == 1)
          screen = SDL_SetVideoMode(800, 600, 32, SDL_HWSURFACE | SDL_DOUBLEBUF | SDL_RESIZABLE);
        else
          screen = SDL_SetVideoMode(800, 600, 32, SDL_HWSURFACE | SDL_DOUBLEBUF | SDL_RESIZABLE | SDL_FULLSCREEN);
        init_everything(&bg, &bg_2, &new_game_1, &new_game_2, &option_1, &option_2, &resume_1, &resume_2, &exit_1, &exit_2, &option_bg, &volume_0, &volume_25, &volume_50, &volume_75, &volume_100, &sound_selected, &screen_selected, &windowed, &fullscreen);
        son_bref("music/running.wav", son);
        display_image(bg, screen);
        display_image(new_game_1, screen);
        display_image(resume_1, screen);
        display_image(option_1, screen);
        display_image(exit_1, screen);
        i = 0;
        j = 0;
        k = 0;

        SDL_Flip(screen);

        break;
      }
      SDL_WaitEvent(&event);
    }
    if (j == 0)
    {
      display_image(bg, screen);
      switch (i)
      {
      case 1:
        son_bref("music/running.wav", son);
        display_image(new_game_2, screen);
        display_image(resume_1, screen);
        display_image(option_1, screen);
        display_image(exit_1, screen);
        SDL_Flip(screen);

        break;
      case 2:

        son_bref("music/running.wav", son);
        display_image(new_game_1, screen);
        display_image(resume_2, screen);
        display_image(exit_1, screen);
        display_image(option_1, screen);
        SDL_Flip(screen);
        break;
      case 3:
        son_bref("music/running.wav", son);
        display_image(new_game_1, screen);
        display_image(resume_1, screen);
        display_image(option_2, screen);
        display_image(exit_1, screen);
        SDL_Flip(screen);
        break;
      case 4:
        son_bref("music/running.wav", son);
        display_image(new_game_1, screen);
        display_image(resume_1, screen);
        display_image(option_1, screen);
        display_image(exit_2, screen);
        SDL_Flip(screen);
        break;
      }
    }
    else if (j == 1)
    {
      switch (k)
      {
      case 1:
        display_image(option_bg, screen);
        if (soundvolume == 0)
        {
          sound_volume(0, music, son);
          display_image(volume_0, screen);
          SDL_Flip(screen);
        }
        else if (soundvolume == 1)
        {
          sound_volume(0.25, music, son);
          display_image(volume_25, screen);
          SDL_Flip(screen);
        }
        else if (soundvolume == 2)
        {
          sound_volume(0.5, music, son);
          display_image(volume_50, screen);
          SDL_Flip(screen);
        }
        else if (soundvolume == 3)
        {
          sound_volume(0.75, music, son);
          display_image(volume_75, screen);
          display_image(volume_75, screen);
          SDL_Flip(screen);
        }
        else if (soundvolume == 4)
        {
          sound_volume(1, music, son);
          display_image(volume_100, screen);
          SDL_Flip(screen);
        }
        display_image(sound_selected, screen);
        if (screenmode == 1)
        {
          display_image(windowed, screen);
          SDL_Flip(screen);
        }
        else if (screenmode == 2)
        {
          display_image(fullscreen, screen);
          SDL_Flip(screen);
        }
        SDL_Flip(screen);
        break;
      case 2:
        display_image(option_bg, screen);

        if (screenmode == 1)
        {
          screen = SDL_SetVideoMode(800, 600, 32, SDL_HWSURFACE | SDL_DOUBLEBUF | SDL_RESIZABLE);
          display_image(option_bg, screen);

          display_image(screen_selected, screen);
          display_image(windowed, screen);
          SDL_Flip(screen);
        }
        else if (screenmode == 2)
        {
          screen = SDL_SetVideoMode(800, 600, 32, SDL_HWSURFACE | SDL_DOUBLEBUF | SDL_RESIZABLE | SDL_FULLSCREEN);

          display_image(option_bg, screen);
          display_image(screen_selected, screen);
          display_image(fullscreen, screen);
          SDL_Flip(screen);
        }
        display_image(screen_selected, screen);

        if (soundvolume == 0)
        {
          display_image(volume_0, screen);
        }
        else if (soundvolume == 1)
        {
          display_image(volume_25, screen);
        }
        else if (soundvolume == 2)
        {
          display_image(volume_50, screen);
        }
        else if (soundvolume == 3)
        {
          display_image(volume_75, screen);
        }
        else if (soundvolume == 4)
        {
          display_image(volume_100, screen);
        }
        SDL_Flip(screen);
        break;
      }
    }
  }
  libere_image(bg);
  libere_image(new_game_1);
  libere_image(new_game_2);
  libere_image(exit_2);
  SDL_Quit();
  return 0;
}