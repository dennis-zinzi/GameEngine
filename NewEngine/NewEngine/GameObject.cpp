#include "GameObject.h"
#include <iostream>

using std::cout;
using std::endl;

int GameObject::ID = 0;

//NOT CURRENTLY USED
GameObject::GameObject(GraphicsRenderer &renderer, PhysicsManager &physics, int red, int green, int blue, int alpha){
	this->red = red;
	this->green = green;
	this->blue = blue;
	this->alpha = alpha;

	renderer.AddRenderObject(this);

	SetID(GetObjID());
	SetBody(physicalObj);

	physics.addPhysicsObj(this);
}


GameObject::GameObject(GraphicsRenderer &renderer, PhysicsManager &physics, btRigidBody *body, float width, float height, float depth,
	int red, int green, int blue, int alpha){

	this->physicalObj = body;

	this->width = width;
	this->height = height;
	this->depth = depth;

	this->red = red;
	this->green = green;
	this->blue = blue;
	this->alpha = alpha;

	renderer.AddRenderObject(this);

	SetID(GetObjID());
	SetBody(this->physicalObj);

	physics.addPhysicsObj(this);
}


GameObject::GameObject(GraphicsRenderer &renderer, Type type, int red, int green, int blue, int alpha){

	objType = type;
	this->red = red;
	this->green = green;
	this->blue = blue;
	this->alpha = alpha;

	renderer.AddRenderObject(this);
}


GameObject::GameObject(GraphicsRenderer &renderer, PhysicsManager &physics, Shape shape, Type type, float x, float y, float z, float mass, float radius, float height,
	int red, int green, int blue, int alpha) : GameObject(renderer, type, red, green, blue, alpha){
	
	switch(shape){
		case Plane:
			physicalObj = physics.AddPlane(x, y, z, mass);
			break;
		case Sphere:
			physicalObj = physics.AddSphere(radius, x, y, z, mass);
			break;
		case Cylinder:
			physicalObj = physics.AddCylinder(radius, height, x, y, z, mass);
			break;
		case Cone:
			physicalObj = physics.AddCone(radius, height, x, y, z, mass);
			break;
	}
	
	this->radius = radius;
	this->height = height;

	SetID(GetObjID());
	SetBody(physicalObj);

	physics.addPhysicsObj(this);
}


GameObject::GameObject(GraphicsRenderer &renderer, PhysicsManager &physics, Shape shape, Type type, float x, float y, float z, float mass, float width, float height, float depth,
	int red, int green, int blue, int alpha) : GameObject(renderer, type, red, green, blue, alpha){
	
	switch(shape){
		case Plane:
			physicalObj = physics.AddPlane(x, y, z, mass);
			break;
		case Box:
			physicalObj = physics.AddBox(width, height, depth, x, y, z, mass);
			break;
	}

	this->width = width;
	this->height = height;
	this->depth = depth;

	SetID(GetObjID());
	SetBody(physicalObj);

	physics.addPhysicsObj(this);
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
	}

	if(objType == Type::Target && ((GameObject*)Other)->objType == Type::Bullet){
		cout << "Target HIT bullet" << endl;
	}
}
