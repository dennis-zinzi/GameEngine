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

void GameObject::RenderObject(){
	btCollisionShape *shape = physicalBody->getCollisionShape();

	switch(shape->getShapeType()){
		case STATIC_PLANE_PROXYTYPE: {
			btTransform t;
			physicalBody->getMotionState()->getWorldTransform(t);
			float matrix[16];
			t.getOpenGLMatrix(matrix);


			GraphicsRenderer::RenderPlane(1000, 0, 1000, matrix);
		}
		break;

		case SPHERE_SHAPE_PROXYTYPE: {
			btTransform t;
			physicalBody->getMotionState()->getWorldTransform(t);
			float matrix[16];
			t.getOpenGLMatrix(matrix);

			GraphicsRenderer::RenderSphere(((btSphereShape*)shape)->getRadius(), matrix,
				red, green, blue, alpha);

			cout << "Sphere drawing" << endl;

			break;
		}
	}
}
