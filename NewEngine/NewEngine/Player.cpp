#include "Player.h"

Player::Player(GraphicsRenderer *renderer, PhysicsManager *physics, AudioPlayer *player, float radius, float mass,
	int red, int green, int blue, int alpha)
	: GameObject(renderer, physics, player, Shape::Sphere, Type::PLAYER, renderer->GetCamera()->GetCameraPos()[0], renderer->GetCamera()->GetCameraPos()[1], renderer->GetCamera()->GetCameraPos()[2] - 5.0f, mass, radius, 0.0f, red, green, blue, alpha){

	camera = renderer->GetCamera();
	this->renderer = renderer;
	this->physics = physics;
	this->player = player;

	jumpNum = 0;
	isJumping = false;
	isFalling = false;

	show = false;
}


Player::Player(GraphicsRenderer *renderer, PhysicsManager *physics, AudioPlayer *player, float width, float height, float depth, float mass,
	int red, int green, int blue, int alpha)
	: GameObject(renderer, physics, player, Shape::Box, Type::PLAYER, renderer->GetCamera()->GetCameraPos()[0], renderer->GetCamera()->GetCameraPos()[1], renderer->GetCamera()->GetCameraPos()[2] - 5.0f, mass, width, height, depth,
		red, green, blue, alpha){

	camera = renderer->GetCamera();
	this->renderer = renderer;
	this->physics = physics;
	this->player = player;

	jumpNum = 0;
	isJumping = false;
	isFalling = false;

	show = false;
}


void Player::Render(){
	if(isJumping){
		camera->MoveCameraY(JUMP_VEL, 90);
		//camera->MoveCameraXZ(0.1, 0.0f);

		if(jumpNum > 10){
			isJumping = false;
			isFalling = true;
			jumpNum = 0;
		}


		jumpNum++;
		SDL_Delay(10);
	}
	
	if(isFalling){
		camera->MoveCameraY(JUMP_VEL, -90.0f);
		//camera->MoveCameraXZ(0.1, 0.0f);

		if(jumpNum > 10){
			isFalling = false;
			jumpNum = 0;
		}

		if(camera->GetCameraPos()[1] < 0.0){
			isFalling = false;
		}

		jumpNum++;
		SDL_Delay(10);
	}


	//btTransform t;
	////physicalBody->getMotionState()->getWorldTransform(t);
	//t = GetBody()->getWorldTransform();

	//float matrix[16];
	//t.getOpenGLMatrix(matrix);
	
	
	//GraphicsRenderer::RenderSphere(radius, matrix, red, green, blue, alpha);

	//btVector3 extents = ((btBoxShape*)physicalBody->getCollisionShape())->getHalfExtentsWithoutMargin();
	//GraphicsRenderer::RenderBox(extents.x(), extents.y(), extents.z(), matrix,
	//	red, green, blue, alpha);
}


void Player::MovePhysicObj(float x1, float x2, float y1, float y2, float z1, float z2){
	//cout << "p= X1: " << physicalBody->getCenterOfMassPosition().x() << ", Y1: " << physicalBody->getCenterOfMassPosition().y()
	//		<< ", Z1: " << physicalBody->getCenterOfMassPosition().z() << endl;

	//cout << x2 << "," << x1 << endl;
	//cout << x2 << "," << x1 << endl;
	btVector3 moved(x2 - x1, y2 - y1, z2 - z1);
	//btVector3 look = btVector3(camera->GetCameraLookVect()[0] + 0.0f, camera->GetCameraLookVect()[1] + 0.0f, camera->GetCameraLookVect()[2] + 0.0f);

	float dist = sqrt((moved.x()*moved.x()) + (moved.y()*moved.y()) + (moved.z()*moved.z()));

	btVector3 vel(moved.x() * MOVE_VEL / dist, moved.y() * MOVE_VEL / dist, moved.z() * MOVE_VEL / dist);

	GetBody()->setLinearVelocity(vel);
}


void Player::MoveLeft(){
	float x1 = camera->GetCameraPos()[0],
		z1 = camera->GetCameraPos()[2];

	camera->MoveCameraXZ(MOVE_VEL, 90.0f);

	float x2 = camera->GetCameraPos()[0],
		z2 = camera->GetCameraPos()[2];

	MovePhysicObj(x1, x2, 0, 0, z1, z2);
	//physicalBody->translate(btVector3(x2 - x1, 0, z2 - z1));
}


void Player::MoveForward(){
	float x1 = camera->GetCameraPos()[0],
		z1 = camera->GetCameraPos()[2];

	camera->MoveCameraXZ(MOVE_VEL, 0.0f);

	float x2 = camera->GetCameraPos()[0],
		z2 = camera->GetCameraPos()[2];

	//MovePhysicObj();
	MovePhysicObj(x1, x2, 0, 0, z1, z2);
	//physicalBody->translate(btVector3(x2 - x1, 0, z2 - z1));
}


void Player::MoveRight(){
	float x1 = camera->GetCameraPos()[0],
		z1 = camera->GetCameraPos()[2];

	camera->MoveCameraXZ(MOVE_VEL, 270.0f);

	float x2 = camera->GetCameraPos()[0],
		z2 = camera->GetCameraPos()[2];

	//MovePhysicObj();
	//physicalBody->translate(btVector3(x2 - x1, 0, z2 - z1));
	MovePhysicObj(x1, x2, 0, 0, z1, z2);
}


void Player::MoveBackward(){
	float x1 = camera->GetCameraPos()[0],
		z1 = camera->GetCameraPos()[2];

	camera->MoveCameraXZ(MOVE_VEL, 180.0f);
	
	float x2 = camera->GetCameraPos()[0],
		z2 = camera->GetCameraPos()[2];

	//MovePhysicObj();
	//physicalBody->translate(btVector3(x2 - x1, 0, z2 - z1));
	MovePhysicObj(x1, x2, 0, 0, z1, z2);
}


void Player::Jump(){

	if(!isJumping && !isFalling){
		isJumping = true;
	}

}


void Player::Shoot(){
	RenderObject *bullet = new GameObject(renderer, physics, player, Shape::Sphere, Type::Bullet, camera->GetCameraPos()[0], camera->GetCameraPos()[1], camera->GetCameraPos()[2], 0.2f, 0.05f, 0.0f, 255, 255, 255);

	float *camLook = camera->GetCameraLookVect();
	((GameObject*)bullet)->GetBody()->setLinearVelocity(btVector3(camLook[0] * 50, camLook[1] * 50, camLook[2] * 50));

	player->PlayEffect("throw_sound.wav");
}


void Player::ShowControls(bool show){
	if(this->show != show){
		if(show){
			GameLevel::SetStartPause(SDL_GetTicks() / 1000);
		}
		else{
			GameLevel::SetEndPause(SDL_GetTicks() / 1000);
		}

		this->show = show;
	}

	renderer->ShowControlsScreen();
}


void Player::NoMovement(){
	//cout << "NO MOVE" << endl;
	GetBody()->setLinearVelocity(btVector3(0, 0, 0));
}