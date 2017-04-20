#pragma once

#include <btBulletDynamicsCommon.h>
#include "../Graphics/GraphicsRenderer.h"
#pragma comment(lib, "Graphics.lib")

class GameObject{
	public:
		GameObject(btRigidBody *physicalBody, int red = 127, int green = 127, int blue = 127, int alpha = 255);
		GameObject(btRigidBody *physicalBody, float width, float height, float depth,
			int red = 127, int green = 127, int blue = 127, int alpha = 255);

		void RenderObject();

	private:
		btRigidBody *physicalBody;
		float radius;
		float width, height, depth;
		int red, green, blue, alpha;

};