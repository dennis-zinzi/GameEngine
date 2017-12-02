/**
 * 3D OpenGL camera class
 * Code adapted from YouTube OpenGL tutorial series (https://pastebin.com/Zbg0gxVj)
 */


#pragma once

#include "common.h"
#include "../SDL2-2.0.5/include/SDL.h"

#include "../glew-2.0.0/include/GL/glew.h"
#include "../freeglut/include/GL/freeglut.h"

//Set Camera constants
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

		//Called in main loop to update camera based on input
		void UpdateCamera();
		
		//Camera update XZ + Y coordinates
		void MoveCameraXZ(float dist, float direction);
		void MoveCameraY(float dist, float direction);
		
		//Array representation of camera's x,y, z coordinates
		inline float* GetCameraPos(){
			float pos[3] = {x, y, z};
			return pos;
		}

		//Gets the look vector of the camera (location being pointed at)
		inline float* GetCameraLookVect(){
			//Calculate direction looking at in radians
			float look[3];
			look[0] = -cos(pitch * PI_VAL / 180.0f) * sin(yaw * PI_VAL / 180.0f);
			look[1] = sin(pitch * PI_VAL / 180.0f);
			look[2] = -cos(pitch * PI_VAL / 180.0f) * cos(yaw * PI_VAL / 180.0f);
			
			return look;
		}

		inline void SetCameraLoc(float x = 0.0f, float y = 0.0f, float z = 0.0f){
			this->x = x;
			this->y = y;
			this->z = z;
		}
		inline void SetCameraLoc(float x, float y, float z, float yaw, float pitch){
			this->x = x;
			this->y = y;
			this->z = z;
			this->yaw = yaw;
			this->pitch = pitch;
		}

		void UpdatePitchYaw();

	private:
		float x, y, z;
		float yaw, pitch;
		SDL_Window *window;

		void LockCamera();
		
};