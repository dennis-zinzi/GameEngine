/**
 * Class that responds to game input by performing the relevant actions 
 * @author: Dennis Zinzi (130301136)
 */
#pragma once

#include "../SDL2-2.0.5/include/SDL.h"
#include "InputPlayer.h"

#include <iostream>

using std::cout;
using std::endl;

enum Action{
	Restart,
	Close,
	Nothing
};

class InputManager{
	public:
		InputManager();
		InputManager(InputPlayer *Player);

		//Set the player performing input actions
		inline void SetInputPlayer(InputPlayer *Player){
			this->Player = Player;
		}
		inline InputPlayer* GetInputPlayer(){
			return Player;
		}

		//Check for inputs and initiate apropriate action
		bool CheckForInputs();

		//Check for restart key pressed
		Action CheckForRestart();

	private:
		InputPlayer *Player;
		bool isPaused;
};