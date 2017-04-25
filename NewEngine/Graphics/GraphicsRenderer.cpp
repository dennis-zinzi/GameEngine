#include "GraphicsRenderer.h"
GLuint GraphicsRenderer::tex = LoadTexture("chess_board.jpg");

GraphicsRenderer::GraphicsRenderer(){
	SDL_Init(SDL_INIT_EVERYTHING);
	screen = SDL_CreateWindow("SDL Engine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_OPENGL);
	renderer = SDL_CreateRenderer(screen, -1, 0);
	context = SDL_GL_CreateContext(screen);
	IMG_Init(IMG_INIT_JPG);
	IMG_Init(IMG_INIT_PNG);
	TTF_Init();

	//Set up camera
	camera = new Camera(screen);
	
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
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
}

GraphicsRenderer::~GraphicsRenderer(){
	for(auto ro : objectsToRender){
		delete ro;
	}

	glDisable(GL_TEXTURE_2D);
	SDL_Quit();
}


void GraphicsRenderer::UpdateScene(float msec){
	//SDL_SetRenderDrawColor(GraphicsRenderer, 79, 79, 79, 255);
	//SDL_RenderClear(renderer);
	
	//SDL update render	
	//SDL_RenderPresent(renderer);

	for(auto ro : objectsToRender){
		ro->Render();
	}

	SDL_GL_SwapWindow(screen);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();


	if(1000 / FRAME_RATE > SDL_GetTicks() - msec){
		SDL_Delay((Uint32)((1000 / FRAME_RATE) - (SDL_GetTicks() - msec)));
	}

	camera->UpdateCamera();
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


void GraphicsRenderer::DrawTextLabel(string message, string fontname, int fontsize, int x, int y, int width, int height, int red, int green, int blue){
	//TTF_Font *font = TTF_OpenFont("../Assets/Fonts/UnifrakturCook-Bold.ttf", 180);
	TTF_Font *font = GetFont(fontname, fontsize);//TTF_OpenFont("../Assets/Fonts/Invasion2000.ttf", fontSize);
	if(!font){
		return;
	}


	SDL_Color textColor = {red, blue, green};
	SDL_Surface *text = TTF_RenderText_Solid(font, message.c_str(), textColor);
	SDL_Texture *messageTex = SDL_CreateTextureFromSurface(renderer, text);

	SDL_Rect textRect;
	textRect.x = x;
	textRect.y = y;
	textRect.h = height;
	textRect.w = width;

	SDL_RenderCopy(renderer, messageTex, nullptr, &textRect);

	//TTF_CloseFont(font);
	SDL_FreeSurface(text);
	SDL_DestroyTexture(messageTex);
}


unsigned int GraphicsRenderer::LoadTexture(string imagename){
	//Get full image path
	string imagePath = IMAGE_PATH + imagename;
	
	SDL_Surface *img = IMG_Load(imagePath.c_str());
	if(img == NULL){
		cout << "ERROR: " << imagename << " not found" << endl;
		return -1;
	}

	SDL_Surface *img2 = SDL_ConvertSurfaceFormat(img, SDL_PIXELFORMAT_RGBA8888, 0);
	if(!img2){
		cout << "ERROR: Couln't convert " << imagename << endl;
		return -1;
	}

	unsigned int tex;
	glGenTextures(1, &tex);
	glBindTexture(GL_TEXTURE_2D, tex);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, img->w, img2->h, 0, GL_RGBA, GL_UNSIGNED_INT_8_8_8_8, img2->pixels);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	
	SDL_FreeSurface(img);
	SDL_FreeSurface(img2);

	return tex;
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
	//GLuint tex = LoadTexture("chess_board.jpg");
	//if(tex == 0){ cout << SOIL_last_result() << endl; }
	glBindTexture(GL_TEXTURE_2D, tex);

	//cout << tex << endl;

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
	//glBindTexture(GL_TEXTURE_2D, 0);
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


void GraphicsRenderer::ShowLaunchScreen(){
	//Show at start up
	DrawTextLabel("Loading Engine... please wait", "Invasion2000.TTF", 180, 150, 0, 900, 150, 66, 244, 217);
	ShowControlsScreen();
}


void GraphicsRenderer::ShowControlsScreen(){
	DrawTextLabel("Controls", "Invasion2000.TTF", 100, WINDOW_WIDTH / 2 - 130, 125, 300, 150, 100, 200, 100);

	DrawTextLabel("Movement:", "Invasion2000.TTF", 75, 300, 275, 200, 50, 100, 200, 100);
	DrawTextLabel("W A S D", "Invasion2000.TTF", 50, 700, 275, 200, 50, 100, 200, 100);

	DrawTextLabel("Camera:", "Invasion2000.TTF", 75, 300, 350, 200, 50, 100, 200, 100);
	DrawTextLabel("Mouse", "Invasion2000.TTF", 50, 700, 350, 200, 50, 100, 200, 100);

	DrawTextLabel("Shoot:", "Invasion2000.TTF", 75, 300, 425, 200, 50, 100, 200, 100);
	DrawTextLabel("Click", "Invasion2000.TTF", 50, 700, 425, 200, 50, 100, 200, 100);

	DrawTextLabel("Jump:", "Invasion2000.TTF", 75, 300, 500, 200, 50, 100, 200, 100);
	DrawTextLabel("Space", "Invasion2000.TTF", 50, 700, 500, 200, 50, 100, 200, 100);

	DrawTextLabel("Show Controls:", "Invasion2000.TTF", 75, 300, 575, 200, 50, 100, 200, 100);
	DrawTextLabel("  P  ", "Invasion2000.TTF", 50, 700, 575, 200, 50, 100, 200, 100);

	DrawTextLabel("Exit:", "Invasion2000.TTF", 75, 300, 650, 200, 50, 100, 200, 100);
	DrawTextLabel(" Esc ", "Invasion2000.TTF", 50, 700, 650, 200, 50, 100, 200, 100);

	SDLRender();
	SDL_Delay(500);
}


void GraphicsRenderer::LoadFont(string filename, int fontsize){
	string filePath = FONT_PATH + filename;

	TTF_Font *font = TTF_OpenFont(filePath.c_str(), fontsize);
	if(!font){
		cout << "ERROR: could not find font " << filename << endl;
		return;
	}

	Font f = {filename, fontsize, font};
	fonts.push_back(f);
}