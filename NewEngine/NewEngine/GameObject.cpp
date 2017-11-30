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

	SetID(GetNewObjID());
	SetBody(body);

	physics->AddPhysicsObj(this);
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


	SetID(GetNewObjID());
}


GameObject::GameObject(GraphicsRenderer *renderer, PhysicsManager *physics, AudioPlayer *audio, Shape shape, Type type, float x, float y, float z, float mass, float radius, float height,
	int red, int green, int blue, int alpha, string texture, int lifeTime) : GameObject(renderer, physics, audio, type, red, green, blue, alpha){
	
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

	this->texture = texture;

	this->lifeTime = lifeTime;
	if(lifeTime > 0){
		lifeStart = SDL_GetTicks();
	}

	physics->AddPhysicsObj(this);
}


GameObject::GameObject(GraphicsRenderer *renderer, PhysicsManager *physics, AudioPlayer *audio, Shape shape, Type type, float x, float y, float z, float mass, float width, float height, float depth,
	int red, int green, int blue, int alpha, string texture) : GameObject(renderer, physics, audio, type, red, green, blue, alpha){
	
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

	this->texture = texture;

	physics->AddPhysicsObj(this);
}

void GameObject::Render(){
	//Check if object should be removed after certain interval
	if(lifeTime > 0 && SDL_GetTicks() - lifeStart > lifeTime){
		renderer->RemoveRenderObj(this);
		physics->RemovePhysicsObj(this);
		return;
	}
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
				red, green, blue, alpha, texture);
			break;
		}

		case SPHERE_SHAPE_PROXYTYPE: {
			GraphicsRenderer::RenderSphere(((btSphereShape*)shape)->getRadius(), matrix,
				red, green, blue, alpha, texture);
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
				red, green, blue, alpha, texture);
			break;
		}

	}
}

void GameObject::HandleHit(PhysicsObject *Other){
	GameObject *o = (GameObject*)Other;

	if(objType == Type::Bullet){
		switch(o->objType){
			case DisabledTarget:{
				audio->PlayEffect("minor_points.wav");
				GameLevel::UpdateScore(GameLevel::GetDisabledTargetPoints());
				break;
			}
			case DisabledNonTarget:{
				audio->PlayEffect("bump.wav");
				GameLevel::UpdateScore(GameLevel::GetDisabledNegativeTargetPoints());
				break;
			}
			case Target:{
				audio->PlayEffect("mario_coin.wav");
				GameLevel::UpdateScore(GameLevel::GetTargetPoints());

				o->objType = Type::DisabledTarget;
				o->texture = "disabledTarget.png";
				break;
			}
			case NonTarget:{
				audio->PlayEffect("bump.wav");
				GameLevel::UpdateScore(GameLevel::GetNegativeTargetPoints());

				o->objType = Type::DisabledNonTarget;
				o->texture = "wrongDisabledTarget.png";
				break;
			}
			case Floor:
				break;

			default:
				return;
		}

		renderer->RemoveRenderObj(this);
		physics->RemovePhysicsObj(this);
	}

}
