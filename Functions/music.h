#ifndef MUSIC_H
#define MUSIC_H
#include <SDL/SDL_mixer.h>
void son_continue(char *name, Mix_Music *music);
void son_bref(char *name, Mix_Chunk *son);
void free_music(Mix_Music *music);
void free_chunk(Mix_Chunk *son);
void sound_volume(float volume, Mix_Music *music, Mix_Chunk *son);
// void sound_volume(float volume,Mix_Music * music,Mix_Chunk *son)
#endif
