#include "PhysicsManager.h"

PhysicsManager::PhysicsManager(){
	collisionConfig = new btDefaultCollisionConfiguration();
	dispatcher = new btCollisionDispatcher(collisionConfig);
	broadphase = new btDbvtBroadphase();
	solver = new btSequentialImpulseConstraintSolver();

	world = new btDiscreteDynamicsWorld(dispatcher, broadphase, solver, collisionConfig);
	world->setGravity(btVector3(0.0f, -9.81f, 0.0f));

	//Add world plane (floor)
	wFloor = AddPlane(0.0f, -2.0f, -10.0f, 0.0f);

	//Set collision callback function (not working)
	//gContactAddedCallback = CollisionFunc;
}


PhysicsManager::~PhysicsManager(){
	for(auto body : physicsObjects){
		world->removeCollisionObject(body->GetBody());
		delete body->GetBody()->getMotionState();
		delete body->GetBody()->getCollisionShape();
		delete body->GetBody();
	}

	delete solver;
	delete broadphase;
	delete collisionConfig;
	delete dispatcher;
	delete world;
}

/**
 * Add new Sphere physics object to world
 */
btRigidBody* PhysicsManager::AddSphere(float radius, float x, float y, float z, float mass){
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
	
	return body;
}


/**
* Add new Infinite plane physics object to world
*/
btRigidBody* PhysicsManager::AddPlane(float x, float y, float z, float mass)
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

	return planeBod;
}


/**
* Add new Cylinder physics object to world
*/
btRigidBody* PhysicsManager::AddCylinder(float radius, float height, float x, float y, float z, float mass){
	btTransform t;
	t.setIdentity();
	t.setOrigin(btVector3(x, y, z));

	btCylinderShape *cylinder = new btCylinderShape(btVector3(radius, height / 2.0f, radius));

	btVector3 inertia;
	if(mass > 0.0f){
		cylinder->calculateLocalInertia(mass, inertia);
	}
	btMotionState *motion = new btDefaultMotionState(t);
	btRigidBody::btRigidBodyConstructionInfo info(mass, motion, cylinder, inertia);

	btRigidBody *cylinderBod = new btRigidBody(info);
	world->addRigidBody(cylinderBod);
	
	return cylinderBod;
}


/**
* Add new Cone physics object to world
*/
btRigidBody* PhysicsManager::AddCone(float radius, float height, float x, float y, float z, float mass){
	btTransform t;
	t.setIdentity();
	t.setOrigin(btVector3(x, y, z));

	btConeShape *cone = new btConeShape(radius*2, height);

	btVector3 inertia;
	if(mass > 0.0f){
		cone->calculateLocalInertia(mass, inertia);
	}
	btMotionState *motion = new btDefaultMotionState(t);
	btRigidBody::btRigidBodyConstructionInfo info(mass, motion, cone, inertia);

	btRigidBody *coneBod = new btRigidBody(info);
	world->addRigidBody(coneBod);

	return coneBod;;
}


/**
* Add new Box physics object to world
*/
btRigidBody* PhysicsManager::AddBox(float width, float height, float depth, float x, float y, float z, float mass){
	btTransform t;
	t.setIdentity();
	t.setOrigin(btVector3(x, y, z));

	btBoxShape *box = new btBoxShape(btVector3(width / 2.0f, height / 2.0f, depth / 2.0f));

	btVector3 inertia;
	if(mass > 0.0f){
		box->calculateLocalInertia(mass, inertia);
	}
	btMotionState *motion = new btDefaultMotionState(t);
	btRigidBody::btRigidBodyConstructionInfo info(mass, motion, box, inertia);

	btRigidBody *boxBod = new btRigidBody(info);
	world->addRigidBody(boxBod);

	return boxBod;
}

//Collision callback function
bool PhysicsManager::CollisionFunc(btManifoldPoint &collisionPoint, const btCollisionObject *obj1, int id1, int index1,
	const btCollisionObject *obj2, int id2, int index2){
	printf("Collision happened\n");

	return false;
}
