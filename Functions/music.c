#include "music.h"
void son_continue(char *name, Mix_Music *music)
{
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) == -1)

	{
		printf("%s", Mix_GetError());
	}

	music = Mix_LoadMUS(name); // load the music
	Mix_PlayMusic(music, -1);  // play music
}
void son_bref(char *name, Mix_Chunk *son)
{

	son = Mix_LoadWAV(name);
	Mix_PlayChannel(1, son, 1);
	int previous_volume;
	previous_volume = Mix_VolumeChunk(son, MIX_MAX_VOLUME / 4);
}

void free_music(Mix_Music *music)
{
	Mix_FreeMusic(music);
}

void free_chunk(Mix_Chunk *son)
{
	Mix_FreeChunk(son);
	son = NULL;
}
void sound_volume(float volume, Mix_Music *music, Mix_Chunk *son)
{
	// int music_volume;

	Mix_VolumeMusic(MIX_MAX_VOLUME * volume);
}
