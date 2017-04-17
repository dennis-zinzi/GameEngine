#include <iostream>
#include "../Graphics/Renderer.h"

#pragma comment(lib, "Graphics.lib")

int main(int argc, char **argv){
	//Create Graphics environment
	Renderer r;

	bool running = true;

	//Time in msec
	int time = 0;

	while(running){
		time = r.GetTime();
		running = r.CheckStillRunning();
		r.UpdateScene((float)time);
	}

	return 0;
}