#pragma once
#include <btBulletCollisionCommon.h>
#include <btBulletDynamicsCommon.h>


class PhysicsObject{
	public:
		PhysicsObject(){};
		PhysicsObject(int ID, btRigidBody *body){
			this->ID = ID;
			this->body = body;
			isHit = false;
		}

		inline int GetID() const{
			return ID;
		}
		inline void SetID(int ID){
			this->ID = ID;
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
		inline void SetBody(btRigidBody *body){
			this->body = body;
		}

		virtual void HandleHit(PhysicsObject *Other) = 0;

	private:
		int ID;
		bool isHit;
		btRigidBody *body;

};