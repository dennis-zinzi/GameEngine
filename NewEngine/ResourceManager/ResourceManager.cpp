#include "ResourceManager.h"

ResourceManager::ResourceManager(FileReader *reader, AudioPlayer *player, GraphicsRenderer *renderer){
	this->reader = reader;
	this->player = player;
	this->renderer = renderer;
}

//Loads game assets
void ResourceManager::LoadResources(){
	LoadAudioFiles();
	//LoadImages();
	//LoadFonts();
}


//Frees game assets
void ResourceManager::UnloadResources(){
	player->UnloadAudio();
}


void ResourceManager::LoadAudioFiles(){
	//Load all songs in music directory
	vector<string> music = reader->GetDirFiles(MUSIC_PATH, "wav");
	for(auto track : music){
		player->LoadAudio(track, false);
	}

	//Load all sound effects in music directory
	vector<string> sounds = reader->GetDirFiles(EFFECTS_PATH, "wav");
	for(auto effect : sounds){
		player->LoadAudio(effect, true);
	}
}