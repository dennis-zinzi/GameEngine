#include "Player.h"

Player::Player(GraphicsRenderer &renderer, Camera * camera, btRigidBody * physicalBody, float width, float height, float depth, int red, int green, int blue, int alpha)
: GameObject(renderer, physicalBody, width, height, depth, red, green, blue, alpha){
	this->camera = camera;
	this->renderer = &renderer;
}

Player::Player(GraphicsRenderer &renderer, PhysicsManager &physics, float radius, float mass,
	int red, int green, int blue, int alpha)
	: GameObject(renderer, physics, Shape::Sphere, renderer.GetCamera()->GetCameraPos()[0], renderer.GetCamera()->GetCameraPos()[1], renderer.GetCamera()->GetCameraPos()[2], mass, radius, 0.0f, red, green, blue, alpha){
	
	camera = renderer.GetCamera();
	this->renderer = &renderer;
	this->physics = &physics;
}

void Player::MovePhysicObj(){
	physicalBody->setLinearVelocity(btVector3(camera->GetCameraPos()[0] * 0.95f, camera->GetCameraPos()[1] * 0.95f, camera->GetCameraPos()[2] * 0.95f));
}


Player::Player(GraphicsRenderer &renderer, PhysicsManager &physics, float width, float height, float depth, float mass,
	int red, int green, int blue, int alpha)
	: GameObject(renderer, physics, Shape::Box, renderer.GetCamera()->GetCameraPos()[0], renderer.GetCamera()->GetCameraPos()[1], renderer.GetCamera()->GetCameraPos()[2], mass, width, height, depth,
		red, green, blue, alpha){

	camera = renderer.GetCamera();
	this->renderer = &renderer;
	this->physics = &physics;
}


void Player::Render(){

	btTransform t;
	physicalBody->getMotionState()->getWorldTransform(t);
	//t.setOrigin(btVector3(camera->GetCameraPos()[0] - 0.0f, physicalBody->getCenterOfMassPosition().y(), camera->GetCameraPos()[2] - 0.0f));

	//physicalBody->setWorldTransform(t);
	//physicalBody->getMotionState()->setWorldTransform(t);

	//cout << "Camera X: " << camera->GetCameraPos()[0] << ", Camera Y: " << camera->GetCameraPos()[1] << ", Camera Z: " << camera->GetCameraPos()[2] << endl;
	//cout << "X: " << physicalBody->getCenterOfMassPosition().x() << ", Y: " << physicalBody->getCenterOfMassPosition().y() << ", Z: " << physicalBody->getCenterOfMassPosition().z() << endl;
	//physicalBody->setLinearVelocity(btVector3(camera->GetCameraPos()[0] - 0.0f, camera->GetCameraPos()[1] - 1.0f, camera->GetCameraPos()[2] - 5.0f));
	/*physicalBody->setLinearVelocity(btVector3(physicalBody->getLinearVelocity().x(), physicalBody->getLinearVelocity().y(), camera->GetCameraPos()[2]));*/

	float matrix[16];
	t.getOpenGLMatrix(matrix);
	
	
	GraphicsRenderer::RenderSphere(radius, matrix, red, green, blue, alpha);

	//btVector3 extents = ((btBoxShape*)physicalBody->getCollisionShape())->getHalfExtentsWithoutMargin();
	//GraphicsRenderer::RenderBox(extents.x(), extents.y(), extents.z(), matrix,
	//	red, green, blue, alpha);
}


void Player::MoveLeft(){
	camera->MoveCameraXZ(MOVE_VEL, 90.0f);
	MovePhysicObj();
}


void Player::MoveForward(){
	camera->MoveCameraXZ(MOVE_VEL, 0.0f);
	MovePhysicObj();
}


void Player::MoveRight(){
	camera->MoveCameraXZ(MOVE_VEL, 270.0f);
	MovePhysicObj();
}


void Player::MoveBackward(){
	camera->MoveCameraXZ(MOVE_VEL, 180.0f);
	MovePhysicObj();
}


void Player::Jump(){

}


void Player::Shoot(){
	RenderObject *bullet = new GameObject(*renderer, *physics, Shape::Sphere, camera->GetCameraPos()[0], camera->GetCameraPos()[1], camera->GetCameraPos()[2], 0.2f, 0.1f, 0.0f, 255, 255, 255);

	float *camLook = camera->GetCameraLookVect();
	((GameObject*)bullet)->GetPhysicalObj()->setLinearVelocity(btVector3(camLook[0] * 30, camLook[1] * 30, camLook[2] * 30));
}


void Player::NoMovement(){
	physicalBody->setLinearVelocity(btVector3(0, 0, 0));
}