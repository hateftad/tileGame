#include "StaticShape.h"
#include "Helpers.h"
#include <iostream>


StaticShape::StaticShape(const std::string& fileName, const glm::vec3 &pos, const glm::vec2& size) : IRenderable(fileName, pos, size)
{
	//m_body = new RigidBody(Utils::Vec3TobVec(pos), Utils::Vec2TobVec(size), b2_staticBody, 0.0f, 0.3f);
}

StaticShape::~StaticShape()
{
	
}

void StaticShape::Render( Graphics* graphics)
{
	graphics->Render(this);
}



