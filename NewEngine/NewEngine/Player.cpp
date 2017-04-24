#include "Player.h"

Player::Player(GraphicsRenderer &renderer, Camera * camera, btRigidBody * physicalBody, float width, float height, float depth, int red, int green, int blue, int alpha)
: GameObject(renderer, physicalBody, width, height, depth, red, green, blue, alpha){
	this->camera = camera;
}

Player::Player(GraphicsRenderer &renderer, PhysicsManager &physics, float radius, float mass,
	int red, int green, int blue, int alpha)
	: GameObject(renderer, physics, Shape::Sphere, renderer.GetCamera()->GetCameraPos()[0], renderer.GetCamera()->GetCameraPos()[1], renderer.GetCamera()->GetCameraPos()[2], mass, radius, 0.0f, red, green, blue, alpha){
	
	camera = renderer.GetCamera();
}

void Player::Render(){

	btTransform t;
	physicalBody->getMotionState()->getWorldTransform(t);
	//t.setOrigin(btVector3(camera->GetCameraPos()[0] - 0.0f, physicalBody->getCenterOfMassPosition().y(), camera->GetCameraPos()[2] - 5.0f));

	//physicalBody->setWorldTransform(t);
	//physicalBody->getMotionState()->setWorldTransform(t);

	//cout << "Camera X: " << camera->GetCameraPos()[0] << ", Camera Y: " << camera->GetCameraPos()[1] << ", Camera Z: " << camera->GetCameraPos()[2] << endl;
	//cout << "X: " << physicalBody->getCenterOfMassPosition().x() << ", Y: " << physicalBody->getCenterOfMassPosition().y() << ", Z: " << physicalBody->getCenterOfMassPosition().z() << endl;
	//physicalBody->setLinearVelocity(btVector3(camera->GetCameraPos()[0] - 0.0f, camera->GetCameraPos()[1] - 1.0f, camera->GetCameraPos()[2] - 5.0f));
	physicalBody->setLinearVelocity(btVector3(physicalBody->getLinearVelocity().x(), physicalBody->getLinearVelocity().y(), camera->GetCameraPos()[2] * 0.7f));

	float matrix[16];
	t.getOpenGLMatrix(matrix);
	
	
	GraphicsRenderer::RenderSphere(radius, matrix, red, green, blue, alpha);
}
