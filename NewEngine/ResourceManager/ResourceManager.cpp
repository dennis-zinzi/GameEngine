#include "ResourceManager.h"

ResourceManager::ResourceManager(FileReader *reader, AudioPlayer *player, GraphicsRenderer *renderer){
	this->reader = reader;
	this->player = player;
	this->renderer = renderer;
}

//Loads game assets
void ResourceManager::LoadResources(){
	LoadAudioFiles();
	LoadFontFiles();
	//LoadImages();
}


//Frees game assets
void ResourceManager::UnloadResources(){
	player->UnloadAudio();
	renderer->UnloadFonts();
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


void ResourceManager::LoadFontFiles(){
	vector<string> fontsizesString = reader->ReadFile("font_sizes.txt");
	vector<int> intSizes;
	for(auto size : fontsizesString){
		intSizes.push_back(stoi(size));
	}

	vector<string> fonts = reader->GetDirFiles(FONT_PATH, "ttf");
	for(auto font : fonts){
		for(auto size : intSizes){
			cout << size << endl;
			renderer->LoadFont(font, size);
		}
	}
}