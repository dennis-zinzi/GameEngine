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

			/*int numManifolds = world->getDispatcher()->getNumManifolds();
			for(int i = 0; i<numManifolds; i++){
				btPersistentManifold* contactManifold = world->getDispatcher()->getManifoldByIndexInternal(i);
				btCollisionObject* obA = (btCollisionObject*)(contactManifold->getBody0());
				btCollisionObject* obB = (btCollisionObject*)(contactManifold->getBody1());

				if(obA->getCollisionShape()->getShapeType() == STATIC_PLANE_PROXYTYPE
					|| obB->getCollisionShape()->getShapeType() == STATIC_PLANE_PROXYTYPE){
					continue;
				}

				int numContacts = contactManifold->getNumContacts();
				for(int j = 0; j<numContacts; j++){
					btManifoldPoint& pt = contactManifold->getContactPoint(j);
					if(pt.getDistance()<0.f){
						const btVector3& ptA = pt.getPositionWorldOnA();
						const btVector3& ptB = pt.getPositionWorldOnB();
						const btVector3& normalOnB = pt.m_normalWorldOnB;
						printf("ouch \n");
					}
				}
			}*/
		}

		btRigidBody* AddSphere(float radius, float x, float y, float z, float mass);
		btRigidBody* AddPlane(float x, float y, float z, float mass);
		btRigidBody* AddCylinder(float radius, float height, float x, float y, float z, float mass);
		btRigidBody* AddCone(float radius, float height, float x, float y, float z, float mass);
		btRigidBody* AddBox(float width, float height, float depth, float x, float y, float z, float mass);


		btRigidBody* GetWorldPlane() const{
			return physicsObjects[0];
		}

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