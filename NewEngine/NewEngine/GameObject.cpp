#include "GameObject.h"
#include <iostream>

using std::cout;
using std::endl;

GameObject::GameObject(btRigidBody * physicalBody, int red, int green, int blue, int alpha){
	this->physicalBody = physicalBody;

	this->halfWidth = halfWidth;
	this->halfHeight = halfHeight;
	this->halfDepth = halfDepth;

	this->red = red;
	this->green = green;
	this->blue = blue;
	this->alpha = alpha;
}

GameObject::GameObject(btRigidBody * physicalBody, float halfWidth, float halfHeight, float halfDepth,
	int red, int green, int blue, int alpha){

	this->physicalBody = physicalBody;

	this->halfWidth = halfWidth;
	this->halfHeight = halfHeight;
	this->halfDepth = halfDepth;

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


			GraphicsRenderer::RenderPlane(x, y, z, halfWidth, halfHeight, halfDepth, matrix);
			break;
		}

		case SPHERE_SHAPE_PROXYTYPE: {
			GraphicsRenderer::RenderSphere(((btSphereShape*)shape)->getRadius(), matrix,
				red, green, blue, alpha);
			break;
		}

		case CYLINDER_SHAPE_PROXYTYPE: {
			btVector3 extents = ((btCylinderShape*)shape)->getHalfExtentsWithoutMargin();
			GraphicsRenderer::RenderCylinder(extents.x(), extents.y(), matrix,
				red, green, blue, alpha);
			break;
		}
		case CONE_SHAPE_PROXYTYPE: {
			GraphicsRenderer::RenderCone(((btConeShape*)shape)->getRadius(), ((btConeShape*)shape)->getHeight(),
				matrix, red, green, blue, alpha);
			break;
		}
		case BOX_SHAPE_PROXYTYPE: { 
			float x = physicalBody->getCenterOfMassPosition().x(),
				y = physicalBody->getCenterOfMassPosition().y(),
				z = physicalBody->getCenterOfMassPosition().z();


			GraphicsRenderer::RenderBox(x, y, z, halfWidth, halfHeight, halfDepth, matrix,
				red, green, blue, alpha);
			break;
		}

	}
}
