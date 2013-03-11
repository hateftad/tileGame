#ifndef ANIMATION_H
#define ANIMATION_H

#include "IRenderable.h"

class Animation
{
public:

	
	enum Direction
	{
		LEFT = 1,
		RIGHT,
		UP,
		DOWN,
		STILL
	};

	enum AnimType
	{
		MATCH,
		NOMATCH,
		SCALE,
	};

	Animation();
	~Animation();
	void Animate(IRenderable* object, float timeElapsed);
	void PlayAnimation(AnimType type, const glm::vec3& from, const glm::vec3& to, float delay = 0.0f);
	void QueueAnim(const glm::vec3& from, const glm::vec3& to, float delay);
	void Reset();
	void SetSpeed(float speed){m_animSpeed = speed;}
	float GetSpeed() const {return m_animSpeed;}

private:

	struct QueuedAnim
	{
		glm::vec3 start;
		glm::vec3 end;
		float delay;
	};

	Animation(const Animation&);
	const Animation& operator=(const Animation&);

	QueuedAnim m_queued;

	float m_animSpeed;
	float m_lastTime;
	float m_delay;
	float m_scaleDelay;

	bool m_scaleEnabled;
	bool m_stay;

	glm::vec3 m_direction;
	glm::vec3 m_stopAt;
	glm::vec3 m_currentPosition;
	glm::vec3 m_scaleAmt;
	
	bool IsAtStop(IRenderable* object);
	void Matched(const glm::vec3& from, const glm::vec3& to );
	void NoMatch(const glm::vec3& from, const glm::vec3& to);
	void FadeOut(float delay);
	void PlayQueued(IRenderable* object);
};


#endif