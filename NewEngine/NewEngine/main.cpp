//Graphics includes
#include "../Graphics/Renderer.h"
#pragma comment(lib, "Graphics.lib")

//Physics includes
#include "../Physics/PhysicsManager.h"
#pragma comment(lib, "Physics.lib")

int main(int argc, char **argv){
	//Create Graphics environment
	Renderer renderer;

	//Create Physics environment
	PhysicsManager physics;

	bool running = true;

	//Time in msec
	int time = 0;

	while(running){
		time = renderer.GetTime();
		running = renderer.CheckStillRunning();
		renderer.UpdateScene((float)time);
	}

	return 0;
}