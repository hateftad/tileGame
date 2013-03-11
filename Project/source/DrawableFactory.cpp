#include "DrawableFactory.h"


Tile* DrawableFactory::CreateTile(const std::string& fileName, const glm::vec3& pos, const glm::vec2& size )
{
	Tile *t = new Tile(fileName, pos, size);
	m_graphics->SetUpTriangles(size, fileName, t);
	return t;
}

MoveableShape* DrawableFactory::CreateMovableShape( const std::string& fileName, const glm::vec3& pos, const glm::vec2& size )
{
	MoveableShape *f = new MoveableShape(fileName, pos, size);
	m_graphics->SetUpTriangles(size,fileName, f);
	return f;
}

StaticShape* DrawableFactory::CreateStaticShape(const std::string& fileName, const glm::vec3& pos, const glm::vec2& size )
{
	StaticShape* s = new StaticShape(fileName, pos, size);
	m_graphics->SetUpTriangles(size, fileName, s);
	return s;
}
