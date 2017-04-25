#pragma once

//Graphics includes
#include "../Graphics/GraphicsRenderer.h"
#include "../Graphics/RenderObject.h"
#pragma comment(lib, "Graphics.lib")

//Physics includes
#include "../Physics/PhysicsManager.h"
#pragma comment(lib, "Physics.lib")

//FileIO includes
#include "../FileIO/FileReader.h"
#pragma comment(lib, "FileIO.lib")

//Audio includes
#include "../Audio/AudioPlayer.h"
#pragma comment(lib, "Audio.lib")


class ResourceManager{
	public:
		ResourceManager(FileReader *reader, AudioPlayer *player, GraphicsRenderer *renderer);
		void LoadResources();
		void UnloadResources();

	private:
		void LoadAudioFiles();
	
		FileReader *reader;
		AudioPlayer *player;
		GraphicsRenderer *renderer;
};