#include "DataLoader.h"

DataLoader::DataLoader(GraphicsRenderer *renderer, PhysicsManager *physics, FileReader *reader, AudioPlayer *player){
	this->renderer = renderer;
	this->physics = physics;
	this->reader = reader;
	this->player = player;
}

void DataLoader::LoadGameFloor(){
	new GameObject(*renderer, physics->GetWorldPlane(), 500.0f, 0.0f, 500.0f, 240, 240, 240, 100);
}


void DataLoader::LoadRadWorldObjects(){
	vector<vector<string>> allData = reader->ReadObjectInfo("radius_objects.txt");
	for(auto data : allData){
		Shape shape;

		if(data[0] == "Sphere"){
			shape = Shape::Sphere;
		}
		else if(data[0] == "Cylinder"){
			shape = Shape::Cylinder;
		}
		else if(data[0] == "Cone"){
			shape = Shape::Cone;
		}

		new GameObject(*renderer, *physics, shape, stof(data[1]), stof(data[2]), stof(data[3]), stof(data[4]), stof(data[5]),
			stof(data[6]), stoi(data[7]), stoi(data[8]), stoi(data[9]), stoi(data[10]));
	}
}

void DataLoader::LoadFlatWorldObjects(){
	vector<vector<string>> allData = reader->ReadObjectInfo("flat_objects.txt");
	for(auto data : allData){
		Shape shape;

		if(data[0] == "Plane"){
			shape = Shape::Plane;
		}
		else if(data[0] == "Box"){
			shape = Shape::Box;
		}

		new GameObject(*renderer, *physics, shape, stof(data[1]), stof(data[2]), stof(data[3]), stof(data[4]),
			stof(data[5]), stof(data[6]), stof(data[7]),
			stoi(data[8]), stoi(data[9]), stoi(data[10]), stoi(data[11]));
	}
}

void DataLoader::LoadMusicAndSounds(){
	vector<string> music = reader->GetDirFiles(MUSIC_PATH, "wav");

	for(auto track : music){
		player->LoadAudio(track, false);
	}

	vector<string> sounds = reader->GetDirFiles(EFFECTS_PATH, "wav");
	for(auto effect : sounds){
		player->LoadAudio(effect, true);
	}
}

void DataLoader::LoadGameSettings(){
	vector<string> gameData = reader->ReadFile("game_settings.txt");

	//Set background music
	player->ChangeMusic(gameData[0]);
}
