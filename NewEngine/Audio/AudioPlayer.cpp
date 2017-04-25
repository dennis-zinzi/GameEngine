#include "AudioPlayer.h"


AudioPlayer::AudioPlayer(){
	if(Mix_OpenAudio(SOUND_FREQUENCY, MIX_DEFAULT_FORMAT, CHANNELS, SAMPLE_SIZE) < 0){
		printf("Error: %s", Mix_GetError());
	}
}

AudioPlayer::~AudioPlayer(){
	Mix_HaltMusic();
	for(auto song : songs){
		Mix_FreeMusic(song.sound);
		song.sound = nullptr;
	}
	for(auto effect : soundEffects){
		Mix_FreeChunk(effect.sound);
		effect.sound = nullptr;
	}
	Mix_Quit();
}

void AudioPlayer::LoadAudio(string filename, bool isSoundEffect){
	if(isSoundEffect){
		string filePath = EFFECTS_PATH + filename;
		Mix_Chunk *effect = Mix_LoadWAV(filePath.c_str());
		if(!effect){
			printf("Error: %s", Mix_GetError());
			return;
		}
		Effect sound = {filename, effect};
		soundEffects.push_back(sound);
		return;
	}

	string filePath = MUSIC_PATH + filename;
	Mix_Music *song = Mix_LoadMUS(filePath.c_str());
	if(!song){
		printf("Error: %s", Mix_GetError());
		return;
	}
	Song track = {filename, song};
	songs.push_back(track);
}
