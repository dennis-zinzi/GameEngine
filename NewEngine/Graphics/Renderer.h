//#include <SDL.h>
#include "../SDL2-2.0.5/include/SDL.h"
#include "../SDL2-2.0.5/SDL2_ttf-2.0.14/include/SDL_ttf.h"

class Renderer{
	public:
		Renderer();
		~Renderer();

		void OpenGLUpdate();

		bool CheckStillRunning();
		void UpdateScene(float msec);
		void Draw2DRect(int x, int y, int height, int width, int red, int green, int blue, int alpha);
		void DrawTextLabel();

		inline int GetTime() const{
			return SDL_GetTicks();
		}

	private:
		SDL_Window *screen;
		SDL_Renderer *renderer;
		SDL_GLContext context;
};