//Graphics includes
#include "../Graphics/GraphicsRenderer.h"
#include "../Graphics/RenderObject.h"
#pragma comment(lib, "Graphics.lib")

//Physics includes
#include "../Physics/PhysicsManager.h"
#pragma comment(lib, "Physics.lib")

//FileIO
#include "../FileIO/FileReader.h"
#pragma comment(lib, "FileIO.lib")

//Audio includes
#include "../Audio/AudioPlayer.h"
#pragma comment(lib, "Audio.lib")

#include "GameObject.h"
#include "GameHUDObject.h"
#include "GameLevel.h"
#include <vector>

using std::stof;
using std::stoi;
using std::vector;
using std::string;

class GameLoader{
	public:
		GameLoader(GameLevel *game, GraphicsRenderer *renderer, PhysicsManager *physics, FileReader *reader, AudioPlayer *player);
		void LoadGameFloor();
		void LoadRadWorldObjects();
		void LoadFlatWorldObjects();
		void LoadGameSettings();
		void LoadGameHUD();

	private:
		GraphicsRenderer *renderer;
		PhysicsManager *physics;
		FileReader *reader;
		AudioPlayer *player;
		GameLevel *game;
};