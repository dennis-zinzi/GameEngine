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

	//Create Audio environment
	AudioPlayer player("notahero.wav");
	player.PlayMusic();
	player.LoadAudio("breakingglass.wav", true);

	FileReader reader;

	//Create Physics environment
	PhysicsManager physics;
	//Add floor
	RenderObject *plane = new GameObject(renderer, physics.GetWorldPlane(), 500.0f, 0.0f, 500.0f, 240, 240, 240, 100);

	InputPlayer *gamePlayer = new Player(renderer, physics, 0.5f);
	//InputPlayer *gamePlayer = new Player(renderer, physics, 1.0f, 1.0f, 0.5f, 5.0f);

	DataLoader loader(renderer, physics, reader);
	loader.LoadRadWorldObjects();
	loader.LoadFlatWorldObjects();

	InputManager input(gamePlayer);

	bool running = true;

	//Time in msec
	int time = 0;

	while(running){
		time = renderer.GetTime();
		running = input.CheckForInputs();
		physics.UpdatePhysics((float)time);
		renderer.UpdateScene((float)time);
	}

	return 0;
}