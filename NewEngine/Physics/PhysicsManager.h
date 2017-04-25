#pragma once

/**
 * Handles physical representation of the world and its object
 * Code adapted from YouTube bullet physics tutorial series (https://pastebin.com/Xxv5gBLH)
 */

#include <vector>
#include <btBulletCollisionCommon.h>
#include <btBulletDynamicsCommon.h>

using std::vector;

class PhysicsManager{
	public:
		PhysicsManager();
		~PhysicsManager();

		//Timestep function
		inline void UpdatePhysics(float msec){
			world->stepSimulation(1 / 90.0f);
		}

		/* Add new physical representation of game object */
		btRigidBody* AddSphere(float radius, float x, float y, float z, float mass);
		btRigidBody* AddPlane(float x, float y, float z, float mass);
		btRigidBody* AddCylinder(float radius, float height, float x, float y, float z, float mass);
		btRigidBody* AddCone(float radius, float height, float x, float y, float z, float mass);
		btRigidBody* AddBox(float width, float height, float depth, float x, float y, float z, float mass);

		//Get physical floor of the world
		btRigidBody* GetWorldPlane() const{
			return physicsObjects[0];
		}

		//Collision callback function (not working)
		bool CollisionFunc(btManifoldPoint &collisionPoint, const btCollisionObject *obj1, int id1, int index1, 
			const btCollisionObject *obj2, int id2, int index2);

	private:
		vector<btRigidBody*> physicsObjects;
		btDynamicsWorld *world;
		btDispatcher *dispatcher;
		btCollisionConfiguration *collisionConfig;
		btBroadphaseInterface *broadphase;
		btConstraintSolver *solver;
};