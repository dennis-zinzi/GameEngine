/**
 * Helpful reference https://github.com/lokesh-sharma/GameEngine
 */
#pragma once

#include "BulletCollision\CollisionDispatch\btGhostObject.h"
#include "BulletDynamics\Character\btKinematicCharacterController.h"
#include <btBulletCollisionCommon.h>

class PhysicsPlayer{
	public:
		PhysicsPlayer();

		inline void SetGravity(const btVector3 &gravity){
			charController->setGravity(gravity);
		}

		inline btPairCachingGhostObject* GetGhostObj(){
			return ghostObj;
		}
		inline btKinematicCharacterController* GetCharController(){
			return charController;
		}

		virtual void Tick() = 0;

	protected:
		btPairCachingGhostObject *ghostObj;
		btKinematicCharacterController *charController;
};