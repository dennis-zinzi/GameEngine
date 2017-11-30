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


/* Set up corresponding data indicies to correspond to text files (easier to deal with) */
enum SettingsData{
	BACKGROUND_MUSIC,
	GAME_TIME,
	POSITIVE_POINTS,
	NEGATIVE_POINTS,
	DISABLED_POSITIVE_POINTS,
	DISABLED_NEGATIVE_POINTS,
	FLOOR_TEX,
	BULLET_TEX
};

namespace FlatObjectData{
	enum FlatObjectData{
		SHAPE,
		TYPE,
		POS_X,
		POS_Y,
		POS_Z,
		MASS,
		WIDTH,
		HEIGHT,
		DEPTH,
		RED,
		GREEN,
		BLUE,
		ALPHA,
		TEXTURE
	};
}

namespace CircularObjectData{
	enum CircularObjectData{
		SHAPE,
		TYPE,
		POS_X,
		POS_Y,
		POS_Z,
		MASS,
		RADIUS,
		HEIGHT,
		RED,
		GREEN,
		BLUE,
		ALPHA,
		TEXTURE
	};
}

#define HUDObjectType 0

namespace HUDTextObjectData{
	enum HUDTextObjectData{
		PURPOSE = 1,
		FONT,
		FONTSIZE,
		POS_X,
		POS_Y,
		WIDTH,
		HEIGHT,
		RED,
		GREEN,
		BLUE,
		ALPHA
	};
}

namespace HUDImgObjectData{
	enum HUDImgObjectData{
		IMG = 1,
		POS_X,
		POS_Y,
		WIDTH,
		HEIGHT
	};
}


class GameLoader{
	public:
		GameLoader(GameLevel *game, GraphicsRenderer *renderer, PhysicsManager *physics, FileReader *reader, AudioPlayer *player);
		void LoadGame();

	private:
		GraphicsRenderer *renderer;
		PhysicsManager *physics;
		FileReader *reader;
		AudioPlayer *player;
		GameLevel *game;

		void LoadGameFloor(string tex = "none");
		void LoadRadWorldObjects();
		void LoadFlatWorldObjects();
		void LoadGameSettings();
		void LoadGameHUD();
};