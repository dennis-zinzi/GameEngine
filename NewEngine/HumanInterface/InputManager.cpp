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

					case SDLK_w:
						Player->MoveForward();
						break;
					case SDLK_s:
						Player->MoveBackward();
						break;
					case SDLK_a:
						Player->MoveLeft();
						break;
					case SDLK_d:
						Player->MoveRight();
						break;
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

	//Player->NoMovement();

	return true;
}