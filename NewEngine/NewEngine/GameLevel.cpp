#include "GameLevel.h"

int GameLevel::score = 0;
int GameLevel::timeLeft = 0;
int GameLevel::pauseTime = 0;
int GameLevel::startPause = 0;
int GameLevel::endPause = 0;
vector<int> GameLevel::points = {};
vector<int> GameLevel::scores = {};

GameLevel::GameLevel(GraphicsRenderer *renderer, AudioPlayer *player){
	this->renderer = renderer;
	this->player = player;
}

void GameLevel::StartGame(){
	startTime = SDL_GetTicks() / 1000;
	state = GameState::Running;
}

void GameLevel::UpdateGame(int time){
	if(startPause > 0 && endPause > 0){
		UpdatePauseTime();
		startPause = 0;
		endPause = 0;
	}

	timeLeft = gameTime - ((SDL_GetTicks() / 1000) - startTime) + pauseTime;

	if(timeLeft < 0){
		state = GameState::Done;
		scores.push_back(score);
		int maxScore = *max_element(scores.begin(), scores.end());
		if(score == maxScore){
			//play highscore music
			player->PlayEffect("highscore.wav");
			//player->ChangeMusic("khtheme.wav");
		}

	}
}

void GameLevel::HandleGameFinish(){
	renderer->ShowGameOverScreen(scores);
}

void GameLevel::RestartLevel(){
	score = 0;
	timeLeft = gameTime;
	startTime = SDL_GetTicks() / 1000;
	state = GameState::Running;
	pauseTime = 0;
}