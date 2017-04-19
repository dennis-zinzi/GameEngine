#include "GraphicsRenderer.h"


#define FRAME_RATE 60
#define WINDOW_HEIGHT 720
#define WINDOW_WIDTH 1200


GraphicsRenderer::GraphicsRenderer(){
	SDL_Init(SDL_INIT_EVERYTHING);
	screen = SDL_CreateWindow("SDL Engine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_OPENGL);
	renderer = SDL_CreateRenderer(screen, -1, 0);
	context = SDL_GL_CreateContext(screen);

	//Set OpenGL attribs
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	
	//OpenGL
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f, WINDOW_WIDTH / WINDOW_HEIGHT, 1.0f, 500.0f);
	glMatrixMode(GL_MODELVIEW);

	quadric = gluNewQuadric();
}

GraphicsRenderer::~GraphicsRenderer(){
	//gluDeleteQuadric(quadric);
	SDL_Quit();
}


void GraphicsRenderer::OpenGLUpdate(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	//glBegin(GL_TRIANGLES);
	//{
	//	glVertex3f(1.0f, 1.0f, -5.0f);
	//	glVertex3f(-1.0f, -1.0f, -5.0f);
	//	glVertex3f(1.0f, -1.0f, -5.0f);
	//}
	//glEnd();
}


bool GraphicsRenderer::CheckStillRunning(){
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

void GraphicsRenderer::UpdateScene(float msec){
	//SDL_SetRenderDrawColor(GraphicsRenderer, 79, 79, 79, 255);
	//SDL_RenderClear(GraphicsRenderer);

	//Additional stuff render here
	//DrawTextLabel();
	/*Draw2DRect(10, 10, 100, 200, 100, 205, 222, 200);*/
	//RenderPlane(1000, 0, )
	//End
	
	//SDL_RenderPresent(GraphicsRenderer);

	//OpenGLUpdate();
	//gluSphere(gluNewQuadric(), 10.0f, 20.0f, 20.0f);

	SDL_GL_SwapWindow(screen);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	if(1000 / FRAME_RATE > SDL_GetTicks() - msec){
		SDL_Delay((Uint32)((1000 / FRAME_RATE) - (SDL_GetTicks() - msec)));
	}
}


void GraphicsRenderer::Draw2DRect(int x, int y, int height, int width,
	int red, int green, int blue, int alpha){

	SDL_Rect rect;
	rect.x = x;
	rect.y = y;
	rect.h = height;
	rect.w = width;

	SDL_SetRenderDrawColor(renderer, red, green, blue, alpha);
	SDL_RenderFillRect(renderer, &rect);
}


void GraphicsRenderer::DrawTextLabel(){
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

	//SDL_SetRenderDrawColor(GraphicsRenderer, 66, 244, 217, 255);

	//SDL_BlitSurface(text, nullptr, SDL_GetWindowSurface(screen), nullptr);

	TTF_CloseFont(font);
}

void GraphicsRenderer::RenderPlane(float halfWidth, float halfHeight, float halfDepth, float matrix[16],
	int red, int green, int blue, int alpha){
	glColor4f(red / 255.0f, green / 255.0f, blue / 255.0f, alpha / 255.0f);

	glPushMatrix();
	{
		glMultMatrixf(matrix);
		glBegin(GL_QUADS);
		{
			//TODO - Need to think about this
			glVertex3f(-halfWidth, halfHeight, halfDepth);
			glVertex3f(-halfWidth, halfHeight, -halfDepth);
			glVertex3f(halfWidth, -halfHeight, -halfDepth);
			glVertex3f(halfWidth, -halfHeight, halfDepth);
		}
		glEnd();
	}
	glPopMatrix();
}

void GraphicsRenderer::RenderSphere(float radius, float matrix[16], int red, int green, int blue, int alpha){
	glColor4f(red / 255.0f, green / 255.0f, blue / 255.0f, alpha / 255.0f);

	GLUquadricObj *quadr = gluNewQuadric();
	glPushMatrix();
	{
		glMultMatrixf(matrix); //translation + rotation
		gluSphere(quadr, radius, 100.0f, 100.0f);
	}
	glPopMatrix();

	gluDeleteQuadric(quadr);
}
