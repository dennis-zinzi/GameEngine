#include "InputManager.h"

InputManager::InputManager(){

}


InputManager::InputManager(InputPlayer *Player){
	this->Player = Player;
}


bool InputManager::CheckForInputs(){
	SDL_Event event;

	//Runs whilst there is an event being queued
	while(SDL_PollEvent(&event)){
		switch(event.type){
			case SDL_QUIT:
				return false;
			case SDL_KEYDOWN: {
				switch(event.key.keysym.sym){
					case SDLK_ESCAPE:
						return false;

					//case SDLK_w:
					//	Player->MoveForward();
					//	break;
					//case SDLK_s:
					//	Player->MoveBackward();
					//	break;
					//case SDLK_a:
					//	Player->MoveLeft();
					//	break;
					//case SDLK_d:
					//	Player->MoveRight();
					//	break;
					case SDLK_p:
						Player->ShowControls();
						break;
					default:
						break;
				}
				break;
			}
			case SDL_KEYUP:{
				switch(event.key.keysym.sym){
					case SDLK_SPACE:
						Player->Jump();
						break;
					default:
						break;
				}
				break;
			}
			case SDL_MOUSEBUTTONDOWN: {
				Player->Shoot();
				break;
			}
		}
	}

	const Uint8 *keyboard_state = SDL_GetKeyboardState(NULL);

	//bool directions[4];
	//for (int i = 0; i < 4; i++) {
	//	directions[i] = false;
	//}

	// Move player
	if ((keyboard_state[SDL_SCANCODE_W] && !keyboard_state[SDL_SCANCODE_S])
		|| (keyboard_state[SDL_SCANCODE_UP] && !keyboard_state[SDL_SCANCODE_DOWN])) {
		//Apply force upwards
		Player->MoveForward();
	}
	else if ((keyboard_state[SDL_SCANCODE_S] && !keyboard_state[SDL_SCANCODE_W])
		|| (keyboard_state[SDL_SCANCODE_DOWN] && !keyboard_state[SDL_SCANCODE_UP])) {
		//Apply force downwards
		Player->MoveBackward();
	}

	if ((keyboard_state[SDL_SCANCODE_D] && !keyboard_state[SDL_SCANCODE_A])
		|| (keyboard_state[SDL_SCANCODE_RIGHT] && !keyboard_state[SDL_SCANCODE_LEFT])) {
		//Apply force rightwards
		Player->MoveRight();
	}
	else if ((keyboard_state[SDL_SCANCODE_A] && !keyboard_state[SDL_SCANCODE_D])
		|| (keyboard_state[SDL_SCANCODE_LEFT] && !keyboard_state[SDL_SCANCODE_RIGHT])) {
		//Apply force leftwards
		Player->MoveLeft();
	}


	//Player->NoMovement();

	return true;
}