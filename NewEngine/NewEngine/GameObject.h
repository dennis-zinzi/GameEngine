#pragma once

#include <btBulletDynamicsCommon.h>
#include "../Physics/PhysicsManager.h"
#pragma comment(lib, "Physics.lib")

#include "../Graphics/GraphicsRenderer.h"
#include "../Graphics/RenderObject.h"
#pragma comment(lib, "Graphics.lib")

enum Shape{
	Plane,
	Sphere,
	Cylinder,
	Cone,
	Box
};

class GameObject : public RenderObject{
	public:
		GameObject(GraphicsRenderer &renderer, btRigidBody *physicalBody, int red = 127, int green = 127, int blue = 127, int alpha = 255);
		GameObject(GraphicsRenderer &renderer, btRigidBody *physicalBody, float width, float height, float depth,
			int red = 127, int green = 127, int blue = 127, int alpha = 255);

		GameObject(GraphicsRenderer &renderer, int red = 127, int green = 127, int blue = 127, int alpha = 255);
		GameObject(GraphicsRenderer &renderer, PhysicsManager &physics, Shape shape, float x, float y, float z, float mass, float radius, float height = 0.0f,
			int red = 127, int green = 127, int blue = 127, int alpha = 255);
		GameObject(GraphicsRenderer &renderer, PhysicsManager &physics, Shape shape, float x, float y, float z, float mass, float width, float height, float depth,
			int red = 127, int green = 127, int blue = 127, int alpha = 255);


		virtual void Render();

	protected:
		btRigidBody *physicalBody;
		float radius;
		float width, height, depth;
		int red, green, blue, alpha;

};