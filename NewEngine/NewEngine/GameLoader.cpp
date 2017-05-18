#include "GameLoader.h"

GameLoader::GameLoader(GraphicsRenderer *renderer, PhysicsManager *physics, FileReader *reader, AudioPlayer *player){
	this->renderer = renderer;
	this->physics = physics;
	this->reader = reader;
	this->player = player;
}

void GameLoader::LoadGameFloor(){
	new GameObject(*renderer, *physics, physics->GetWorldPlane(), 500.0f, 0.0f, 500.0f, 240, 240, 240, 100);
}


void GameLoader::LoadRadWorldObjects(){
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
		
		Type type;

		if(data[1] == "Target"){
			type = Type::Target;
		}
		else if(data[1] == "Bullet"){
			type = Type::Bullet;
		}
		else if(data[1] == "Player"){
			type = Type::PLAYER;
		}
		else if(data[1] == "Floor"){
			type = Type::Floor;
		}
		else if(data[1] == "Other"){
			type = Type::Other;
		}

		new GameObject(*renderer, *physics, shape, type, stof(data[2]), stof(data[3]), stof(data[4]), stof(data[5]), stof(data[6]),
			stof(data[7]), stoi(data[8]), stoi(data[9]), stoi(data[10]), stoi(data[11]));
	}
}

void GameLoader::LoadFlatWorldObjects(){
	vector<vector<string>> allData = reader->ReadObjectInfo("flat_objects.txt");
	for(auto data : allData){
		Shape shape;

		if(data[0] == "Plane"){
			shape = Shape::Plane;
		}
		else if(data[0] == "Box"){
			shape = Shape::Box;
		}

		Type type;

		if(data[1] == "Target"){
			type = Type::Target;
		}
		else if(data[1] == "Bullet"){
			type = Type::Bullet;
		}
		else if(data[1] == "Player"){
			type = Type::PLAYER;
		}
		else if(data[1] == "Floor"){
			type = Type::Floor;
		}
		else if(data[1] == "Other"){
			type = Type::Other;
		}

		new GameObject(*renderer, *physics, shape, type, stof(data[2]), stof(data[3]), stof(data[4]), stof(data[5]),
			stof(data[6]), stof(data[7]), stof(data[8]),
			stoi(data[9]), stoi(data[10]), stoi(data[11]), stoi(data[12]));
	}
}


void GameLoader::LoadGameSettings(){
	vector<string> gameData = reader->ReadFile("game_settings.txt");

	//Set background music
	player->ChangeMusic(gameData[0]);
}
