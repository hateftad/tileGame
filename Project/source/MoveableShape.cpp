#include "Helpers.h"
#include "MoveableShape.h"

MoveableShape::MoveableShape(const std::string fileName, const glm::vec3 &pos, const glm::vec2& size) : IRenderable(fileName, pos, size)
{
	
	m_waypoints.push_back(glm::vec3(242, 30, 0.2));
	m_waypoints.push_back(glm::vec3(242, 75, 0.2));
	m_waypoints.push_back(glm::vec3(205, 75, 0.2));
	m_waypoints.push_back(glm::vec3(205, 205, 0.2));
	m_waypoints.push_back(glm::vec3(180, 205, 0.2));
	m_velocity = glm::vec3();
	m_moveSpeed = 4.5f;
	m_current = 0;
	vel = glm::vec3();

	//m_body = new RigidBody(Utils::Vec3TobVec(pos), Utils::Vec2TobVec(size), b2_dynamicBody, 1.0f, 0.3f);
}

void MoveableShape::Update( float timeElapsed )
{
	m_position += m_velocity * timeElapsed;
	if(m_current < m_waypoints.size())
	{
		
		glm::vec3 target = m_waypoints.at(m_current);
		glm::vec3 movDir = target - m_position;
		vel = m_velocity;

		if (glm::length(m_position - target) < 1.f)
		{
			m_current++;
		}
		else
		{
			vel = glm::normalize(movDir) * m_moveSpeed;
		}
	}
	m_velocity = vel;
}

void MoveableShape::Render( Graphics* graphics )
{
	graphics->Render(this);
}

