#include "../InitShutdown/StartupShutdown.h"
#pragma comment(lib, "InitShutdown.lib")

#include "../ResourceManager/ResourceManager.h"
#pragma comment(lib, "ResourceManager.lib")

#include "GameObject.h"
#include "Player.h"
#include "GameLoader.h"


int main(int argc, char **argv){
	StartupShutdown onoff;
	
	//Init Engine subsystems
	if(!onoff.Start()){
		//Quit if initialization error
		return -1;
	}

	//Create Graphics environment
	GraphicsRenderer *renderer = onoff.GetGraphicsRenderer();
	
	//Create Physics environment
	PhysicsManager *physics = onoff.GetPhysicsManager();

	//Create Audio environment
	AudioPlayer *player = onoff.GetAudioPlayer();

	//Get File reader/parser
	FileReader *reader = onoff.GetFileReader();

	//Load assets
	ResourceManager resourcer(reader, player, renderer);
	resourcer.LoadResources();

	//Load game specific attributes
	GameLoader loader(renderer, physics, reader, player);
	//Add floor
	loader.LoadGameFloor();
	//Load circular objects
	loader.LoadRadWorldObjects();
	//load rectangular objects
	loader.LoadFlatWorldObjects();
	//load general game settings
	loader.LoadGameSettings();

	//Set up game player & controls
	InputManager *input = onoff.GetInputManager();
	input->SetInputPlayer(new Player(*renderer, *physics, *player, 1.0f, 1.0f, 1.0f, 5.0f, 68, 195, 18, 125));

	//Allow time for everything to be set up correctly, and give player time to learn controls
	SDL_Delay(2500);


	//Status of excecution
	bool running = true;
	//Time in msec
	int time = 0;


	//Excecution loop
	while(running){
		time = renderer->GetTime();
		physics->UpdatePhysics((float)time);
		renderer->UpdateScene((float)time);
		running = input->CheckForInputs();
	}


	//Unload any used resource
	resourcer.UnloadResources();

	//Destroy subsystems to avoid memory leaks
	if(!onoff.Shutdown()){
		return -1;
	}

	return 0;
}