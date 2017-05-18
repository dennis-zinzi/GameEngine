#include "GameObject.h"
#include <iostream>

using std::cout;
using std::endl;

int GameObject::ID = 0;

//NOT CURRENTLY USED
GameObject::GameObject(GraphicsRenderer *renderer, PhysicsManager *physics, AudioPlayer *audio, int red, int green, int blue, int alpha){
	this->red = red;
	this->green = green;
	this->blue = blue;
	this->alpha = alpha;

	renderer->AddRenderObject(this);
}


GameObject::GameObject(GraphicsRenderer *renderer, PhysicsManager *physics, AudioPlayer *audio, btRigidBody *body, float width, float height, float depth,
	int red, int green, int blue, int alpha){

	this->width = width;
	this->height = height;
	this->depth = depth;

	this->red = red;
	this->green = green;
	this->blue = blue;
	this->alpha = alpha;

	renderer->AddRenderObject(this);

	SetID(GetObjID());
	SetBody(body);

	physics->addPhysicsObj(this);
}


GameObject::GameObject(GraphicsRenderer *renderer, PhysicsManager *physics, AudioPlayer *audio, Type type, int red, int green, int blue, int alpha){

	objType = type;
	this->red = red;
	this->green = green;
	this->blue = blue;
	this->alpha = alpha;

	this->audio = audio;
	this->physics = physics;
	this->renderer = renderer;

	renderer->AddRenderObject(this);


	SetID(GetObjID());
}


GameObject::GameObject(GraphicsRenderer *renderer, PhysicsManager *physics, AudioPlayer *audio, Shape shape, Type type, float x, float y, float z, float mass, float radius, float height,
	int red, int green, int blue, int alpha) : GameObject(renderer, physics, audio, type, red, green, blue, alpha){
	
	switch(shape){
		case Plane:
			SetBody(physics->AddPlane(x, y, z, mass));
			break;
		case Sphere:
			SetBody(physics->AddSphere(radius, x, y, z, mass));
			break;
		case Cylinder:
			SetBody(physics->AddCylinder(radius, height, x, y, z, mass));
			break;
		case Cone:
			SetBody(physics->AddCone(radius, height, x, y, z, mass));
			break;
	}
	
	this->radius = radius;
	this->height = height;

	physics->addPhysicsObj(this);
}


GameObject::GameObject(GraphicsRenderer *renderer, PhysicsManager *physics, AudioPlayer *audio, Shape shape, Type type, float x, float y, float z, float mass, float width, float height, float depth,
	int red, int green, int blue, int alpha) : GameObject(renderer, physics, audio, type, red, green, blue, alpha){
	
	switch(shape){
		case Plane:
			SetBody(physics->AddPlane(x, y, z, mass));
			break;
		case Box:
			SetBody(physics->AddBox(width, height, depth, x, y, z, mass));
			break;
	}

	this->width = width;
	this->height = height;
	this->depth = depth;

	physics->addPhysicsObj(this);
}

void GameObject::Render(){
	//Get physical properties
	btRigidBody *bod = GetBody();
	btCollisionShape *shape = bod->getCollisionShape();

	//Get model matrix
	btTransform t;
	bod->getMotionState()->getWorldTransform(t);
	float matrix[16];
	t.getOpenGLMatrix(matrix);

	switch(shape->getShapeType()){
		case STATIC_PLANE_PROXYTYPE: {
			float x = bod->getCenterOfMassPosition().x(),
				y = bod->getCenterOfMassPosition().y(),
				z = bod->getCenterOfMassPosition().z();


			GraphicsRenderer::RenderPlane(x, y, z, width, height, depth, matrix,
				red, green, blue, alpha);
			break;
		}

		case SPHERE_SHAPE_PROXYTYPE: {
			GraphicsRenderer::RenderSphere(((btSphereShape*)shape)->getRadius(), matrix,
				red, green, blue, alpha);
			break;
		}

		case CYLINDER_SHAPE_PROXYTYPE: {
			btVector3 extents = ((btCylinderShape*)shape)->getHalfExtentsWithoutMargin();
			GraphicsRenderer::RenderCylinder(extents.x(), extents.y()*2.0f, matrix,
				red, green, blue, alpha);
			break;
		}
		case CONE_SHAPE_PROXYTYPE: {
			GraphicsRenderer::RenderCone(((btConeShape*)shape)->getRadius(), ((btConeShape*)shape)->getHeight(),
				matrix, red, green, blue, alpha);
			break;
		}
		case BOX_SHAPE_PROXYTYPE: { 
			btVector3 extents = ((btBoxShape*)shape)->getHalfExtentsWithoutMargin();
			
			GraphicsRenderer::RenderBox(extents.x(), extents.y(), extents.z(), matrix,
				red, green, blue, alpha);
			break;
		}

	}
}

void GameObject::HandleHit(PhysicsObject *Other){
	if(objType == Type::Bullet && ((GameObject*)Other)->objType == Type::Target){
		cout << "BULLET HIT Target" << endl;
		audio->PlayEffect("mario_coin.wav");
		GameLevel::UpdateScore(15);
		cout << "Score: " << GameLevel::GetScore() << endl;

		renderer->RemoveRenderObj(this);
		physics->RemovePhysicsObj(this);
	}

	//if(objType == Type::Target && ((GameObject*)Other)->objType == Type::Bullet){
	//	cout << "Target HIT bullet" << endl;
	//}
}
