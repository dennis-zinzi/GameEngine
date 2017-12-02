#include "PhysicsPlayer.h"

PhysicsPlayer::PhysicsPlayer(){
	btTransform start;
	start.setIdentity();
	start.setOrigin(btVector3(0.0f, 0.0f, 0.0f));

	btConvexShape *capsule = new btCapsuleShape(1.3f, 6.3f);
	ghostObj = new btPairCachingGhostObject();
	ghostObj->setWorldTransform(start);
	ghostObj->setCollisionShape(capsule);
	ghostObj->setCollisionFlags(btCollisionObject::CF_CHARACTER_OBJECT);
	charController = new btKinematicCharacterController(ghostObj, capsule, 0.05f);
	charController->setMaxJumpHeight(10.0f);
}
