#include "Points.h"

Points::Points(DrawableFactory* df, OGL::Texture** textures)
{
	m_shapes.push_back(df->CreateStaticShape("zero.png", glm::vec3(70, 378, 0.3f), glm::vec2(25,25)));
	m_shapes.push_back(df->CreateStaticShape("zero.png", glm::vec3(105, 378, 0.3f), glm::vec2(25,25)));
	m_shapes.push_back(df->CreateStaticShape("zero.png", glm::vec3(140, 378, 0.3f), glm::vec2(25,25)));
	m_shapes.push_back(df->CreateStaticShape("zero.png", glm::vec3(175, 378, 0.3f), glm::vec2(25,25)));
	
	m_textures = textures;

	m_points = 0;
}

Points::~Points()
{

}

void Points::Update( float timeElapsed )
{

	m_shapes.at(0)->SetTexture(m_textures[m_points / 1000]);
// 	if (m_points > 999)
// 	{
// 		m_shapes.at(1)->SetTexture(m_textures[m_points % 1000]);
// 	}
// 	else 
		m_shapes.at(1)->SetTexture(m_textures[m_points / 100]);
	
	m_shapes.at(2)->SetTexture(m_textures[(m_points % 100)/10]);
	m_shapes.at(3)->SetTexture(m_textures[m_points % 10]);
}


void Points::Add()
{
	m_points += 50;
}

void Points::Remove()
{
	if ((m_points - 50) > 0)
	{
		m_points -= 50;
	}
}
