#include "Particles.h"


Particles::Particles(const std::string fileName, const glm::vec3 &pos, int numParticles) : m_particles(std::vector<Particle>(numParticles))
{
// 	OGL::Bitmap bmp = OGL::Bitmap::bitmapFromFile(ResourcePath(fileName));
// 	bmp.flipVertically();
// 	m_asset->texture = new OGL::Texture(bmp);
	SetPosition(pos);
}

Particles::~Particles()
{

}

void Particles::Initialize(Graphics* graphics)
{
	std::vector<Utils::Color> colors;
	colors.push_back(Utils::Color(1.0f, 0.0f, 0.0f, 1.0f));
	colors.push_back(Utils::Color(1.0f, 1.0f, 0.0f, 1.0f));
	colors.push_back(Utils::Color(1.0f, 0.5f, 0.0f, 1.0f));
	colors.push_back(Utils::Color(0.5f, 0.5f, 0.5f, 1.0f));


	for (pItr it = m_particles.begin(); it != m_particles.end(); ++it)
	{
		float randX = rand() / ((float)RAND_MAX + 1) - 0.5f;
		float randY = rand() / ((float)RAND_MAX + 1) - 0.5f;
		float randZ = rand() / ((float)RAND_MAX + 1) - 0.5f;
		float randSpeed = 1.5f;

		(*it).life = 10.0f;
		(*it).velocity = glm::vec3(randX, randY, randZ);
		glm::normalize((*it).velocity);
		(*it).velocity = (*it).velocity * randSpeed;

		(*it).position = m_position;

		int randColor = rand() % colors.size();
		(*it).color = colors[randColor];
	}

	m_asset = new ModelAsset();
	m_asset->shaders = graphics->LoadShaders("particle-vertex.txt", "particle-fragment.txt");
	m_asset->drawType = GL_POINTS;
	m_asset->texture = graphics->LoadTexture("Red.png");

	m_asset->shaders->use();
	m_asset->shaders->bindAttrib(0, "a_Vertex");
	m_asset->shaders->bindAttrib(1, "a_Color");
	m_asset->shaders->setUniform("orthoMat4", glm::ortho(0.0f, SCREEN_SIZE.x, 0.0f, SCREEN_SIZE.y));
	m_asset->shaders->stopUsing();
	glGenBuffers(1, &m_asset->vao); //Generate a buffer for the vertices
	glBindBuffer(GL_ARRAY_BUFFER, m_asset->vao); //Bind the vertex buffer
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * m_particles.size(), NULL, GL_DYNAMIC_DRAW); //Send the data to OpenGL

	glGenBuffers(1, &m_asset->vbo); //Generate a buffer for the colors
	glBindBuffer(GL_ARRAY_BUFFER, m_asset->vbo); //Bind the vertex buffer
	glBufferData(GL_ARRAY_BUFFER, sizeof(Utils::Color) * m_particles.size(), NULL, GL_DYNAMIC_DRAW); //Send the data to OpenGL

	glBindVertexArray(0);
}


void Particles::SetPosition( const glm::vec3& pos )
{
	m_position = pos;
	for (pItr it = m_particles.begin(); it != m_particles.end(); ++it)
	{
		(*it).position = m_position;
	}
}

void Particles::Update( float timeElapsed )
{
	int numDead = 0;
	for (pItr it = m_particles.begin(); it != m_particles.end(); ++it)
	{
		if ((*it).life <= 0.0f)
		{
			numDead++;
			continue;
		}

		(*it).life -= 1.0f * timeElapsed;
		(*it).position += (*it).velocity * timeElapsed;
		std::cout << (*it).position.x << "  " << (*it).position.y << std::endl;
	}

	if (numDead == m_particles.size())
	{
		//destroy();
	}
}

 //void Particles::Draw()
 //{
 //
 //
 //	static std::vector<glm::vec3> positions;
 //	static std::vector<Utils::Color> colors;
 //
 //	m_asset->shaders->use();
 //
 //
 //	float w = SCREEN_SIZE.x;
 //	float h = SCREEN_SIZE.y;
 //	m_asset->shaders->setUniform("orthoMat4", glm::ortho(0.0f, w, 0.0f, h));
 //
 //	//Send the modelview and projection matrices to the shaders
 //	//m_program->setUniformMatrix4("modelview_matrix", modelviewMatrix);
 //	//m_program->setUniformMatrix4("projection_matrix", projectionMatrix);
 //	m_asset->shaders->SetUniform("point_size", 50.0f);
 //	
 //
 //	positions.clear();
 //	colors.clear();
	//glActiveTexture(GL_TEXTURE0);
	//
 //	glBindTexture(GL_TEXTURE_2D, m_asset->texture->object());
	//m_asset->shaders->SetUniform("texture0", 0);
 //	for (pItr it = m_particles.begin(); it != m_particles.end(); ++it)
 //	{
 //		if ((*it).life <= 0.0f)
 //		{
 //			continue; //Ignore dead particles
 //		}
 //
 //		//Add to the list of points to be rendered
 //		positions.push_back((*it).position);
 //		Utils::Color c = (*it).color;
 //		c.a = (*it).life;
 //		colors.push_back(c);
 //	}
 //
 //	if (positions.empty())
 //	{
 //		return;
 //	}
	//glBindVertexArray(m_asset->vao);

 //
 //	// 	glDepthMask(GL_FALSE);
 //	// 	glEnable(GL_BLEND);
 //	// 	glBlendFunc(GL_SRC_ALPHA, GL_ONE);
 //	// 	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
 //
 //	//Draw the points
 //	glEnable(GL_POINT_SPRITE);
 //	//glEnable(GL_VERTEX_PROGRAM_POINT_SIZE);
 //	glTexEnvi(GL_POINT_SPRITE, GL_COORD_REPLACE, GL_TRUE);
 //	glDrawArrays(m_asset->drawType, 0, positions.size());
 //	glDisable(GL_POINT_SPRITE);
 //
	//glBindVertexArray(0);
	//glBindTexture(GL_TEXTURE_2D, 0);
	//m_asset->shaders->stopUsing();
 //
 //}

 void Particles::Draw()
 {
 
 	
 	static std::vector<glm::vec3> positions;
 	static std::vector<Utils::Color> colors;
 
 	m_asset->shaders->use();
 
 
 	float w = SCREEN_SIZE.x;
 	float h = SCREEN_SIZE.y;
 	//m_asset->shaders->setUniform("orthoMat4", glm::ortho(0.0f, w, 0.0f, h));
 
 	//Send the modelview and projection matrices to the shaders
 	//m_program->setUniformMatrix4("modelview_matrix", modelviewMatrix);
 	//m_program->setUniformMatrix4("projection_matrix", projectionMatrix);
 	m_asset->shaders->SetUniform("point_size", 50.0f);
 	//m_asset->shaders->SetUniform("texture0", 0);
 
 	positions.clear();
 	colors.clear();
 
	glActiveTexture(GL_TEXTURE0);

	glBindTexture(GL_TEXTURE_2D, m_asset->texture->object());
	m_asset->shaders->SetUniform("texture0", 0);
 	for (pItr it = m_particles.begin(); it != m_particles.end(); ++it)
 	{
 		if ((*it).life <= 0.0f)
 		{
 			continue; //Ignore dead particles
 		}
 
 		//Add to the list of points to be rendered
 		positions.push_back((*it).position);
 		Utils::Color c = (*it).color;
 		c.a = (*it).life;
 		colors.push_back(c);
 	}
 
 	if (positions.empty())
 	{
 		return;
 	}
	//glBindVertexArray(m_asset->vao);

	glBindBuffer(GL_ARRAY_BUFFER, m_asset->vao);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(glm::vec3) * positions.size(), &positions[0]);

	glBindBuffer(GL_ARRAY_BUFFER, m_asset->vbo);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(Utils::Color) * colors.size(), &colors[0]);

	glBindVertexArray(m_asset->vbo);
 
  	glDepthMask(GL_FALSE);
  	glEnable(GL_BLEND);
  	glBlendFunc(GL_SRC_ALPHA, GL_ONE);
  	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
 
 	//Draw the points
 	glEnable(GL_POINT_SPRITE);
 	glEnable(GL_VERTEX_PROGRAM_POINT_SIZE);
 	glTexEnvi(GL_POINT_SPRITE, GL_COORD_REPLACE, GL_TRUE);
 	glDrawArrays(m_asset->drawType, 0, positions.size());
 	glDisable(GL_POINT_SPRITE);
 
  	glDisable(GL_BLEND);
  	glDepthMask(GL_TRUE);
 	//glDisableVertexAttribArray(1);
 	//glDisableVertexAttribArray(0);

	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
	m_asset->shaders->stopUsing();
 
 }




