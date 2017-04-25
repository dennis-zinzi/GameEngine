#pragma once

#include <iostream>
#include <string>
#include <vector>
//#include <SDL_mixer.h>
#include "../SDL2_mixer-2.0.1/include/SDL_mixer.h"

#include "common.h"

#define SOUND_FREQUENCY 44100
#define SAMPLE_SIZE 4096
#define CHANNELS 2

using std::cout;
using std::endl;
using std::string;
using std::vector;

struct Effect{
	std::string name;
	Mix_Chunk *sound;
};

struct Song{
	std::string name;
	Mix_Music *sound;
};

class AudioPlayer{
	public:
		AudioPlayer();
		~AudioPlayer();

		inline static void PauseMusic(){
			Mix_PauseMusic();
		}

		inline void ResumeMusic(){
			Mix_ResumeMusic();
		}

		inline void ChangeMusic(string music){
			Mix_HaltMusic();
			for(auto song : songs){
				if(song.name == music){
					Mix_PlayMusic(song.sound, -1);
					return;
				}
			}
			printf("Error: %s not found", music);
		}

		void LoadAudio(string filename, bool isSoundEffect);

		void UnloadAudio();

		inline void PlayEffect(string filename){
			for(auto effect : soundEffects){
				if(effect.name == filename){
					Mix_PlayChannel(-1, effect.sound, 0);
					return;
				}
			}
			printf("Error: %s not found", filename);
		}

	private:
		vector<Effect> soundEffects;
		vector<Song> songs;
};