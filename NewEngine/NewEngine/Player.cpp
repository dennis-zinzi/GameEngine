#include "Player.h"

Player::Player(GraphicsRenderer *renderer, PhysicsManager *physics, AudioPlayer *player, float radius, float mass,
	int red, int green, int blue, int alpha)
	: PhysicsPlayer(){

	camera = renderer->GetCamera();

	this->renderer = renderer;
	this->physics = physics;
	this->audio = player;

	physics->AddPhysicsPlayer(this);
}



Player::Player(GraphicsRenderer *renderer, PhysicsManager *physics, AudioPlayer *player, float width, float height, float depth, float mass,
	int red, int green, int blue, int alpha)
	: PhysicsPlayer(){

	camera = renderer->GetCamera();

	this->renderer = renderer;
	this->physics = physics;
	this->audio = player;

	physics->AddPhysicsPlayer(this);
}


//void Player::Render(){
void Player::Tick(){
	btVector3 pos = charController->getGhostObject()->getWorldTransform().getOrigin();
	camera->SetCameraLoc(pos.x(), pos.y() + 1.0f, pos.z());
}


void Player::MovePhysicObj(float x1, float x2, float y1, float y2, float z1, float z2){
	charController->setWalkDirection(btVector3(x2 - x1, y2 - y1, z2 - z1));
}


void Player::MoveLeft(){
	float x1 = camera->GetCameraPos()[0],
		z1 = camera->GetCameraPos()[2];

	camera->MoveCameraXZ(MOVE_VEL, 90.0f);

	float x2 = camera->GetCameraPos()[0],
		z2 = camera->GetCameraPos()[2];

	MovePhysicObj(x1, x2, 0, 0, z1, z2);
}


void Player::MoveForward(){
	float x1 = camera->GetCameraPos()[0],
		z1 = camera->GetCameraPos()[2];

	camera->MoveCameraXZ(MOVE_VEL, 0.0f);

	float x2 = camera->GetCameraPos()[0],
		z2 = camera->GetCameraPos()[2];

	MovePhysicObj(x1, x2, 0, 0, z1, z2);
}


void Player::MoveRight(){
	float x1 = camera->GetCameraPos()[0],
		z1 = camera->GetCameraPos()[2];

	camera->MoveCameraXZ(MOVE_VEL, 270.0f);

	float x2 = camera->GetCameraPos()[0],
		z2 = camera->GetCameraPos()[2];


	MovePhysicObj(x1, x2, 0, 0, z1, z2);
}


void Player::MoveBackward(){
	float x1 = camera->GetCameraPos()[0],
		z1 = camera->GetCameraPos()[2];

	camera->MoveCameraXZ(MOVE_VEL, 180.0f);
	
	float x2 = camera->GetCameraPos()[0],
		z2 = camera->GetCameraPos()[2];

	MovePhysicObj(x1, x2, 0, 0, z1, z2);
}


void Player::Jump(){
	if(charController->onGround()){
		charController->jump(btVector3(0.0f, 10.0f, 0.0f));
	}

}


void Player::Shoot(){
	RenderObject *bullet = new GameObject(renderer, physics, audio, Shape::Sphere, Type::Bullet, 
		camera->GetCameraPos()[0], camera->GetCameraPos()[1], camera->GetCameraPos()[2], 
		0.2f, 0.05f, 0.0f, 255, 255, 255, 255, GameLevel::GetBulletTex(), 2500);
	
	float *camLook = camera->GetCameraLookVect();
	((GameObject*)bullet)->GetBody()->setLinearVelocity(btVector3(camLook[0] * BULLET_VEL, camLook[1] * BULLET_VEL, camLook[2] * BULLET_VEL));

	audio->PlayEffect("throw_sound.wav");
}


void Player::ShowControls(bool show){
	if(show){
		GameLevel::SetStartPause(SDL_GetTicks() / 1000);
		GameLevel::SetGameState(Paused);
	}
	else{
		GameLevel::SetEndPause(SDL_GetTicks() / 1000);
		GameLevel::SetGameState(Running);
	}
}


void Player::NoMovement(){
	charController->setWalkDirection(btVector3(0.0f,0.0f,0.0f));
}