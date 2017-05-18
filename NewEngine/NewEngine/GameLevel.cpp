#include "GameLevel.h"

int GameLevel::score = 0;
int GameLevel::timeLeft = 0;

GameLevel::GameLevel(GraphicsRenderer *renderer){
	this->renderer = renderer;
	startTime = SDL_GetTicks() / 1000;
}

void GameLevel::UpdateGame(int time){
	timeLeft = gameTime - ((SDL_GetTicks() / 1000) - startTime);

	if(timeLeft < 0){
		renderer->ShowControlsScreen();
	}
}
