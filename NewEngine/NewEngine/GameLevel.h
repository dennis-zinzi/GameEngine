#pragma once

#include "../Graphics/GraphicsRenderer.h"
#include "../Graphics/HUDObject.h"
#pragma comment(lib, "Graphics.lib")

#include <vector>

using std::vector;

enum GameState{
	Running,
	Done
};


class GameLevel{
	public:
		GameLevel(GraphicsRenderer *renderer);

		inline static int GetScore(){
			return score;
		}
		inline static void UpdateScore(int points){
			score += points;
		}
		inline void SetScore(int score){
			this->score = score;
		}


		inline static int GetTimeLeft(){
			return timeLeft;
		}
		inline void SetGameTime(int time){
			gameTime = time;
		}


		inline GameState GetState(){
			return state;
		}


		void UpdateGame(int time);
		void RestartLevel();
		void HandleGameFinish();

	private:
		static int score;
		static int timeLeft;
		int startTime;
		int gameTime;
		GameState state;

		GraphicsRenderer *renderer;

		vector<int> scores;
};