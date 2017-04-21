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

class AudioPlayer{
	public:
		AudioPlayer(string backgroundFile = "uncharted.wav");
		~AudioPlayer();

		inline static void PauseMusic(){
			Mix_PauseMusic();
		}

		inline void ResumeMusic(){
			Mix_ResumeMusic();
		}

		inline void PlayMusic(){
			Mix_PlayMusic(background, -1);
		}

		inline void ChangeMusic(string music){
			Mix_HaltMusic();
			string audioPath = AUDIO_PATH + music;

			background = Mix_LoadMUS(audioPath.c_str());
			Mix_PlayMusic(background, -1);
		}

		void LoadAudio(string filename, bool isSoundEffect);

		void PlayEffect(string filename){
			for(auto effect : soundEffects){
				if(effect.name == filename){
					Mix_PlayChannel(-1, effect.sound, 0);
					return;
				}
			}
			printf("Error: %s not found", filename);
		}

	private:
		Mix_Music *background;
		vector<Effect> soundEffects;
		vector<Mix_Music*> songs;
};