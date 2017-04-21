//Graphics includes
//#include "../Graphics/GraphicsRenderer.h"
#pragma comment(lib, "Graphics.lib")

//Physics includes
#include "../Physics/PhysicsManager.h"
#pragma comment(lib, "Physics.lib")

//Audio includes
#include "../Audio/AudioPlayer.h"
#pragma comment(lib, "Audio.lib")

#include <vector>
#include "GameObject.h"

using std::vector;

vector<GameObject*> gameObjects;

int main(int argc, char **argv){
	//Create Graphics environment
	GraphicsRenderer renderer;

	//Create Audio environment
	AudioPlayer player;//("notahero.wav");
	player.PlayMusic();

	//Create Physics environment
	PhysicsManager physics;
	//Add floor
	gameObjects.push_back(new GameObject(physics.GetWorldPlane(), 500.0f, 0.0f, 500.0f));
	
	//Spheres
	GameObject *sp1 = new GameObject(physics.AddSphere(1.0f, 0.0f, 20.0f, -20.0f, 1.0f));
	GameObject *sp2 = new GameObject(physics.AddSphere(1.0f, 0.5f, 20.5f, -20.0f, 1.0f), 255);
	//Cylinder
	GameObject *cyl = new GameObject(physics.AddCylinder(1.5f, 3.0f, 1.2f, 10.0f, -20.0f, 5.0f), 10, 0, 200, 150);
	//Cone
	GameObject *cone1 = new GameObject(physics.AddCone(0.5f, 2.0f, 0.5f, 0.0f, -20.0f, 2.0f), 255, 0, 200, 140);
	//Box
	GameObject *box1 = new GameObject(physics.AddBox(2.2f, 2.2f, 2.2f, 0.0f, 5.0f, -20.0f, 100.0f), 2.2f, 2.2f, 2.2f, 0, 45, 0);

	//Add game objects	
	gameObjects.push_back(cone1);
	gameObjects.push_back(box1);
	gameObjects.push_back(sp1);
	gameObjects.push_back(sp2);
	gameObjects.push_back(cyl);



	bool running = true;

	//Time in msec
	int time = 0;

	while(running){
		time = renderer.GetTime();
		running = renderer.CheckStillRunning();
		physics.UpdatePhysics((float)time);

		for(auto gameObj : gameObjects){
			gameObj->RenderObject();
		}

		renderer.UpdateScene((float)time);
	}

	return 0;
}