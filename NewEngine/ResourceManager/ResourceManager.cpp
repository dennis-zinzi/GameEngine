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
	LoadImages();
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
	//Get the sizes to load the fonts for
	vector<string> fontsizesString = reader->ReadFile("font_sizes.txt");
	vector<int> intSizes;

	//As reading from files gives back string, convert results to int
	for(auto size : fontsizesString){
		intSizes.push_back(stoi(size));
	}

	//Load all fonts at the needed sizes
	vector<string> fonts = reader->GetDirFiles(FONT_PATH, "ttf");
	for(auto font : fonts){
		for(auto size : intSizes){
			renderer->LoadFont(font, size);
		}
	}
}


void ResourceManager::LoadImages(){
	//Load all pngs in image directory
	vector<string> pngs = reader->GetDirFiles(IMAGE_PATH, "png");
	for(auto png : pngs){
		renderer->LoadTexture(png);
	}


	//Load all jpgs in image directory
	vector<string> jpgs = reader->GetDirFiles(IMAGE_PATH, "jpg");
	for(auto jpg : jpgs){
		renderer->LoadTexture(jpg);
	}
}