#ifndef RIGIDBODY_H
#define RIGIDBODY_H

#include <Box2D/Box2D.h>

class RigidBody
{
public:
	RigidBody(const b2Vec2& pos, const b2Vec2& size, b2BodyType type, float density, float friciton);
	~RigidBody();

	b2BodyDef GetBodyDef() const;

	b2PolygonShape GetPolyShape() const;
	
	b2FixtureDef GetFixDef() const;
	
	b2Body *GetBody() const;
	void SetBody(b2Body * val);

private:
	b2BodyDef m_bodyDef;
	b2PolygonShape m_polyShape;
	b2FixtureDef m_fixDef;
	b2Body *m_body;
};



#endif