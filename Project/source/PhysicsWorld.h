#ifndef PHYSICSWORLD_H 
#define PHYSICSWORLD_H

#include <Box2D/Box2D.h>
#include "RigidBody.h"


class PhysicsWorld
{
public:
	PhysicsWorld(const b2Vec2& gravity, bool doSleep);
	~PhysicsWorld();
	void Update(float timeElasped);
	b2Body* AddBody(RigidBody* body);
	void SetDebugDrawer(b2Draw* drawer);
	b2World* GetWorld(){return m_world;}

protected:
private:
	b2World *m_world;
	int m_iterations;
	float32 m_timeStep;
	int32 m_velocityIterations;
	int32 m_positionIterations;
};


#endif