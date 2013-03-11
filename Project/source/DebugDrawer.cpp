#include "DebugDrawer.h"

#define ARRAY_COUNT( array ) (sizeof( array ) / (sizeof( array[0] ) * (sizeof( array ) != sizeof(void*) || sizeof( array[0] ) <= sizeof(void*))))

const float vertexPositions[] = {
	100.25f, 100.25f,
	100.25f, 200.25f,
	200.25f, 200.25f,
	200.25f, 100.25f
};

DebugDrawer::DebugDrawer(Graphics* graphics)
{
	m_assets = new ModelAsset();
	m_assets->shaders = graphics->LoadShaders("standard-vert.txt", "standard-frag.txt");
	m_assets->texture = graphics->LoadTexture("Blue.png");

	glGenBuffers(1, &m_assets->vbo);

	glBindBuffer(GL_ARRAY_BUFFER, m_assets->vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexPositions), vertexPositions, GL_STREAM_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenVertexArrays(1, &m_assets->vao);
	glBindVertexArray(m_assets->vao);

	glBindVertexArray(0);
	m_assets->shaders->use();
	m_assets->shaders->setUniform("orthoMat4", glm::ortho(0.0f, graphics->GetWindow().x, 0.0f, graphics->GetWindow().y));
	m_assets->shaders->stopUsing();


}


void DebugDrawer::DrawPolygon( const b2Vec2* vertices, int32 vertexCount, const b2Color& color )
{
	CreateVerts(vertices, vertexCount, sizeof(vertexPositions));	Draw(vertexCount);
}

void DebugDrawer::Draw( int32 vertexCount )
{


	m_assets->shaders->use();	glBindBuffer(GL_ARRAY_BUFFER, m_assets->vbo);	glEnableVertexAttribArray(m_assets->shaders->attrib("position"));		glVertexAttribPointer(m_assets->shaders->attrib("position"), 2, GL_FLOAT, GL_FALSE, 0, 0);		glBindVertexArray(m_assets->vao);	glDrawArrays(GL_LINE_LOOP, 0, 4);		glDisableVertexAttribArray(0);	//glBindVertexArray(0);	m_assets->shaders->stopUsing();

	//glfwSwapBuffers();
}

void DebugDrawer::CreateVerts( const b2Vec2* vertices, int32 vertexCount, int size )
{

	GLfloat glverts[8];
	int count = 0;
	for (int i = 0; i < vertexCount; i++) {
		glverts[count++]   = vertices[i].x;
		glverts[count++] = vertices[i].y;

	}

	glBindBuffer(GL_ARRAY_BUFFER, m_assets->vbo);
	glBufferSubData(GL_ARRAY_BUFFER, 0, size, &glverts[0]);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

