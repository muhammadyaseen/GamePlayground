#include "CollisionListener.h"



CollisionListener::CollisionListener()
{
}


CollisionListener::~CollisionListener()
{
}

void CollisionListener::BeginContact(b2Contact* contact)
{
	GameObject* objectA = (GameObject *)contact->GetFixtureA()->GetBody()->GetUserData();
	GameObject* objectB = (GameObject *)contact->GetFixtureB()->GetBody()->GetUserData();

	if ( objectA == NULL || objectB == NULL ) { return; }

	cout << "some collision detection";
	
	/*
	if ( 
		( objectA->getEntityType() == BRICK_PLATFORM && objectB->getEntityType() == EDWARD ) || 
		( objectA->getEntityType() == EDWARD && objectB->getEntityType() == BRICK_PLATFORM )
		)
	{
		cout << "edward collides with brick platform";
	}


	if ( 
		( objectA->getEntityType() == RANGER && objectB->getEntityType() == EDWARD ) || 
		( objectA->getEntityType() == EDWARD && objectB->getEntityType() == RANGER )
		)
	{
		cout << "edward collides with ranger";
	}

	
	if ( 
		( objectA->getEntityType() == TREE && objectB->getEntityType() == EDWARD ) || 
		( objectA->getEntityType() == EDWARD && objectB->getEntityType() == TREE )
		)
	{
		cout << "edward collides with tree";
	}


	if ( 
		( objectA->getEntityType() == SPIKE_BALL && objectB->getEntityType() == EDWARD ) || 
		( objectA->getEntityType() == EDWARD && objectB->getEntityType() == SPIKE_BALL )
		)
	{
		cout << "edward collides with spikeball";
	}
	*/

	
}


void CollisionListener::EndContact(b2Contact* contact)
{

}