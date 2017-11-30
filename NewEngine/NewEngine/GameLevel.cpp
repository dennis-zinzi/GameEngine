#include "GameLevel.h"

int GameLevel::score = 0;
int GameLevel::timeLeft = 0;
int GameLevel::pauseTime = 0;
int GameLevel::startPause = 0;
int GameLevel::endPause = 0;
vector<int> GameLevel::points = {};
vector<int> GameLevel::scores = {};
GameState GameLevel::state = GameState::Running;
string GameLevel::bulletTex = "none";

GameLevel::GameLevel(GraphicsRenderer *renderer, AudioPlayer *audioPlayer){
	this->renderer = renderer;
	this->audioPlayer = audioPlayer;
}

void GameLevel::StartGame(){
	startTime = SDL_GetTicks() / 1000;
	state = GameState::Running;
}

void GameLevel::UpdateGame(int time){
	if(state == GameState::Paused){
		renderer->ShowControlsScreen();
		return;
	}
	if(startPause > 0 && endPause > 0){
		UpdatePauseTime();
		startPause = 0;
		endPause = 0;
	}

	timeLeft = gameTime - ((SDL_GetTicks() / 1000) - startTime) + pauseTime;

	if(timeLeft < 0){
		state = GameState::Done;
		scores.push_back(score);

		if(scores.size() > 1){
			int maxScore = *max_element(scores.begin(), scores.end());
			if(score == maxScore){
				//play highscore music
				audioPlayer->PlayEffect("highscore.wav");
				//player->ChangeMusic("khtheme.wav");
			}
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