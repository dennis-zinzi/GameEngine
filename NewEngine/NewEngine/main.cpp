//Graphics includes
#include "../Graphics/GraphicsRenderer.h"
#include "../Graphics/RenderObject.h"
#pragma comment(lib, "Graphics.lib")

//Physics includes
#include "../Physics/PhysicsManager.h"
#pragma comment(lib, "Physics.lib")

//Audio includes
#include "../Audio/AudioPlayer.h"
#pragma comment(lib, "Audio.lib")

//FileIO
#include "../FileIO/FileReader.h"
#pragma comment(lib, "FileIO.lib")

//Input
#include "../HumanInterface/InputManager.h"
#pragma comment(lib, "HumanInterface.lib")

#include "GameObject.h"
#include "Player.h"
#include "DataLoader.h"


int main(int argc, char **argv){
	//Create Graphics environment
	GraphicsRenderer renderer;
	
	//Create Physics environment
	PhysicsManager physics;

	//Create Audio environment
	AudioPlayer player;

	//Get File reader/parser
	FileReader reader;
	
	//InputPlayer *gamePlayer = new Player(renderer, physics, player, 0.5f);
	//InputPlayer *gamePlayer = new Player(renderer, physics, player, 1.0f, 1.0f, 1.0f, 5.0f, 68, 195, 18, 125);

	DataLoader loader(renderer, physics, reader, player);
	//Add floor
	loader.LoadGameFloor();
	loader.LoadRadWorldObjects();
	loader.LoadFlatWorldObjects();
	loader.LoadMusicAndSounds();
	loader.LoadGameSettings();

	InputManager input(new Player(renderer, physics, player, 1.0f, 1.0f, 1.0f, 5.0f, 68, 195, 18, 125));

	SDL_Delay(1500);


	bool running = true;
	//Time in msec
	int time = 0;

	while(running){
		time = renderer.GetTime();
		physics.UpdatePhysics((float)time);
		renderer.UpdateScene((float)time);
		running = input.CheckForInputs();
	}

	return 0;
}