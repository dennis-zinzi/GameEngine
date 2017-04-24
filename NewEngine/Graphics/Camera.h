#pragma once

#include "common.h"
#include "../SDL2-2.0.5/include/SDL.h"

#include "../glew-2.0.0/include/GL/glew.h"
#include "../freeglut/include/GL/freeglut.h"

#define MAX_PITCH 90.0f
#define MIN_PITCH -90.0f

#define MAX_YAW 360.0f
#define MIN_YAW 0.0f

#define MOUSE_VEL 0.5f

#include <iostream>
using std::cout;
using std::endl;

class Camera{
	public:
		Camera(SDL_Window *window);
		~Camera();

		void UpdateCamera();
		
		void MoveCameraXZ(float dist, float direction);
		void MoveCameraY(float dist, float direction);
		void ControlCamera();

		inline float* GetCameraPos(){
			float pos[3] = {x, y, z};
			return pos;
		}

		inline float* GetCameraLookVect(){
			////Calculate direction looking at in radians
			//float radAngle = ((yaw) * PI_VAL) / 180.0f;

			//if(pitch != MAX_PITCH && pitch != MIN_PITCH){
			//	float tempx = x - sin(radAngle);
			//	float tempz = z - cos(radAngle);

			//	float pos[3] = {tempx, y, tempz};
			//	return pos;
			//}
			float look[3];
			look[0] = -cos(pitch * M_PI / 180.0) * sin(yaw * M_PI / 180.0);
			look[1] = sin(pitch * M_PI / 180.0);
			look[2] = -cos(pitch * M_PI / 180.0) * cos(yaw * M_PI / 180.0);
			
			return look;
		}

	private:
		float x, y, z;
		float yaw, pitch;
		SDL_Window *window;

		void LockCamera();
};