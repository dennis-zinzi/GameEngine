#include "GraphicsRenderer.h"


#define FRAME_RATE 60
#define WINDOW_HEIGHT 720
#define WINDOW_WIDTH 1200


GraphicsRenderer::GraphicsRenderer(){
	SDL_Init(SDL_INIT_EVERYTHING);
	screen = SDL_CreateWindow("SDL Engine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_OPENGL);
	renderer = SDL_CreateRenderer(screen, -1, 0);
	context = SDL_GL_CreateContext(screen);
	IMG_Init(IMG_INIT_JPG);
	IMG_Init(IMG_INIT_PNG);
	
	//Set OpenGL attribs
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	
	//OpenGL
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f, WINDOW_WIDTH / WINDOW_HEIGHT, 1.0f, 500.0f);
	glMatrixMode(GL_MODELVIEW);
	
	//Enable Alpha blending
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
	
	//Enable depth test (Causes z-fighting)
	glEnable(GL_DEPTH_TEST);

	//Enable texture mapping
	glEnable(GL_TEXTURE_2D);
}

GraphicsRenderer::~GraphicsRenderer(){
	glDisable(GL_TEXTURE_2D);
	SDL_Quit();
}


bool GraphicsRenderer::CheckStillRunning(){
	SDL_Event event;

	//Runs whilst any event being queued
	while(SDL_PollEvent(&event)){
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

	//SDL update render	
	//SDL_RenderPresent(GraphicsRenderer);

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


unsigned int GraphicsRenderer::LoadTexture(string imagename){
	//Get full image path
	string imagePath = IMAGE_PATH + imagename;

	//SDL_Surface *image = IMG_Load(imagePath.c_str());
	//if(!image){
	//	cout << "Error loading image: " << IMG_GetError() << endl;
	//	//cout << imagePath << " not found, check path" << endl;
	//	return -1;
	//}

	//unsigned int texID = 0;
	//glGenTextures(1, &texID);
	//glBindTexture(GL_TEXTURE_2D, texID);


	//int mode = GL_RGB;
	//if(image->format->BytesPerPixel == 4){
	//	if(image->format->Rmask == 0x000000ff){
	//		cout << "4yay" << endl;
	//		mode = GL_RGBA;
	//	}
	//	else{
	//		cout << "4b" << endl;
	//		mode = GL_BGRA;
	//	}
	//}
	//else if(image->format->BytesPerPixel == 3){
	//	if(image->format->Rmask == 0x000000ff){
	//		cout << "3yay" << endl;
	//		mode = GL_RGB;
	//	}
	//	else{
	//		cout << "3b" << endl;
	//		mode = GL_BGR;
	//	}
	//}

	//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image->w, image->h, 0, mode, GL_UNSIGNED_BYTE, image->pixels);

	//if(glGetError() == GL_NO_ERROR){ cout << "Nice" << endl; }
	//if(glGetError() != GL_NO_ERROR){
	//	cout << "Error: " << gluErrorString(glGetError()) << endl;
	//}

	////glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	////glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

	////glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	////glGenerateMipmap(GL_TEXTURE_2D);

	////Release image surface
	//SDL_FreeSurface(image);

	GLuint texID = SOIL_load_OGL_texture(imagePath.c_str(), SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS);
	glBindTexture(GL_TEXTURE_2D, texID);

	//Set filters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	//glGenerateMipmap(GL_TEXTURE_2D);

	return texID;
}


void GraphicsRenderer::RenderPlane(float x, float y, float z,
	float width, float height, float depth, float matrix[16],
	int red, int green, int blue, int alpha){
	glColor4f(red / 255.0f, green / 255.0f, blue / 255.0f, alpha / 255.0f);

	float halfWidth = width / 2.0f,
		halfHeight = height / 2.0f,
		halfDepth = depth / 2.0f;

	//GLuint tex = LoadTexture("chess_board.jpg");
	//GLuint tex = SOIL_load_OGL_texture(IMAGE_PATH"chessboard.jpg", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS);
	//glGenTextures(1, &tex);
	//glBindTexture(GL_TEXTURE_2D, tex);

	//LoadTexture("chess_board.jpg");
	GLuint tex = LoadTexture("chess_board.jpg");
	if(tex == 0){ cout << SOIL_last_result() << endl; }
	glBindTexture(GL_TEXTURE_2D, tex);

	glPushMatrix();
	{
		glMultMatrixf(matrix);
		glBegin(GL_QUADS);
		{
			//TODO - Need to think about this
			glTexCoord2f(0, 0);
			glVertex3f(x - halfWidth, y + halfHeight, z + halfDepth);
			glTexCoord2f(0, 1);
			glVertex3f(x - halfWidth, y + halfHeight, z - halfDepth);
			glTexCoord2f(1, 1);
			glVertex3f(x + halfWidth, y - halfHeight, z - halfDepth);
			glTexCoord2f(1, 0);
			glVertex3f(x + halfWidth, y - halfHeight, z + halfDepth);
		}
		glEnd();
	}
	glPopMatrix();

	//SOIL_free_image_data(img);
	glBindTexture(GL_TEXTURE_2D, 0);
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


void GraphicsRenderer::RenderCylinder(float radius, float height, float matrix[16],
	int red, int green, int blue, int alpha){
	glColor4f(red / 255.0f, green / 255.0f, blue / 255.0f, alpha / 255.0f);

	GLUquadricObj *quadr = gluNewQuadric();
	glPushMatrix();
	{
		glMultMatrixf(matrix); //translation + rotation
		glTranslatef(0.0f, height / 2.0f, 0.0f);
		glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
		gluCylinder(quadr, radius, radius, height, 100.0f, 100.0f);
	}
	glPopMatrix();

	gluDeleteQuadric(quadr);
}


void GraphicsRenderer::RenderCone(float radius, float height, float matrix[16],
	int red, int green, int blue, int alpha){
	glColor4f(red / 255.0f, green / 255.0f, blue / 255.0f, alpha / 255.0f);

	GLUquadricObj *quadr = gluNewQuadric();
	glPushMatrix();
	{
		glMultMatrixf(matrix); //translation + rotation
		//glRotatef(deg, !!x-axis, !!y-axis, !!z-axis); 
		glTranslatef(0, height / 2.0f, 0);
		glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
		gluCylinder(quadr, 0, radius, height, 100.0f, 100.0f);
	}
	glPopMatrix();

	gluDeleteQuadric(quadr);
}


void GraphicsRenderer::RenderBox(float xExtent, float yExtent, float zExtent, float matrix[16],
	int red, int green, int blue, int alpha){

	glColor4f(red / 255.0f, green / 255.0f, blue / 255.0f, alpha / 255.0f);

	//unsigned int tex = LoadTexture("chess_board.jpg");
	GLuint tex = SOIL_load_OGL_texture(IMAGE_PATH"chessboard.jpg", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS);
	glBindTexture(GL_TEXTURE_2D, tex);
	glEnable(GL_TEXTURE_2D);

	glPushMatrix();
	{
		glMultMatrixf(matrix);
		//Back
		glBegin(GL_QUADS);
		{
			glVertex3f(-xExtent, -yExtent, -zExtent);
			glVertex3f(-xExtent, yExtent, -zExtent);
			glVertex3f(xExtent, yExtent, -zExtent);
			glVertex3f(xExtent, -yExtent, -zExtent);
		}
		glEnd();
		//Left
		glBegin(GL_QUADS);
		{
			glVertex3f(-xExtent, -yExtent, zExtent);
			glVertex3f(-xExtent, yExtent, zExtent);
			glVertex3f(-xExtent, yExtent, -zExtent);
			glVertex3f(-xExtent, -yExtent, -zExtent);
		}
		glEnd();
		//Right
		glBegin(GL_QUADS);
		{
			glVertex3f(xExtent, -yExtent, zExtent);
			glVertex3f(xExtent, yExtent, zExtent);
			glVertex3f(xExtent, yExtent, -zExtent);
			glVertex3f(xExtent, -yExtent, -zExtent);
		}
		glEnd();
		//Bottom
		glBegin(GL_QUADS);
		{
			glVertex3f(-xExtent, -yExtent, zExtent);
			glVertex3f(-xExtent, -yExtent, -zExtent);
			glVertex3f(xExtent, -yExtent, -zExtent);
			glVertex3f(xExtent, -yExtent, zExtent);
		}
		glEnd();
		//Top
		glBegin(GL_QUADS);
		{
			glVertex3f(-xExtent, yExtent, zExtent);
			glVertex3f(-xExtent, yExtent, -zExtent);
			glVertex3f(xExtent, yExtent, -zExtent);
			glVertex3f(xExtent, yExtent, zExtent);
		}
		glEnd();
		//Front
		glBegin(GL_QUADS);
		{
			glTexCoord2f(0, 0);
			glVertex3f(-xExtent, -yExtent, zExtent);
			glTexCoord2f(0, 1);
			glVertex3f(-xExtent, yExtent, zExtent);
			glTexCoord2f(1, 1);
			glVertex3f(xExtent, yExtent, zExtent);
			glTexCoord2f(1, 0);
			glVertex3f(xExtent, -yExtent, zExtent);
		}
		glEnd();
	}
	glPopMatrix();

	glDisable(GL_TEXTURE_2D);
	glDeleteTextures(1, &tex);
}