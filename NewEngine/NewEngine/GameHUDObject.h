#pragma once

#include "../Graphics/GraphicsRenderer.h"
#include "../Graphics/HUDObject.h"
#pragma comment(lib, "Graphics.lib")

#include "GameLevel.h"

#include <string>
#include <iomanip>
#include <sstream>

using std::string;
using std::to_string;
using std::setw;
using std::setfill;
using std::stringstream;

enum Purpose{
	Score,
	Time,
	HighScore,
	Image
};


class GameHUDObject : public HUDObject{
	public:
		GameHUDObject(GraphicsRenderer *renderer, Purpose purpose, string fontname, int fontsize, float x, float y, float width, float height, int red, int green, int blue, int alpha);
		GameHUDObject(GraphicsRenderer *renderer, string imagename, float x, float y, float width, float height);

		virtual void Render() override;

	protected:
		Purpose purpose;
		string fontname;
		int fontsize;

		string imagename;

		float x, y, 
			width, height;

		int red, green, blue, alpha;

};