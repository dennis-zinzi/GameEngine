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
			world->performDiscreteCollisionDetection();

			int numManifolds = world->getDispatcher()->getNumManifolds();
			//For each contact manifold
			for(int i = 0; i < numManifolds; i++){
				btPersistentManifold* contactManifold = world->getDispatcher()->getManifoldByIndexInternal(i);
				btCollisionObject *obA = const_cast<btCollisionObject*>(contactManifold->getBody0());
				btCollisionObject *obB = const_cast<btCollisionObject*>(contactManifold->getBody1());

				if (obA->getCollisionShape()->getShapeType() == STATIC_PLANE_PROXYTYPE
					|| obB->getCollisionShape()->getShapeType() == STATIC_PLANE_PROXYTYPE){
					continue;
				}
				
				contactManifold->refreshContactPoints(obA->getWorldTransform(), obB->getWorldTransform());
				int numContacts = contactManifold->getNumContacts();
				printf("Contacts: %i\n", numContacts);
				//For each contact point in that manifold
				for(int j = 0; j < numContacts; j++){
					//Get the contact information
					btManifoldPoint &pt = contactManifold->getContactPoint(j);
					btVector3 ptA = pt.getPositionWorldOnA();
					btVector3 ptB = pt.getPositionWorldOnB();
					float ptdist = pt.getDistance();
				}
			}
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