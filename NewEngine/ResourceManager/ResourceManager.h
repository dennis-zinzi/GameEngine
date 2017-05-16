/**
 * Main class responsible for the loading and unloading of common game resources
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

//FileIO includes
#include "../FileIO/FileReader.h"
#pragma comment(lib, "FileIO.lib")

//Audio includes
#include "../Audio/AudioPlayer.h"
#pragma comment(lib, "Audio.lib")


class ResourceManager{
	public:
		ResourceManager(FileReader *reader, AudioPlayer *player, GraphicsRenderer *renderer);

		//Load all resources to memory
		void LoadResources();
		
		//Unload all resources from memory
		void UnloadResources();

	private:
		//Load every audio file
		void LoadAudioFiles();

		//Load every font file
		void LoadFontFiles();

		//Load every image file
		void LoadImages();
	
		FileReader *reader;
		AudioPlayer *player;
		GraphicsRenderer *renderer;
};