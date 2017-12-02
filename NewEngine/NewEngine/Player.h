#pragma once

#include "GameLevel.h"
#include "GameObject.h"
#include <iostream>

#include "../HumanInterface/InputPlayer.h"
#pragma comment(lib, "HumanInterface.lib")

#include "../Audio/AudioPlayer.h"
#pragma comment(lib, "Audio.lib")

using std::cout;
using std::endl;

class Player : public InputPlayer, public PhysicsPlayer{
	public:
		Player(GraphicsRenderer *renderer, PhysicsManager *physics, AudioPlayer *player, float width, float height, float depth, float mass = 5.0f,
			int red = 68, int green = 195, int blue = 18, int alpha = 255);

		Player(GraphicsRenderer *renderer, PhysicsManager *physics, AudioPlayer *player, float radius, float mass = 5.0f,
			int red = 68, int green = 195, int blue = 18, int alpha = 255);

		void MovePhysicObj(float x1, float x2, float y1, float y2, float z1, float z2);

		//virtual void Render() override;
		virtual void Tick() override;

		virtual void MoveLeft() override;
		virtual void MoveForward() override;
		virtual void MoveRight() override;
		virtual void MoveBackward() override;
		virtual void Jump() override;
		virtual void Shoot() override;
		virtual void NoMovement() override;
		virtual void ShowControls(bool show) override;

		inline Camera* GetCamera(){
			return camera;
		}
		inline void SetPlayerPos(float x, float y, float z){
			camera->SetCameraLoc(x, y, z);
			charController->getGhostObject()->getWorldTransform().setOrigin(btVector3(x, y, z));
		}


	private:
		Camera *camera;

		GraphicsRenderer *renderer;
		PhysicsManager *physics;
		AudioPlayer *audio;
};