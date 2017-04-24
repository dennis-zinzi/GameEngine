#pragma once

//#include <SDL.h>
#include "../SDL2-2.0.5/include/SDL.h"
#include "../SDL2-2.0.5/SDL2_ttf-2.0.14/include/SDL_ttf.h"
#include "../SDL2-2.0.5/SDL2_image-2.0.1/include/SDL_image.h"
#include "../SOIL/SOIL.h"

//OpenGL
//#include <GL/glew.h>
#include "../glew-2.0.0/include/GL/glew.h"

//#include <GL/freeglut.h>
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

class GraphicsRenderer{
	public:
		GraphicsRenderer();
		~GraphicsRenderer();

		void OpenGLUpdate();

		bool CheckStillRunning();
		void UpdateScene(float msec);
		void Draw2DRect(int x, int y, int height, int width, int red, int green, int blue, int alpha);
		void DrawTextLabel();

		static unsigned int LoadTexture(string imagename);

		inline int GetTime() const{
			return SDL_GetTicks();
		}

		inline Camera* GetCamera(){
			return camera;
		}

		inline void AddRenderObject(RenderObject *ro){
			objectsToRender.push_back(ro);
		}

		//inline void RemoveRenderObject(RenderObject *ro){
		//	objectsToRender.erase(ro);
		//}

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
		static GLuint GraphicsRenderer::tex;
		vector<RenderObject*> objectsToRender;

};