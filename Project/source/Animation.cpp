#include "Animation.h"
#include "Helpers.h"
#include "SoundManager.h"
#include <gl/glfw.h>
#include <iostream>
#include <math.h>


Animation::Animation()
{
	Reset();
}

void Animation::Reset()
{
	m_animSpeed = 3.0f;
	m_scaleEnabled = false;
	m_delay = 0.0f;
	m_scaleDelay = 1.0f;
	m_stay = false;

	m_direction = glm::vec3();
	m_stopAt = glm::vec3();
	m_currentPosition =glm::vec3();
	m_scaleAmt = glm::vec3();

}

Animation::~Animation()
{

}

void Animation::Animate( IRenderable* object , float timeElapsed)
{


	if (!IsAtStop(object))
	{
		if (glfwGetTime() - m_lastTime > m_delay)
		{
			object->SetPosition(object->GetPosition() + (m_direction) * timeElapsed * m_animSpeed);
		}
	}

	if (m_scaleEnabled)
	{
		if (glfwGetTime() - m_lastTime > m_scaleDelay)
		{
			
			object->SetScale(object->GetScale() + m_scaleAmt * timeElapsed);
			if (object->GetScale().y < 0.0f)
			{
		 		object->SetScale(glm::vec3(0,0,0));
				m_scaleEnabled = false;
				PlayQueued(object);
			}
		}
	}
	
}


bool Animation::IsAtStop( IRenderable* object )
{
	bool atStop = Utils::AtPosition(object, m_stopAt, m_direction);
	if (atStop)
	{
		
		if (!m_stay)
		{
			m_stopAt = m_currentPosition;
			atStop = m_stay;
			m_direction = -m_direction;
			m_stay = true;

		}
		else
		{

			SoundManager::Instance()->PlayEvent("Drop");
			m_direction = glm::vec3();
			object->Animate(false);
			object->SetPosition(m_stopAt);
		}

	}
	return atStop;
}

void Animation::NoMatch( const glm::vec3& from, const glm::vec3& to )
{
	m_direction = Utils::Direction(from, to);
	
	m_stopAt = to;
	m_currentPosition = from;
	m_stay = false;
	m_delay = 0.0f;
}


void Animation::PlayAnimation( AnimType type, const glm::vec3& from, const glm::vec3& to, float delay )
{

	switch(type)
	{
	case NOMATCH:
		NoMatch(from, to);
		break;
	case MATCH:
		Matched(from, to);
		break;
	case SCALE:
		FadeOut(delay);
		break;
	default:
		break;
	}
}

void Animation::Matched(const glm::vec3& from, const glm::vec3& to )
{
	
	m_direction = Utils::Direction(from, to);
	m_stopAt = to;
	m_currentPosition = from;
	m_stay = true;
	m_delay = 0.0f;
	m_scaleDelay = 1.0f;
}


void Animation::FadeOut( float delay )
{
	m_scaleEnabled = true;
	m_scaleAmt.y = -2.5f;
	m_scaleDelay = delay;

}

void Animation::QueueAnim( const glm::vec3& from, const glm::vec3& to, float delay )
{
	m_queued.start = from;
	m_queued.end = to;
	m_queued.delay = delay;
}

void Animation::PlayQueued( IRenderable* object )
{
	
	Reset();
	m_direction = glm::vec3(0, -80.f, 0);
	m_stopAt = m_queued.end;
	m_currentPosition = m_queued.start;
	object->SetPosition(m_queued.start);
	object->SetScale(glm::vec3(1,1,1));
	m_stay = true;
	m_delay = m_queued.delay;
	m_lastTime = (float)glfwGetTime();
}
