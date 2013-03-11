#ifndef POINTS_H
#define POINTS_H

#include "StaticShape.h"
#include "DrawableFactory.h"

class Points
{
public:
	Points(DrawableFactory* df, OGL::Texture** textures);
	~Points();
	void Update(float timeElapsed);
	void Add();
	void Remove();
	std::vector<IRenderable*> Shapes() const { return m_shapes; }
private:
	OGL::Texture** m_textures;
	std::vector<IRenderable*> m_shapes;
	int m_points;
};

#endif