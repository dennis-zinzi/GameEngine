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

#include <vector>
#include "GameObject.h"
#include "Player.h"
#include "DataLoader.h"

using std::vector;

vector<GameObject*> gameObjects;

int main(int argc, char **argv){
	//Create Graphics environment
	GraphicsRenderer renderer;

	//Create Audio environment
	AudioPlayer player;//("notahero.wav");
	player.PlayMusic();
	player.LoadAudio("breakingglass.wav", true);

	FileReader reader;
	//reader.ReadFile("test.txt");
	//reader.ReadRadiusObjects("sample_radius_objects.txt");

	//Create Physics environment
	PhysicsManager physics;
	//Add floor
	//gameObjects.push_back(renderer, new GameObject(physics.GetWorldPlane(), 500.0f, 0.0f, 500.0f, 240, 240, 240, 100));
	RenderObject *plane = new GameObject(renderer, physics.GetWorldPlane(), 500.0f, 0.0f, 500.0f, 240, 240, 240, 100);
	
	//Spheres
	//RenderObject *sp1 = new GameObject(renderer, physics.AddSphere(1.0f, 0.0f, 20.0f, -20.0f, 1.0f));
	//RenderObject *sp1 = new GameObject(renderer, physics, Shape::Sphere, 0.0f, 20.0f, -20.0f, 1.0f, 1.0f);
	////RenderObject *sp2 = new GameObject(renderer, physics.AddSphere(1.0f, 0.5f, 20.5f, -20.0f, 1.0f), 255);
	//RenderObject *sp2 = new GameObject(renderer, physics, Shape::Sphere, 0.5f, 20.5f, -20.0f, 1.0f, 1.0f, 0.0f, 255);

	////Cylinder
	////RenderObject *cyl = new GameObject(renderer, physics.AddCylinder(1.5f, 3.0f, 1.2f, 10.0f, -20.0f, 5.0f), 10, 0, 200, 150);
	//RenderObject *cy1 = new GameObject(renderer, physics, Shape::Cylinder, 1.2f, 10.0f, -19.5f, 5.0f, 1.5f, 3.0f, 10, 0, 200, 150);
	////Cone
	////RenderObject *cone1 = new GameObject(renderer, physics.AddCone(0.5f, 2.0f, 0.5f, 0.0f, -20.0f, 2.0f), 255, 0, 200, 140);
	//RenderObject *cone1 = new GameObject(renderer, physics, Shape::Cone, 0.5f, 0.0f, -21.5f, 2.0f, 0.5f, 2.0f, 10, 0, 200, 150);
	////Box
	////RenderObject *box1 = new GameObject(renderer, physics.AddBox(2.2f, 2.2f, 2.2f, 0.0f, 5.0f, -20.0f, 100.0f), 2.2f, 2.2f, 2.2f, 0, 45, 0);
	//RenderObject *box1 = new GameObject(renderer, physics, Shape::Box, 0.0f, 5.0f, -20.0f, 100.0f, 2.2f, 2.2f, 2.2f, 10, 65, 0);

	/*RenderObject *gamePlayer = new Player(renderer, renderer.GetCamera(), physics.AddBox(1.1f, 1.1f, 1.1f,
		renderer.GetCamera()->GetCameraPos()[0], renderer.GetCamera()->GetCameraPos()[1],
		renderer.GetCamera()->GetCameraPos()[2] - 5.0f, 1.0f), 1.1f, 1.1f, 1.1f, 255, 255, 255); */
	RenderObject *gamePlayer = new Player(renderer, physics, 0.5f);

	//Add game objects	
	//gameObjects.push_back(cone1);
	//gameObjects.push_back(box1);
	//gameObjects.push_back(sp1);
	//gameObjects.push_back(sp2);
	//gameObjects.push_back(cyl);
	//gameObjects.push_back(gamePlayer);

	DataLoader loader(renderer, physics, reader);
	loader.LoadRadWorldObjects();
	loader.LoadFlatWorldObjects();

	bool running = true;

	//Time in msec
	int time = 0;

	while(running){
		time = renderer.GetTime();
		running = renderer.CheckStillRunning();
		physics.UpdatePhysics((float)time);

		//for(auto gameObj : gameObjects){
		//	gameObj->RenderObject();
		//}

		renderer.UpdateScene((float)time);
	}

	return 0;
}