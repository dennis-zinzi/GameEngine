#include "GameHUDObject.h"

GameHUDObject::GameHUDObject(GraphicsRenderer *renderer, Purpose purpose, string fontname, float x, float y, float width, float height, int red, int green, int blue, int fontsize){
	this->purpose = purpose;
	this->fontname = fontname;
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
	this->red = red;
	this->green = green;
	this->blue = blue;
	this->fontsize = fontsize;

	renderer->AddHUDObject(this);
}

GameHUDObject::GameHUDObject(GraphicsRenderer *renderer, string imagename, float x, float y, float width, float height){
	purpose = Purpose::Image;
	
	this->imagename = imagename;
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;

	renderer->AddHUDObject(this);
}

void GameHUDObject::Render(){
	switch(purpose){
		case Score:
		{
			string score = "Score: " + to_string(GameLevel::GetScore());
			GraphicsRenderer::LoadSDLText(score, fontname, fontsize, x, y, width, height, red, green, blue);

			break;
		}

		case Time:
		{
			stringstream minsstream;
			minsstream << setw(2) << setfill('0') << to_string(GameLevel::GetTimeLeft() / 60);
			string mins = minsstream.str();

			stringstream secsstream;
			secsstream << setw(2) << setfill('0') << to_string(GameLevel::GetTimeLeft() % 60);
			string secs = secsstream.str();

			string time = mins + ":" + secs;
			GraphicsRenderer::LoadSDLText(time, fontname, fontsize, x, y, width, height, red, green, blue);

			break;
		}

		case Image:
		{
			GraphicsRenderer::RenderHUDImage(x, y, width, height, imagename);
			break;
		}

		default:
			break;
	}
}
