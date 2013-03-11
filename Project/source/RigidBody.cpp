
#include "RigidBody.h"


RigidBody::RigidBody(const b2Vec2& pos, const b2Vec2& size, b2BodyType type, float density, float friciton )
{
	m_bodyDef = b2BodyDef();
	m_polyShape = b2PolygonShape();
	m_fixDef = b2FixtureDef();

	m_bodyDef.type = type;
	m_bodyDef.position.Set(pos.x, pos.y);

	m_polyShape.SetAsBox(size.x/2, size.y/2);

	m_fixDef.shape = &m_polyShape;
	m_fixDef.density = density;
	m_fixDef.friction = friciton;
	m_fixDef.restitution = .4f;

}

b2BodyDef RigidBody::GetBodyDef() const
{
	return m_bodyDef;
}

b2PolygonShape RigidBody::GetPolyShape() const
{
	return m_polyShape;
}

b2FixtureDef RigidBody::GetFixDef() const
{
	return m_fixDef;
}

b2Body * RigidBody::GetBody() const
{
	return m_body;
}

void RigidBody::SetBody( b2Body * val )
{
	m_body = val;
}
