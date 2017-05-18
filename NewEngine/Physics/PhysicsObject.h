#pragma once
#include <btBulletCollisionCommon.h>
#include <btBulletDynamicsCommon.h>


class PhysicsObject{
	public:
		PhysicsObject(int ID, btRigidBody *body){
			this->ID = ID;
			this->body = body;
			isHit = false;
		}

		inline int GetID() const{
			return ID;
		}
		

		inline bool GetIsHit() const{
			return isHit;
		}
		inline void SetIsHit(bool isHit){
			this->isHit = isHit;
		}


		inline btRigidBody* GetBody() const{
			return body;
		}

	private:
		int ID;
		bool isHit;
		btRigidBody *body;

};