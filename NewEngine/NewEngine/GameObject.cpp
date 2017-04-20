#include "GameObject.h"
#include <iostream>

using std::cout;
using std::endl;

GameObject::GameObject(btRigidBody * physicalBody, int red, int green, int blue, int alpha){
	this->physicalBody = physicalBody;

	this->red = red;
	this->green = green;
	this->blue = blue;
	this->alpha = alpha;
}

GameObject::GameObject(btRigidBody * physicalBody, float width, float height, float depth,
	int red, int green, int blue, int alpha){

	this->physicalBody = physicalBody;

	this->width = width;
	this->height = height;
	this->depth = depth;

	this->red = red;
	this->green = green;
	this->blue = blue;
	this->alpha = alpha;
}

void GameObject::RenderObject(){
	//Get physical properties
	btCollisionShape *shape = physicalBody->getCollisionShape();

	//Get model matrix
	btTransform t;
	physicalBody->getMotionState()->getWorldTransform(t);
	float matrix[16];
	t.getOpenGLMatrix(matrix);

	switch(shape->getShapeType()){
		case STATIC_PLANE_PROXYTYPE: {
			float x = physicalBody->getCenterOfMassPosition().x(),
				y = physicalBody->getCenterOfMassPosition().y(),
				z = physicalBody->getCenterOfMassPosition().z();


			GraphicsRenderer::RenderPlane(x, y, z, width, height, depth, matrix);
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
