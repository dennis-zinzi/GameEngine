/**
 * Class that handles the initialization and closing of the game engine
 * @author: Dennis Zinzi (130301136)
 */


#pragma once

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

class StartupShutdown{
	public:
		StartupShutdown();

		//Perform startup tasks
		bool Start();

		//Perform shutdown tasks
		bool Shutdown();

		inline AudioPlayer* GetAudioPlayer(){
			return player;
		}

		inline PhysicsManager* GetPhysicsManager(){
			return physics;
		}

		inline GraphicsRenderer* GetGraphicsRenderer(){
			return renderer;
		}

		inline FileReader* GetFileReader(){
			return reader;
		}

		inline InputManager* GetInputManager(){
			return input;
		}

	private:
		AudioPlayer *player;
		PhysicsManager *physics;
		GraphicsRenderer *renderer;
		FileReader *reader;
		InputManager *input;
};