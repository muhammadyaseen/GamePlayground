#pragma once

#include <iostream>
#include <Box2D\Box2D.h>
#include "EntityType.cpp"
#include "GameObject.h"
#include "SwingSpikeBall.h"
#include "Player.h"

using namespace std;

class CollisionListener : public b2ContactListener
{
public:

	CollisionListener();

	~CollisionListener();

	/// Called when two fixtures begin to touch.
	virtual void BeginContact(b2Contact* contact);

	/// Called when two fixtures cease to touch.
	virtual void EndContact(b2Contact* contact); 

	
	/// Called before solving the collision (yes, we use diffn'l equations)
	virtual void PreSolve(b2Contact* contact, const b2Manifold* oldManifold)
	{
		B2_NOT_USED(contact);
		B2_NOT_USED(oldManifold);
	}

	/// This lets you inspect a contact after the solver is finished. This is useful
	/// for inspecting impulses.

	virtual void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse)
	{
		B2_NOT_USED(contact);
		B2_NOT_USED(impulse);
	}
};

