#include "InputManager.h"
#include "InputManager.h"

InputManager::InputManager(){

}


InputManager::InputManager(InputPlayer *Player){
	this->Player = Player;
	isPaused = false;
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

					default:
						break;
				}
				break;
			}
			case SDL_KEYUP:{
				switch(event.key.keysym.sym){
					case SDLK_SPACE:
						if(!isPaused){
							Player->Jump();
						}
						break;
					case SDLK_p:
						isPaused = !isPaused;
						Player->ShowControls(isPaused);
						break;
					default:
						break;
				}
				break;
			}
			case SDL_MOUSEBUTTONDOWN: {
				switch(event.button.button){
					//Left click
					case SDL_BUTTON_LEFT: {
						if(!isPaused){
							Player->Shoot();
						}
						break;
					}
					default:
						break;
				}
			}
		}
	}

	//Gather player input if game unpaused
	if(!isPaused){
		const Uint8 *keyboard_state = SDL_GetKeyboardState(NULL);
		bool moving = false;
		// Move player
		if((keyboard_state[SDL_SCANCODE_W] && !keyboard_state[SDL_SCANCODE_S])
			|| (keyboard_state[SDL_SCANCODE_UP] && !keyboard_state[SDL_SCANCODE_DOWN])) {
			//Apply force upwards
			Player->MoveForward();
			moving = true;
		}
		else if((keyboard_state[SDL_SCANCODE_S] && !keyboard_state[SDL_SCANCODE_W])
			|| (keyboard_state[SDL_SCANCODE_DOWN] && !keyboard_state[SDL_SCANCODE_UP])) {
			//Apply force downwards
			Player->MoveBackward();
			moving = true;
		}

		if((keyboard_state[SDL_SCANCODE_D] && !keyboard_state[SDL_SCANCODE_A])
			|| (keyboard_state[SDL_SCANCODE_RIGHT] && !keyboard_state[SDL_SCANCODE_LEFT])) {
			//Apply force rightwards
			Player->MoveRight();
			moving = true;
		}
		else if((keyboard_state[SDL_SCANCODE_A] && !keyboard_state[SDL_SCANCODE_D])
			|| (keyboard_state[SDL_SCANCODE_LEFT] && !keyboard_state[SDL_SCANCODE_RIGHT])) {
			//Apply force leftwards
			Player->MoveLeft();
			moving = true;
		}

		if(!moving){
			Player->NoMovement();
		}
	}

	return true;
}

Action InputManager::CheckForRestart(){
	SDL_Event event;

	//Runs whilst there is an event being queued
	while(SDL_PollEvent(&event)){
		switch(event.type){
			case SDL_QUIT:
				return Action::Close;
			case SDL_KEYDOWN: {
				switch(event.key.keysym.sym){
					case SDLK_ESCAPE:
						return Action::Close;

					case SDLK_r:
						return Action::Restart;
				}
			}
		}
	}

	return Action::Nothing;
}
