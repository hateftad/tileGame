#ifndef PARTICLES_H
#define PARTICLES_H

#include "IRenderable.h"
#include "Geometry.h"



class Particles
{
public:
	struct Particle
	{
		float life;
		glm::vec3 position;
		glm::vec3 velocity;
		Utils::Color color;
	};
	typedef std::vector<Particle>::iterator pItr;

	Particles(const std::string fileName, const glm::vec3 &pos, int num);
	~Particles();
	void Initialize(Graphics* graphics);
	glm::vec3 GetPosition(){return m_position;}
	void SetPosition(const glm::vec3& pos);
	void Update(float timeElapsed);
	void Draw();

private:
	ModelAsset *m_asset;
	glm::vec3 m_position;

	std::vector<Particle> m_particles;
};


#endif