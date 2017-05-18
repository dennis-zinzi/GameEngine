#include "GameLoader.h"

GameLoader::GameLoader(GameLevel *game, GraphicsRenderer *renderer, PhysicsManager *physics, FileReader *reader, AudioPlayer *player){
	this->game = game;
	this->renderer = renderer;
	this->physics = physics;
	this->reader = reader;
	this->player = player;
}

void GameLoader::LoadGameFloor(){
	new GameObject(renderer, physics, player, physics->GetWorldPlane(), 500.0f, 0.0f, 500.0f, 240, 240, 240, 100);
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

		new GameObject(renderer, physics, player, shape, type, stof(data[2]), stof(data[3]), stof(data[4]), stof(data[5]), stof(data[6]),
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

		new GameObject(renderer, physics, player, shape, type, stof(data[2]), stof(data[3]), stof(data[4]), stof(data[5]),
			stof(data[6]), stof(data[7]), stof(data[8]),
			stoi(data[9]), stoi(data[10]), stoi(data[11]), stoi(data[12]));
	}
}


void GameLoader::LoadGameSettings(){
	vector<string> gameData = reader->ReadFile("game_settings.txt");

	//Set background music
	player->ChangeMusic(gameData[0]);

	//Set level play time
	game->SetGameTime(stoi(gameData[1]));
}

void GameLoader::LoadGameHUD(){
	vector<vector<string>> HUDData = reader->ReadObjectInfo("hud_objects.txt");

	for(auto hud : HUDData){
		if(hud[0] == "text"){
			Purpose p;
			if(hud[1] == "score"){
				p = Purpose::Score;
			}
			else if(hud[1] == "time"){
				p = Purpose::Time;
			}
			else{ continue; }

			new GameHUDObject(renderer, p, hud[2], stof(hud[3]), stof(hud[4]), stof(hud[5]), stof(hud[6]), stoi(hud[7]), stoi(hud[8]), stoi(hud[9]), stoi(hud[10]));
		}

		//HUD image
		else if(hud[0] == "image"){
			new GameHUDObject(renderer, hud[1], stof(hud[2]), stof(hud[3]), stof(hud[4]), stof(hud[5]));
		}
	}
}
