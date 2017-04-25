#include "StartupShutdown.h"

StartupShutdown::StartupShutdown(){

}

bool StartupShutdown::Start(){
	renderer = new GraphicsRenderer();
	physics = new PhysicsManager();
	reader = new FileReader();
	player = new AudioPlayer();
	input = new InputManager();

	bool correct = true;

	if(!renderer){
		cout << "ERROR: failed to initialized Renderer" << endl;
		correct = false;
	}
	if(!physics){
		cout << "ERROR: failed to initialized Physics" << endl;
		correct = false;
	}
	if(!reader){
		cout << "ERROR: failed to initialized File Reader" << endl;
		correct = false;
	}
	if(!player){
		cout << "ERROR: failed to initialized Audio" << endl;
		correct = false;
	}
	if(!input){
		cout << "ERROR: failed to initialized Input Manager" << endl;
		correct = false;
	}

	if(correct){
		cout << "All Subsystems loaded successfully!" << endl;
	}

	return correct;
}

bool StartupShutdown::Shutdown(){
	delete reader;
	delete player;
	delete input;
	delete physics;
	delete renderer;

	return true;
}
