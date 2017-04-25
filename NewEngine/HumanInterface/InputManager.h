#include "../SDL2-2.0.5/include/SDL.h"
#include "InputPlayer.h"

#include <iostream>

using std::cout;
using std::endl;

class InputManager{
	public:
		InputManager();
		InputManager(InputPlayer *Player);
		inline void SetInputPlayer(InputPlayer *Player){
			this->Player = Player;
		}

		bool CheckForInputs();

	private:
		InputPlayer *Player;
};