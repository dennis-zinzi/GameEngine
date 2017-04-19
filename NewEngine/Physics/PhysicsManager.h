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

		btRigidBody* AddSphere(float radius, float x, float y, float z, float mass);
		btRigidBody* AddPlane(float x, float y, float z, float mass);
		btRigidBody* AddCylinder(float radius, float height, float x, float y, float z, float mass);
		btRigidBody* AddCone(float radius, float height, float x, float y, float z, float mass);
		btRigidBody* AddBox(float halfWidth, float halfHeight, float halfDepth, float x, float y, float z, float mass);


		btRigidBody* GetWorldPlane() const{
			return physicsObjects[0];
		}

	private:
		vector<btRigidBody*> physicsObjects;
		btDynamicsWorld *world;
		btDispatcher *dispatcher;
		btCollisionConfiguration *collisionConfig;
		btBroadphaseInterface *broadphase;
		btConstraintSolver *solver;
};