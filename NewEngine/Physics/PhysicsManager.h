#pragma once

#include <vector>
#include <btBulletCollisionCommon.h>
#include <btBulletDynamicsCommon.h>

using std::vector;

class PhysicsManager{
	public:
		PhysicsManager();
		~PhysicsManager();

		inline void UpdatePhysics(float msec){
			world->stepSimulation(1 / 120.0f);
		}

	private:
		vector<btRigidBody*> physicsObjects;
		btDynamicsWorld *world;
		btDispatcher *dispatcher;
		btCollisionConfiguration *collisionConfig;
		btBroadphaseInterface *broadphase;
		btConstraintSolver *solver;
};