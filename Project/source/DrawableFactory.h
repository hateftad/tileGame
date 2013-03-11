#ifndef TILEFACTORY_H
#define TILEFACTORY_H

#include "Graphics.h"
#include "Tile.h"
#include "MoveableShape.h"
#include "StaticShape.h"

class DrawableFactory
{
public:
	DrawableFactory(Graphics* graphics){ m_graphics = graphics;}
	DrawableFactory(const DrawableFactory& ){}
	DrawableFactory &operator=(const DrawableFactory& ){return *this;}
	~DrawableFactory();

	Tile* CreateTile(const std::string& fileName, const glm::vec3& pos, const glm::vec2& size);
	MoveableShape* CreateMovableShape(const std::string& fileName, const glm::vec3& pos, const glm::vec2& size);
	StaticShape* CreateStaticShape(const std::string& fileName, const glm::vec3& pos, const glm::vec2& size);
	
private:
	Graphics* m_graphics;
};


#endif