/**
 * Representation of game object to work with engine
 * @author: Dennis Zinzi (130301136)
 */

#pragma once

#include <btBulletDynamicsCommon.h>
#include "../Physics/PhysicsManager.h"
#include "../Physics/PhysicsObject.h"
#pragma comment(lib, "Physics.lib")

#include "../Graphics/GraphicsRenderer.h"
#include "../Graphics/RenderObject.h"
#pragma comment(lib, "Graphics.lib")

#include "../Audio/AudioPlayer.h"
#pragma comment(lib, "Audio.lib")

#include "GameLevel.h"

//Represent allowed shapes to be drawn
enum Shape{
	Plane,
	Sphere,
	Cylinder,
	Cone,
	Box
};

enum Type{
	Target,
	NonTarget,
	Bullet,
	PLAYER,
	Floor,
	Other
};

class GameObject : public RenderObject, public PhysicsObject{
	public:
		/* GameObject constructors */
		GameObject(GraphicsRenderer *renderer, PhysicsManager *physics, AudioPlayer *audio, int red = 127, int green = 127, int blue = 127, int alpha = 255);
		GameObject(GraphicsRenderer *renderer, PhysicsManager *physics, AudioPlayer *audio, btRigidBody *body, float width, float height, float depth,
			int red = 127, int green = 127, int blue = 127, int alpha = 255);

		//Base constructor
		GameObject(GraphicsRenderer *renderer, PhysicsManager *physics, AudioPlayer *audio, Type type, int red = 127, int green = 127, int blue = 127, int alpha = 255);

		//Spherical shape constructor
		GameObject(GraphicsRenderer *renderer, PhysicsManager *physics, AudioPlayer *audio, Shape shape, Type type, float x, float y, float z, float mass, float radius, float height = 0.0f,
			int red = 127, int green = 127, int blue = 127, int alpha = 255);
		//Rectangular shape constructor
		GameObject(GraphicsRenderer *renderer, PhysicsManager *physics, AudioPlayer *audio, Shape shape, Type type, float x, float y, float z, float mass, float width, float height, float depth,
			int red = 127, int green = 127, int blue = 127, int alpha = 255, string texture = "none");

		//Shape specific render function
		virtual void Render() override;

		//Object Collision Callback
		virtual void HandleHit(PhysicsObject *Other) override;

		inline int GetObjID() const{
			ID++;
			return ID;
		}

		////Get physical representation of game object
		//inline PhysicsObject* GetPhysicalObj() const{
		//	return physicalObj;
		//}

	protected:
		float radius;
		float width, height, depth;
		int red, green, blue, alpha;
		string texture;
		Type objType;

		GraphicsRenderer *renderer;
		PhysicsManager *physics;
		AudioPlayer *audio;
		
		static int ID;

};