//Graphics includes
//#include "../Graphics/GraphicsRenderer.h"
#pragma comment(lib, "Graphics.lib")

//Physics includes
#include "../Physics/PhysicsManager.h"
#pragma comment(lib, "Physics.lib")

#include <vector>
#include "GameObject.h"

using std::vector;

vector<GameObject*> gameObjects;

int main(int argc, char **argv){
	//Create Graphics environment
	GraphicsRenderer renderer;

	//Create Physics environment
	PhysicsManager physics;
	GameObject *go = new GameObject(physics.AddSphereObj(1.0f, 0.0f, 20.0f, -10.0f, 1.0f));
	GameObject *go1 = new GameObject(physics.AddSphereObj(1.0f, 0.5f, 20.5f, -10.0f, 1.0f), 255);
	GameObject *go2 = new GameObject(physics.AddSphereObj(1.0f, 0.5f, 20.5f, -10.0f, 1.0f), 255);
	//GameObject *go1 = new GameObject(physics.AddPlane(10.0f, -30.0f, -20.0f, 10.0f));
	gameObjects.push_back(new GameObject(physics.GetWorldPlane()));
	gameObjects.push_back(go);
	gameObjects.push_back(go1);


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