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

#include "GameObject.h"
#include <vector>

using std::stof;
using std::stoi;
using std::vector;
using std::string;

class DataLoader{
	public:
		DataLoader(GraphicsRenderer &renderer, PhysicsManager &physics, FileReader &reader);
		void LoadRadWorldObjects();
		void LoadFlatWorldObjects();

	private:
		GraphicsRenderer *renderer;
		PhysicsManager *physics;
		FileReader *reader;
};