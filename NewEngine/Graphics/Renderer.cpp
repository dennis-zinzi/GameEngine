#include "Renderer.h"
//#include <SDL.h>

#define FRAME_RATE 60

Renderer::Renderer(){
	SDL_Init(SDL_INIT_EVERYTHING);
	screen = SDL_CreateWindow("SDL Engine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1200, 720, SDL_WINDOW_OPENGL);
	renderer = SDL_CreateRenderer(screen, -1, 0);
}

Renderer::~Renderer(){
	SDL_Quit();
}


int Renderer::GetTime() const{
	return SDL_GetTicks();
}


bool Renderer::CheckStillRunning(){
	SDL_Event event;
	if(SDL_PollEvent(&event)){
		switch(event.type){
			case SDL_QUIT:
				return false;
			case SDL_KEYDOWN:
				switch(event.key.keysym.sym){
					case SDLK_ESCAPE:
						return false;
					default:
						return true;
				}
		}
	}
	return true;
}

void Renderer::UpdateScene(float msec){
	SDL_SetRenderDrawColor(renderer, 79, 79, 79, 255);
	SDL_RenderClear(renderer);

	//Additional stuff render here
	DrawText();
	/*Draw2DRect(10, 10, 100, 200, 100, 205, 222, 200);*/
	//End
	
	SDL_RenderPresent(renderer);


	if(1000 / FRAME_RATE > SDL_GetTicks() - msec){
		SDL_Delay((Uint32)((1000 / FRAME_RATE) - (SDL_GetTicks() - msec)));
	}
}


void Renderer::Draw2DRect(int x, int y, int height, int width,
	int red, int green, int blue, int alpha){

	SDL_Rect rect;
	rect.x = x;
	rect.y = y;
	rect.h = height;
	rect.w = width;

	SDL_SetRenderDrawColor(renderer, red, green, blue, alpha);
	SDL_RenderFillRect(renderer, &rect);
}


void Renderer::DrawText(){
	TTF_Init();

	TTF_Font *font = TTF_OpenFont("../Assets/Fonts/UnifrakturCook-Bold.ttf", 200);

	SDL_Color textColor = {66, 244, 217};
	SDL_Surface *text = TTF_RenderText_Solid(font, "Welcome to the game engine", textColor);
	SDL_Texture *message = SDL_CreateTextureFromSurface(renderer, text);

	SDL_Rect textRect;
	textRect.x = 200;
	textRect.y = 200;
	textRect.h = 250;
	textRect.w = 720;

	SDL_RenderCopy(renderer, message, nullptr, &textRect);

	//SDL_SetRenderDrawColor(renderer, 66, 244, 217, 255);

	//SDL_BlitSurface(text, nullptr, SDL_GetWindowSurface(screen), nullptr);

	TTF_CloseFont(font);
}