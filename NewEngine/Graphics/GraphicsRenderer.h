/**
* Main class responsible for rendering objects on screen
* @author: Dennis Zinzi (130301136)
*/
#pragma once

#include "../SDL2-2.0.5/include/SDL.h"
#include "../SDL2-2.0.5/SDL2_ttf-2.0.14/include/SDL_ttf.h"
#include "../SDL2-2.0.5/SDL2_image-2.0.1/include/SDL_image.h"
#include "../SOIL/SOIL.h"

//OpenGL includes
#include "../glew-2.0.0/include/GL/glew.h"
#include "../freeglut/include/GL/freeglut.h"

#include "common.h"
#include <string>
#include <iostream>
#include <vector>

#include "Camera.h"
#include "RenderObject.h"

using std::string;
using std::vector;
using std::cout;
using std::endl;

//Representation of Text Font
struct Font{
	std::string name;
	int size;
	TTF_Font *font;
};

class GraphicsRenderer{
	public:
		GraphicsRenderer();
		~GraphicsRenderer();

		//Main function in charge of updating all objects on screen
		void UpdateScene(float msec);

		//Draws 2D rectangluar shape using SDL
		void Draw2DRect(int x, int y, int height, int width, int red, int green, int blue, int alpha);
		//Draws label with given text using SDL
		void DrawTextLabel(string message, string fontname, int fontSize, int x, int y, int width, int height, int red, int green, int blue);

		//Loads OpenGL texture
		static unsigned int LoadTexture(string imagename);


		//Get current execution time since SDL environment initialized
		inline float GetTime() const{
			//cout << SDL_GetTicks() << endl << SDL_GetPerformanceCounter() / SDL_GetPerformanceFrequency() << endl << endl;
			//return SDL_GetPerformanceCounter() / SDL_GetPerformanceFrequency();
			return (float)SDL_GetTicks();
		}

		//Game camera getter
		inline Camera* GetCamera(){
			return camera;
		}

		//Adds RenderObject to list to be rendered each frame
		inline void AddRenderObject(RenderObject *ro){
			objectsToRender.push_back(ro);
		}

		//Handle loading of fonts
		void LoadFont(string filename, int fontsize);
		
		//Handle unloading of fonts
		inline void UnloadFonts(){
			for(auto font : fonts){
				TTF_CloseFont(font.font);
			}
		}

		//Render in SDL environment to show info screens (OpenGL usually)
		inline void SDLRender(){
			SDL_RenderPresent(renderer);
			SDL_RenderClear(renderer);
		}


		//Info screens
		void ShowLaunchScreen();
		void ShowControlsScreen();


		/** Shape Rendering functions **/
		//Renders plane
		static void RenderPlane(float x, float y, float z,
			float width, float height, float depth, float matrix[16],
			int red = 45, int green = 85, int blue = 235, int alpha = 255);

		//Renders spere objects
		static void RenderSphere(float radius, float matrix[16], int red = 45, int green = 85, int blue = 235, int alpha = 255);

		//Renders cylinder objects
		static void RenderCylinder(float radius, float height, float matrix[16],
			int red = 45, int green = 85, int blue = 235, int alpha = 255);

		//Renders cone objects
		static void RenderCone(float radius, float height, float matrix[16],
			int red = 45, int green = 85, int blue = 235, int alpha = 255);

		//Renders box objects
		static void RenderBox(float xExtent, float yExtent, float zExtent, float matrix[16],
			int red = 45, int green = 85, int blue = 235, int alpha = 255);


	private:
		SDL_Window *screen;
		SDL_Renderer *renderer;
		SDL_GLContext context;
		GLUquadricObj *quadric;
		Camera *camera;
		vector<RenderObject*> objectsToRender;
		vector<Font> fonts;

		//Retrieves text font resource if found/loaded
		inline TTF_Font* GetFont(string filename, int fontsize){
			for(auto font : fonts){
				if(font.name == filename && font.size == fontsize){
					return font.font;
				}
			}
			cout << "Error: font "<< filename << " with size " << fontsize << " not found" << endl;
			return nullptr;
		}
};