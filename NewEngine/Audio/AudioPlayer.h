/**
 * Representation of game object to work with engine
 * @author: Dennis Zinzi (130301136)
 */

#pragma once

#include <iostream>
#include <string>
#include <vector>

#include "../SDL2_mixer-2.0.1/include/SDL_mixer.h"

#include "common.h"

#define SOUND_FREQUENCY 44100
#define SAMPLE_SIZE 4096
#define CHANNELS 2

using std::cout;
using std::endl;
using std::string;
using std::vector;

//Representation of Sound Effect
struct Effect{
	std::string name;
	Mix_Chunk *sound;
};

//Representation of Music track
struct Song{
	std::string name;
	Mix_Music *sound;
};

class AudioPlayer{
	public:
		AudioPlayer();
		~AudioPlayer();

		//Pauses currently played music
		inline static void PauseMusic(){
			Mix_PauseMusic();
		}

		//Resumes last played music
		inline void ResumeMusic(){
			Mix_ResumeMusic();
		}

		//Changes played music to one specified if found/loaded
		inline void ChangeMusic(string music){
			for(auto song : songs){
				if(song.name == music){
					//If track found, stop current
					Mix_HaltMusic();
					//Play new track
					Mix_PlayMusic(song.sound, -1);
					return;
				}
			}
			printf("Error: %s not found", music);
		}

		//Load Audio resource (effect or music)
		void LoadAudio(string filename, bool isSoundEffect);

		//Unload all audio resources
		void UnloadAudio();


		//Plays specified sound effect if found/loaded
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