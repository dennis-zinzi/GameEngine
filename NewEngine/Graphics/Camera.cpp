#include "Camera.h"
#include <math.h>

Camera::Camera(SDL_Window *window){
	x = 0.0f;
	y = 0.0f;
	z = 0.0f;
	yaw = 0.0f;
	pitch = 5.0f;
	this->window = window;

	//Don't show mouse
	SDL_ShowCursor(SDL_DISABLE);

	//Move mouse to center of screen
	SDL_WarpMouseInWindow(window, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
}

//Keeps pitch and yaw within appropriate bounds
void Camera::LockCamera(){
	if(pitch > MAX_PITCH){
		pitch = MAX_PITCH;
	}
	if(pitch < MIN_PITCH){
		pitch = MIN_PITCH;
	}

	if(yaw < MIN_YAW){
		yaw += MAX_YAW;
	}
	if(yaw > MAX_YAW){
		yaw -= MAX_YAW;
	}
}


void Camera::MoveCameraXZ(float dist, float direction){
	//Calculate direction looking at in radians
	float radAngle = ((yaw + direction) * PI_VAL) / 180.0f;

	if(pitch != MAX_PITCH && pitch != MIN_PITCH){
		x -= sin(radAngle) * dist;
		z -= cos(radAngle) * dist;
	}
}

void Camera::MoveCameraY(float dist, float direction){
	//Calculate direction looking at in radians
	float radAngle = ((pitch + direction) * PI_VAL) / 180.0f;

	y += sin(radAngle) * dist;
}


void Camera::UpdatePitchYaw(){
	int windowCenterX = WINDOW_WIDTH / 2,
		windowCenterY = WINDOW_HEIGHT / 2;

	int mouseX, mouseY;

	SDL_GetMouseState(&mouseX, &mouseY);

	yaw += MOUSE_VEL * (windowCenterX - mouseX);
	pitch += MOUSE_VEL * (windowCenterY - mouseY);

	//Lock camera in bounds
	LockCamera();
	
	//Move mouse back to center of screen
	SDL_WarpMouseInWindow(window, windowCenterX, windowCenterY);

	glRotatef(-pitch, 1.0f, 0.0f, 0.0f);
	glRotatef(-yaw, 0.0f, 1.0f, 0.0f);
}


void Camera::UpdateCamera(){
	UpdatePitchYaw();
	glTranslatef(-x, -y, -z);

	SDL_Delay((Uint32)(1000 / (FRAME_RATE * 8)));
}