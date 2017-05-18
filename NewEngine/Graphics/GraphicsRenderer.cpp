#include "GraphicsRenderer.h"

vector<Texture> GraphicsRenderer::textures;

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

	//Game vars
	startTime = SDL_GetTicks() / 1000;
	gameTime = 90;//startTime;
	
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
	glDepthMask(GL_TRUE);

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

	//Switch to orthographic to render HUD
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, WINDOW_WIDTH, 0, WINDOW_HEIGHT, 1.0, -1.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glDepthMask(GL_FALSE);
	
	//glTranslatef(10, 100, 0);

	string score = "Score: " + to_string(msec*.1f);
	LoadSDLText(score, "Invasion2000.TTF", 50, 50, 650, 100, 50, 0, 255, 0);

	glLoadIdentity();
	
	stringstream minsstream;
	minsstream << setw(2) << setfill('0') << to_string(gameTime / 60);
	string mins = minsstream.str();

	stringstream secsstream;
	secsstream << setw(2) << setfill('0') << to_string(gameTime % 60);
	string secs = secsstream.str();

	string time = mins + ":" + secs;
	LoadSDLText(time, "Invasion2000.TTF", 50, 600, 600, 100, 50, 0, 150, 200);

	//Draw aim assist
	glLoadIdentity();
	//glColor4f(42 / 255.0f, 166 / 255.0f, 137 / 255.0f, 255 / 255.0f);
	glTranslatef((WINDOW_WIDTH / 2.0f) - 30.0f, (WINDOW_HEIGHT / 2.0f) - 30.0f, 0);
	GetTexture("aimassist.png");

	glPushMatrix();
	{
		//glMultMatrixf(matrix);
		glEnable(GL_TEXTURE_2D);
		glBegin(GL_QUADS);
		{
			//TODO - Need to think about this
			glTexCoord2f(0, 1);
			glVertex3f(0, 60, 0);
			glTexCoord2f(0, 0);
			glVertex3f(0, 0, 0);
			glTexCoord2f(1, 0);
			glVertex3f(60, 0, 0);
			glTexCoord2f(1, 1);
			glVertex3f(60, 60, 0);
		}
		glEnd();
		glDisable(GL_TEXTURE_2D);
	}
	glPopMatrix();



	//Go back to perspective
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(90, WINDOW_WIDTH / WINDOW_HEIGHT, 1.0f, 500.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glDepthMask(GL_TRUE);

	camera->UpdateCamera();
	glPushMatrix();


	for(auto ro : objectsToRender){
		ro->Render();
	}

	glPopMatrix();

	// Restore old ortho
	glMatrixMode(GL_PROJECTION);
	glMatrixMode(GL_MODELVIEW);


	SDL_GL_SwapWindow(screen);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	if(1000 / FRAME_RATE > GetTime() - msec){
		SDL_Delay((Uint32)((1000 / FRAME_RATE) - (GetTime() - msec)));
	}

	gameTime = 90 - ((SDL_GetTicks() / 1000) - startTime);
	//camera->UpdateCamera();
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


	SDL_Color textColor = {red, green, blue};
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
	unsigned int t = GetTexture(imagename);
	if(t != -1){
		return t;
	}

	//Get full image path
	string imagePath = IMAGE_PATH + imagename;
	
	
	unsigned int tex = SOIL_load_OGL_texture(imagePath.c_str(), SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS);;
	//glGenTextures(1, &tex);
	
	
	//glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, tex);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

	Texture texture = {imagename, tex};
	textures.push_back(texture);

	cout << "Loaded texture: " << imagename << endl;

	return tex;
}

SDL_Texture* GraphicsRenderer::LoadSDLText(string message, string fontname, int fontsize, int x, int y, int width, int height, int red, int green, int blue){
	TTF_Font *font = GetFont(fontname, fontsize);//TTF_OpenFont("../Assets/Fonts/Invasion2000.ttf", fontSize);
	if (!font){
		return nullptr;
	}


	SDL_Color textColor = {red, green, blue};
	SDL_Surface *surface = TTF_RenderText_Blended(font, message.c_str(), textColor);

	//Render font to a SDL_Surface
	if(!surface){
		//TTF_CloseFont(font);
		std::cout << "TTF_RenderText error: " << std::endl;
		return nullptr;
	}

	glTranslatef(x, y, 0);

	GLuint texId;

	//Generate OpenGL texture
	glGenTextures(1, &texId);
	glBindTexture(GL_TEXTURE_2D, texId);

	//Avoid mipmap filtering
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	//Find the first power of two for OpenGL image 
	int w = power_two_floor(surface->w) * 2;
	int h = power_two_floor(surface->h) * 2;

	//Create a surface to the correct size in RGB format, and copy the old image
	SDL_Surface *s = SDL_CreateRGBSurface(0, w, h, 32, 0x00ff0000, 0x0000ff00, 0x000000ff, 0xff000000);
	SDL_BlitSurface(surface, NULL, s, NULL);

	//Copy the created image into OpenGL format
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, s->pixels);

	//Draw the OpenGL texture as a Quad
	glEnable(GL_TEXTURE_2D);
	glBegin(GL_QUADS);
	{
		glTexCoord2d(0, 1); glVertex3f(0, 0, 0);
		glTexCoord2d(1, 1); glVertex3f(0 + surface->w, 0, 0);
		glTexCoord2d(1, 0); glVertex3f(0 + surface->w, 0 + surface->h, 0);
		glTexCoord2d(0, 0); glVertex3f(0, 0 + surface->h, 0);
	} glEnd();
	glDisable(GL_TEXTURE_2D);

	//Cleanup
	//SDL_FreeSurface(s);
	//SDL_FreeSurface(surface);
	//glDeleteTextures(1, &texId);

	return nullptr;
}


void GraphicsRenderer::RenderPlane(float x, float y, float z,
	float width, float height, float depth, float matrix[16],
	int red, int green, int blue, int alpha){
	glColor4f(red / 255.0f, green / 255.0f, blue / 255.0f, alpha / 255.0f);

	float halfWidth = width / 2.0f,
		halfHeight = height / 2.0f,
		halfDepth = depth / 2.0f;

	GLuint tex = GetTexture("chess_board.jpg");//GetTexture("checkerboardSmall.jpg");// //LoadTexture("chess_board.jpg");
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	//cout << tex << endl;

	glEnable(GL_TEXTURE_2D);
	glPushMatrix();
	{
		glMultMatrixf(matrix);
		glBegin(GL_QUADS);
		{
			//TODO - Need to think about this
			glTexCoord2f(0, 40);
			glVertex3f(x - halfWidth, 0.0f, z + halfDepth);
			glTexCoord2f(0, 0);
			glVertex3f(x - halfWidth, 0.0f, z - halfDepth);
			glTexCoord2f(40, 0);
			glVertex3f(x + halfWidth, 0.0f, z - halfDepth);
			glTexCoord2f(40, 40);
			glVertex3f(x + halfWidth, 0.0f, z + halfDepth);
		}
		glEnd();
	}
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
	//SOIL_free_image_data(img);
	//glBindTexture(GL_TEXTURE_2D, 0);
}

void GraphicsRenderer::RenderSphere(float radius, float matrix[16], int red, int green, int blue, int alpha){
	glColor4f(red / 255.0f, green / 255.0f, blue / 255.0f, alpha / 255.0f);

	GLuint tex = GetTexture("metal.jpg");

	GLUquadricObj *quadr = gluNewQuadric();
	gluQuadricNormals(quadr, GLU_SMOOTH);
	gluQuadricTexture(quadr, GL_TRUE);

	glEnable(GL_TEXTURE_2D);
	glPushMatrix();
	{
		glMultMatrixf(matrix); //translation + rotation
		gluSphere(quadr, radius, 100.0f, 100.0f);
	}
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);

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

	//int i;
	//int triangleAmount = 20; //# of triangles used to draw circle

	//						 //GLfloat radius = 0.8f; //radius
	//GLfloat twicePi = 2.0f * PI_VAL;

	//glBegin(GL_TRIANGLE_FAN);
	//glVertex2f(radius, height); // center of circle
	//for(i = 0; i <= triangleAmount; i++) {
	//	glVertex2f(
	//		radius + (radius * cos(i *  twicePi / triangleAmount)),
	//		height + (radius * sin(i * twicePi / triangleAmount))
	//		);
	//}
	//glEnd();

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

	//glColor4f(red / 255.0f, green / 255.0f, blue / 255.0f, alpha / 255.0f);
	glColor4f(255, 255, 255, 255);

	//unsigned int tex = LoadTexture("chess_board.jpg");
	//GLuint tex = GetTexture("checkerboardSmall.jpg");
	GLuint tex = GetTexture("target.png");
	if(tex == -1){ cout << "NO TEX" << endl; }
	//glBindTexture(GL_TEXTURE_2D, tex);
	//glEnable(GL_TEXTURE_2D);

	glPushMatrix();
	{
		glMultMatrixf(matrix);
		//Back
		glEnable(GL_TEXTURE_2D);
		glBegin(GL_QUADS);
		{
			glTexCoord2f(0, 0);
			glVertex3f(-xExtent, -yExtent, -zExtent);
			glTexCoord2f(0, 1);
			glVertex3f(-xExtent, yExtent, -zExtent);
			glTexCoord2f(1, 1);
			glVertex3f(xExtent, yExtent, -zExtent);
			glTexCoord2f(1, 0);
			glVertex3f(xExtent, -yExtent, -zExtent);
		}
		glEnd();
		glDisable(GL_TEXTURE_2D);
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
		glEnable(GL_TEXTURE_2D);
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
		glDisable(GL_TEXTURE_2D);
	}
	glPopMatrix();

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