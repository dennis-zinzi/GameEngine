#pragma once

#include "GameObject.h"
#include <iostream>

using std::cout;
using std::endl;

class Player : public GameObject{
	public:
		Player(GraphicsRenderer &renderer, Camera *camera, btRigidBody *physicalBody, float width, float height, float depth,
			int red = 127, int green = 127, int blue = 127, int alpha = 255);

		Player(GraphicsRenderer &renderer, PhysicsManager &physics, float radius, float mass = 5.0f,
			int red = 68, int green = 195, int blue = 18, int alpha = 255);

		virtual void Render() override;

	private:
		Camera *camera;
};