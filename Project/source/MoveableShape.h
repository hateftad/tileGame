#ifndef FUSE_H
#define FUSE_H

#include "IRenderable.h"
#include "Animation.h"
#include "RigidBody.h"

class MoveableShape : public IRenderable
{
public:
	MoveableShape(const std::string fileName, const glm::vec3 &pos, const glm::vec2& size);
	~MoveableShape(){};
	void Update(float timeElapsed);
	void Render(Graphics* graphics);

	Animation* GetAnimation() const { return m_animation; }
	void SetAnimation(Animation* val) { m_animation = val; }

	bool IsSetToMove() const { return m_setToMove; }
	void SetToMove(bool val) { m_setToMove = val; }

protected:

	Animation *m_animation;
	bool m_setToMove;
	
private:

	std::vector<glm::vec3> m_waypoints;
	glm::vec3 m_velocity;
	float m_moveSpeed;
	unsigned int m_current;
	glm::vec3 vel;
};



#endif