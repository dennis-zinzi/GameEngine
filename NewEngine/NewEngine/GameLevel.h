#pragma once

#include "../Graphics/GraphicsRenderer.h"
#include "../Graphics/HUDObject.h"
#pragma comment(lib, "Graphics.lib")

//Audio includes
#include "../Audio/AudioPlayer.h"
#pragma comment(lib, "Audio.lib")

#include <vector>
#include <algorithm>

using std::vector;
using std::max_element;

enum GameState{
	Running,
	Paused,
	Done
};


class GameLevel{
	public:
		GameLevel(GraphicsRenderer *renderer, AudioPlayer *audioPlayer);

		inline static int GetScore(){
			return score;
		}
		inline static void UpdateScore(int points){
			score += points;
		}
		inline void SetScore(int score){
			this->score = score;
		}


		inline static int GetHighscore(){
			return !scores.empty() ? *max_element(scores.begin(), scores.end()) : 0;
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
		inline static void SetGameState(GameState newState){
			state = newState;
		}

		inline static void SetStartPause(int pause){
			startPause = pause;
		}
		inline static void SetEndPause(int pause){
			endPause = pause;
		}

		inline static void UpdatePauseTime(){
			pauseTime += endPause - startPause;
		}


		inline static void SetPointsValues(int pnts[4]){
			points = vector<int>(pnts, pnts + 4);;
		}
		inline static int GetTargetPoints(){
			if(points.size() > 0){
				return points[0];
			}
			return 0;
		}
		inline static int GetNegativeTargetPoints(){
			if(points.size() > 1){
				return points[1];
			}
			return 0;
		}
		inline static int GetDisabledTargetPoints(){
			if(points.size() > 2){
				return points[2];
			}
			return 0;
		}
		inline static int GetDisabledNegativeTargetPoints(){
			if(points.size() > 3){
				return points[3];
			}
			return 0;
		}

		inline static void SetBulletTex(string bulletTexture){
			bulletTex = bulletTexture;
		}
		inline static string GetBulletTex(){
			return bulletTex;
		}

		void StartGame();
		void UpdateGame(int time);
		void RestartLevel();
		void HandleGameFinish();

	private:
		static int score;
		static int pauseTime;
		static int startPause;
		static int endPause;
		static vector<int> points;

		static GameState state;
		static int timeLeft;
		int startTime;
		int gameTime;

		static string bulletTex;

		GraphicsRenderer *renderer;
		AudioPlayer *audioPlayer;

		static vector<int> scores;
};