/**
 * Class that responds to game input by performing the relevant actions 
 * @author: Dennis Zinzi (130301136)
 */

#include "../SDL2-2.0.5/include/SDL.h"
#include "InputPlayer.h"

#include <iostream>

using std::cout;
using std::endl;

class InputManager{
	public:
		InputManager();
		InputManager(InputPlayer *Player);

		//Set the player performing input actions
		inline void SetInputPlayer(InputPlayer *Player){
			this->Player = Player;
		}

		//Check for inputs and initiate apropriate action
		bool CheckForInputs();

	private:
		InputPlayer *Player;
};