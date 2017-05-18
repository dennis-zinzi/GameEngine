#include "../InitShutdown/StartupShutdown.h"
#pragma comment(lib, "InitShutdown.lib")

#include "../ResourceManager/ResourceManager.h"
#pragma comment(lib, "ResourceManager.lib")

#include "../Profiler/Profiler.h"
#pragma comment(lib, "Profiler.lib")

#include "GameObject.h"
#include "Player.h"
#include "GameLoader.h"
#include "GameLevel.h"


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


	//Show launch screen
	renderer->ShowLaunchScreen();

	//Create level instance
	GameLevel *game = new GameLevel(renderer);

	//Load game specific attributes
	GameLoader loader(game, renderer, physics, reader, player);
	//Load game data
	loader.LoadGame();

	//Set up game player & controls
	InputManager *input = onoff.GetInputManager();
	input->SetInputPlayer(new Player(renderer, physics, player, 1.0f, 1.0f, 1.0f, 5.0f, 68, 195, 18, 125));

	//Allow time for everything to be set up correctly, and give player time to learn controls
	SDL_Delay(2500);


	//Status of excecution
	bool running = true;
	//Time in msec
	float time = 0;

	Profiler profiler;


	//Excecution loop
	while(running){
		time = renderer->GetTime();

		profiler.ResetTime(time);
		physics->UpdatePhysics(time);
		profiler.UpdateTime(System::Physics, renderer->GetTime());
		renderer->UpdateScene(time);
		profiler.UpdateTime(System::Graphics, renderer->GetTime());
		running = input->CheckForInputs();
		profiler.UpdateTime(System::Input, renderer->GetTime());

		//Update level specific environment
		game->UpdateGame(time);

		//Show loop execution stats
		profiler.ShowStats();


		//Check for game state
		if(game->GetState() == GameState::Done){
			bool restart = false;
			while(!restart){
				game->HandleGameFinish();
				Action perform = input->CheckForRestart();

				restart = perform == Action::Restart;

				if(perform == Action::Close){
					running = false;
					break;
				}
			}

			//As possible to close, check if actually restarting
			if(restart){
				loader.LoadGame();
				game->RestartLevel();
			}
		}
	}


	//Unload any used resource
	resourcer.UnloadResources();

	//Destroy subsystems to avoid memory leaks
	if(!onoff.Shutdown()){
		return -1;
	}

	return 0;
}