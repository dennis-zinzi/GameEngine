#include "../InitShutdown/StartupShutdown.h"
#pragma comment(lib, "InitShutdown.lib")

#include "GameObject.h"
#include "Player.h"
#include "DataLoader.h"


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

	DataLoader loader(renderer, physics, reader, player);
	//Add floor
	loader.LoadGameFloor();
	loader.LoadRadWorldObjects();
	loader.LoadFlatWorldObjects();
	loader.LoadMusicAndSounds();
	loader.LoadGameSettings();

	InputManager *input = onoff.GetInputManager();
	input->SetInputPlayer(new Player(*renderer, *physics, *player, 1.0f, 1.0f, 1.0f, 5.0f, 68, 195, 18, 125));

	SDL_Delay(2500);


	bool running = true;
	//Time in msec
	int time = 0;

	while(running){
		time = renderer->GetTime();
		physics->UpdatePhysics((float)time);
		renderer->UpdateScene((float)time);
		running = input->CheckForInputs();
	}

	//Destroy subsystems to avoid memory leaks
	if(!onoff.Shutdown()){
		return -1;
	}

	return 0;
}