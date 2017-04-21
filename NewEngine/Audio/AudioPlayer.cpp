#include "AudioPlayer.h"


AudioPlayer::AudioPlayer(string background){
	if(Mix_OpenAudio(SOUND_FREQUENCY, MIX_DEFAULT_FORMAT, CHANNELS, SAMPLE_SIZE) < 0){
		printf("Error: %s", Mix_GetError());
	}

	string audioPath = AUDIO_PATH + background;

	//Load background music
	this->background = Mix_LoadMUS(audioPath.c_str());
	if(this->background == nullptr){
		printf("Error: %s", Mix_GetError());
	}
}

AudioPlayer::~AudioPlayer(){
	Mix_HaltMusic();
	Mix_FreeMusic(background);
	background = nullptr;
	Mix_Quit();
}