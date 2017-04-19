//#include <SDL.h>
#include "../SDL2-2.0.5/include/SDL.h"
#include "../SDL2-2.0.5/SDL2_ttf-2.0.14/include/SDL_ttf.h"

//OpenGL
//#include <GL/glew.h>
#include "../glew-2.0.0/include/GL/glew.h"

//#include <GL/freeglut.h>
#include "../freeglut/include/GL/freeglut.h"

class GraphicsRenderer{
	public:
		GraphicsRenderer();
		~GraphicsRenderer();

		void OpenGLUpdate();

		bool CheckStillRunning();
		void UpdateScene(float msec);
		void Draw2DRect(int x, int y, int height, int width, int red, int green, int blue, int alpha);
		void DrawTextLabel();

		inline int GetTime() const{
			return SDL_GetTicks();
		}

		static void RenderPlane(float halfWidth, float halfHeight, float halfDepth, float matrix[16],
			int red = 45, int green = 85, int blue = 235, int alpha = 255);

		static void RenderSphere(float radius, float matrix[16], int red = 45, int green = 85, int blue = 235, int alpha = 255);

	private:
		SDL_Window *screen;
		SDL_Renderer *renderer;
		SDL_GLContext context;
		GLUquadricObj *quadric;
};