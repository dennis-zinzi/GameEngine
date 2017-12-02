#include "GameLoader.h"

GameLoader::GameLoader(GameLevel *game, GraphicsRenderer *renderer, PhysicsManager *physics, FileReader *reader, AudioPlayer *player){
	this->game = game;
	this->renderer = renderer;
	this->physics = physics;
	this->reader = reader;
	this->player = player;
}

void GameLoader::LoadGame(){
	//Clear any existing objects
	physics->ClearPhysicsObjects();
	renderer->ClearRenderObjects();

	//LoadGameFloor();
	LoadGameSettings();
	LoadRadWorldObjects();
	LoadFlatWorldObjects();

	renderer->ClearHUDObjects();
	LoadGameHUD();
}


void GameLoader::LoadGameFloor(string tex){
	//new GameObject(renderer, physics, player, physics->AddPlane(0.0f, -2.0f, -10.0f, 0.0f), 500.0f, 0.0f, 500.0f, 240, 240, 240, 100);
	new GameObject(renderer, physics, player, Shape::Plane, Type::Floor, 0.0f, -2.4f, -100.0f, 0.0f,
		500.0f, 0.0f, 500.0f,
		240, 240, 240, 150, tex);
}


void GameLoader::LoadRadWorldObjects(){
	vector<vector<string>> allData = reader->ReadObjectInfo("radius_objects.txt");
	for(auto data : allData){
		Shape shape;

		if(data[CircularObjectData::SHAPE] == "Sphere"){
			shape = Shape::Sphere;
		}
		else if(data[CircularObjectData::SHAPE] == "Cylinder"){
			shape = Shape::Cylinder;
		}
		else if(data[CircularObjectData::SHAPE] == "Cone"){
			shape = Shape::Cone;
		}
		
		Type type;

		if(data[CircularObjectData::TYPE] == "Target"){
			type = Type::Target;
		}
		else if(data[CircularObjectData::TYPE] == "NonTarget"){
			type = Type::NonTarget;
		}
		else if(data[CircularObjectData::TYPE] == "Bullet"){
			type = Type::Bullet;
		}
		else if(data[CircularObjectData::TYPE] == "Player"){
			type = Type::PLAYER;
		}
		else if(data[CircularObjectData::TYPE] == "Floor"){
			type = Type::Floor;
		}
		else if(data[CircularObjectData::TYPE] == "Other"){
			type = Type::Other;
		}

		new GameObject(renderer, physics, player, shape, type, 
			stof(data[CircularObjectData::POS_X]), stof(data[CircularObjectData::POS_Y]), stof(data[CircularObjectData::POS_Z]),
			stof(data[CircularObjectData::MASS]), stof(data[CircularObjectData::RADIUS]), stof(data[CircularObjectData::HEIGHT]), 
			stoi(data[CircularObjectData::RED]), stoi(data[CircularObjectData::GREEN]), stoi(data[CircularObjectData::BLUE]), stoi(data[CircularObjectData::ALPHA]),
			(data.size() > CircularObjectData::TEXTURE ? data[CircularObjectData::TEXTURE] : "none"));
	}
}

void GameLoader::LoadFlatWorldObjects(){
	vector<vector<string>> allData = reader->ReadObjectInfo("flat_objects.txt");
	for(auto data : allData){
		Shape shape;

		if(data[FlatObjectData::SHAPE] == "Plane"){
			shape = Shape::Plane;
		}
		else if(data[FlatObjectData::SHAPE] == "Box"){
			shape = Shape::Box;
		}

		Type type;

		if(data[FlatObjectData::TYPE] == "Target"){
			type = Type::Target;
		}
		else if(data[FlatObjectData::TYPE] == "NonTarget"){
			type = Type::NonTarget;
		}
		else if(data[FlatObjectData::TYPE] == "Bullet"){
			type = Type::Bullet;
		}
		else if(data[FlatObjectData::TYPE] == "Player"){
			type = Type::PLAYER;
		}
		else if(data[FlatObjectData::TYPE] == "Floor"){
			type = Type::Floor;
		}
		else if(data[FlatObjectData::TYPE] == "Other"){
			type = Type::Other;
		}

		new GameObject(renderer, physics, player, shape, type, 
			stof(data[FlatObjectData::POS_X]), stof(data[FlatObjectData::POS_Y]), stof(data[FlatObjectData::POS_Z]), 
			stof(data[FlatObjectData::MASS]), stof(data[FlatObjectData::WIDTH]), stof(data[FlatObjectData::HEIGHT]), stof(data[FlatObjectData::DEPTH]),
			stoi(data[FlatObjectData::RED]), stoi(data[FlatObjectData::GREEN]), stoi(data[FlatObjectData::BLUE]), stoi(data[FlatObjectData::ALPHA]),
			data[FlatObjectData::TEXTURE]);
	}
}


void GameLoader::LoadGameSettings(){
	vector<string> gameData = reader->ReadFile("game_settings.txt");

	//Set background music
	player->ChangeMusic(gameData[SettingsData::BACKGROUND_MUSIC]);

	//Set level play time
	game->SetGameTime(stoi(gameData[SettingsData::GAME_TIME]));

	//Set points earned for target types
	int points[4] = {stoi(gameData[SettingsData::POSITIVE_POINTS]), stoi(gameData[SettingsData::NEGATIVE_POINTS]), 
		stoi(gameData[SettingsData::DISABLED_POSITIVE_POINTS]), stoi(gameData[SettingsData::DISABLED_NEGATIVE_POINTS])};

	game->SetPointsValues(points);

	//Set level floor
	LoadGameFloor(gameData[SettingsData::FLOOR_TEX]);

	//Set bullet texture name
	GameLevel::SetBulletTex(gameData[SettingsData::BULLET_TEX]);
}

void GameLoader::LoadGameHUD(){
	vector<vector<string>> HUDData = reader->ReadObjectInfo("hud_objects.txt");

	for(auto hud : HUDData){
		if(hud[HUDObjectType] == "text"){
			Purpose p;
			if(hud[HUDTextObjectData::PURPOSE] == "score"){
				p = Purpose::Score;
			}
			else if(hud[HUDTextObjectData::PURPOSE] == "time"){
				p = Purpose::Time;
			}
			else if(hud[HUDTextObjectData::PURPOSE] == "highscore"){
				p = Purpose::HighScore;
			}
			else{ continue; }
			
			new GameHUDObject(renderer, p, hud[HUDTextObjectData::FONT], stoi(hud[HUDTextObjectData::FONTSIZE]),
				stof(hud[HUDTextObjectData::POS_X]), stof(hud[HUDTextObjectData::POS_Y]),
				stof(hud[HUDTextObjectData::WIDTH]), stof(hud[HUDTextObjectData::HEIGHT]),
				stoi(hud[HUDTextObjectData::RED]), stoi(hud[HUDTextObjectData::GREEN]), stoi(hud[HUDTextObjectData::BLUE]), 
				stoi(hud[HUDTextObjectData::ALPHA]));
		}

		//HUD image
		else if(hud[HUDObjectType] == "image"){
			new GameHUDObject(renderer, hud[HUDImgObjectData::IMG], 
				stof(hud[HUDImgObjectData::POS_X]), stof(hud[HUDImgObjectData::POS_Y]), 
				stof(hud[HUDImgObjectData::WIDTH]), stof(hud[HUDImgObjectData::HEIGHT]));
		}
	}
}
