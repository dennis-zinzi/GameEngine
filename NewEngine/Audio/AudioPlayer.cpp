#include "AudioPlayer.h"


AudioPlayer::AudioPlayer(string background){
	if(Mix_OpenAudio(SOUND_FREQUENCY, MIX_DEFAULT_FORMAT, CHANNELS, SAMPLE_SIZE) < 0){
		printf("Error: %s", Mix_GetError());
	}

	string audioPath = AUDIO_PATH + background;

	//Load background music
	this->background = Mix_LoadMUS(audioPath.c_str());
	if(!this->background){
		printf("Error: %s", Mix_GetError());
		return;
	}
	songs.push_back(this->background);
}

AudioPlayer::~AudioPlayer(){
	Mix_HaltMusic();
	for(auto song : songs){
		Mix_FreeMusic(song);
		song = nullptr;
	}
	for(auto effect : soundEffects){
		Mix_FreeChunk(effect.sound);
		effect.sound = nullptr;
	}
	Mix_Quit();
}

void AudioPlayer::LoadAudio(string filename, bool isSoundEffect){
	string filePath = AUDIO_PATH + filename;
	if(isSoundEffect){
		Mix_Chunk *effect = Mix_LoadWAV(filePath.c_str());
		if(!effect){
			printf("Error: %s", Mix_GetError());
			return;
		}
		Effect sound = {filename, effect};
		soundEffects.push_back(sound);
	}

	Mix_Music *song = Mix_LoadMUS(filePath.c_str());
	if(!song){
		printf("Error: %s", Mix_GetError());
		return;
	}
	songs.push_back(song);
}
