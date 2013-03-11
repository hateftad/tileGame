
#ifndef SQUARE_H
#define SQUARE_H

#include "IRenderable.h"
#include "RigidBody.h"

class StaticShape: public IRenderable
{
public:
	StaticShape(){}
	StaticShape(const std::string& fileName, const glm::vec3 &pos, const glm::vec2& size);
	~StaticShape();
	void Render(Graphics* graphics);
	void Update(float timeElapsed){};
private:
};


#endif