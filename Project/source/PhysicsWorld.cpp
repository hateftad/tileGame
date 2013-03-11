
#include "PhysicsWorld.h"

PhysicsWorld::PhysicsWorld( const b2Vec2& gravity, bool doSleep )
{
	m_world = new b2World(gravity);
	m_world->SetAllowSleeping(doSleep);
	m_iterations = 60;
	m_timeStep = 1.0f / 60.0f;
	m_velocityIterations = 6;
	m_positionIterations = 2;
}

void PhysicsWorld::Update( float timeElasped )
{


		// Instruct the world to perform a single step of simulation.
		// It is generally best to keep the time step and iterations fixed.
		m_world->Step(m_timeStep, m_velocityIterations, m_positionIterations);

// 		// Now print the position and angle of the body.
// 		b2Vec2 position = body->GetPosition();
// 		float32 angle = body->GetAngle();
}

b2Body* PhysicsWorld::AddBody( RigidBody* body )
{

	body->SetBody(m_world->CreateBody(&body->GetBodyDef()));

	if (body->GetBodyDef().type == b2_dynamicBody)
	{
		body->GetBody()->CreateFixture(&body->GetFixDef());
	}
	else if (body->GetBodyDef().type == b2_staticBody)
	{
		body->GetBody()->CreateFixture(&body->GetPolyShape(), 0.0f);
	}

	return body->GetBody();
}

void PhysicsWorld::SetDebugDrawer( b2Draw* drawer )
{
	m_world->SetDebugDraw(drawer);
}
