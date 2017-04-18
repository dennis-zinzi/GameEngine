#include "PhysicsManager.h"

PhysicsManager::PhysicsManager(){
	collisionConfig = new btDefaultCollisionConfiguration();
	dispatcher = new btCollisionDispatcher(collisionConfig);
	broadphase = new btDbvtBroadphase();
	solver = new btSequentialImpulseConstraintSolver();

	world = new btDiscreteDynamicsWorld(dispatcher, broadphase, solver, collisionConfig);
	world->setGravity(btVector3(0.0f, 9.81f, 0.0f));

	//Add world plan (floor)
	btTransform t;
	t.setIdentity();
	t.setOrigin(btVector3(0.0f, 0.0f, 0.0f));

	btStaticPlaneShape *plane = new btStaticPlaneShape(btVector3(0.0f, 1.0f, 0.0f), 0);
	btMotionState *motion = new btDefaultMotionState(t);
	btRigidBody::btRigidBodyConstructionInfo info(0.0f, motion, plane);

	btRigidBody *planeBod = new btRigidBody(info);
	world->addRigidBody(planeBod);
	physicsObjects.push_back(planeBod);
}


PhysicsManager::~PhysicsManager(){
	for(auto body : physicsObjects){
		world->removeCollisionObject(body);
		delete body->getMotionState();
		delete body->getCollisionShape();
		delete body;
	}

	delete solver;
	delete broadphase;
	delete collisionConfig;
	delete dispatcher;
	delete world;
}