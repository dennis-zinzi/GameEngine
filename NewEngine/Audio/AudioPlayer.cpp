#include "AudioPlayer.h"


AudioPlayer::AudioPlayer(){
	if(Mix_OpenAudio(SOUND_FREQUENCY, MIX_DEFAULT_FORMAT, CHANNELS, SAMPLE_SIZE) < 0){
		printf("Error: %s", Mix_GetError());
	}
}

AudioPlayer::~AudioPlayer(){
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

void AudioPlayer::UnloadAudio(){
	//Stop whatever music is playing in the background
	Mix_HaltMusic();

	//Free music resources
	for(auto song : songs){
		Mix_FreeMusic(song.sound);
		song.sound = nullptr;
	}
	//Free sound effects resources
	for(auto effect : soundEffects){
		Mix_FreeChunk(effect.sound);
		effect.sound = nullptr;
	}
}
