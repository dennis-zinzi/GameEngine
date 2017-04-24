#pragma once

#include "GameObject.h"
#include <iostream>

#include "../HumanInterface/InputPlayer.h"
#pragma comment(lib, "HumanInterface.lib")

using std::cout;
using std::endl;

class Player : public GameObject, public InputPlayer{
	public:
		Player(GraphicsRenderer &renderer, Camera *camera, btRigidBody *physicalBody, float width, float height, float depth,
			int red = 127, int green = 127, int blue = 127, int alpha = 255);

		Player(GraphicsRenderer &renderer, PhysicsManager &physics, float width, float height, float depth, float mass = 5.0f,
			int red = 68, int green = 195, int blue = 18, int alpha = 255);

		Player(GraphicsRenderer &renderer, PhysicsManager &physics, float radius, float mass = 5.0f,
			int red = 68, int green = 195, int blue = 18, int alpha = 255);

		void MovePhysicObj();

		virtual void Render() override;

		virtual void MoveLeft() override;
		virtual void MoveForward() override;
		virtual void MoveRight() override;
		virtual void MoveBackward() override;
		virtual void Jump() override;
		virtual void Shoot() override;
		virtual void NoMovement() override;

	private:
		Camera *camera;
		GraphicsRenderer *renderer;
		PhysicsManager *physics;
};