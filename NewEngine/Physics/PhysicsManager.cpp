#include "PhysicsManager.h"

PhysicsManager::PhysicsManager(){
	collisionConfig = new btDefaultCollisionConfiguration();
	dispatcher = new btCollisionDispatcher(collisionConfig);
	broadphase = new btDbvtBroadphase();
	solver = new btSequentialImpulseConstraintSolver();

	world = new btDiscreteDynamicsWorld(dispatcher, broadphase, solver, collisionConfig);
	world->setGravity(btVector3(0.0f, -9.81f, 0.0f));

	//Add world plane (floor)
	AddPlane(0.0f, -2.0f, -10.0f, 0.0f);
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

btRigidBody* PhysicsManager::AddSphereObj(float radius, float x, float y, float z, float mass){
	btTransform t;
	t.setIdentity();
	t.setOrigin(btVector3(x, y, z));

	btSphereShape *sphere = new btSphereShape(radius);
	btVector3 inertia;
	if(mass > 0.0f){
		sphere->calculateLocalInertia(mass, inertia);
	}

	btMotionState *motion = new btDefaultMotionState(t);
	btRigidBody::btRigidBodyConstructionInfo info(mass, motion, sphere, inertia);
	btRigidBody *body = new btRigidBody(info);

	world->addRigidBody(body);
	physicsObjects.push_back(body);
	
	return body;
}

btRigidBody * PhysicsManager::AddPlane(float x, float y, float z, float mass)
{
	btTransform t;
	t.setIdentity();
	t.setOrigin(btVector3(x, y, z));

	btStaticPlaneShape *plane = new btStaticPlaneShape(btVector3(0.0f, 1.0f, 0.0f), 0);
	btVector3 inertia;
	if(mass > 0.0f){
		plane->calculateLocalInertia(mass, inertia);
	}
	btMotionState *motion = new btDefaultMotionState(t);
	btRigidBody::btRigidBodyConstructionInfo info(mass, motion, plane, inertia);

	btRigidBody *planeBod = new btRigidBody(info);
	world->addRigidBody(planeBod);
	physicsObjects.push_back(planeBod);

	return planeBod;
}
