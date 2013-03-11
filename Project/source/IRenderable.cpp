#include "IRenderable.h"

IRenderable::IRenderable(const std::string& filePath, const glm::vec3& pos, const glm::vec2& size )
{
	m_asset = new ModelAsset();
	m_scale = glm::vec3(1,1,1);
	m_zdepth = pos.z;
	m_angle = 0.0f;
	SetPosition(pos);
	SetDimension(size);
	LoadTexture(filePath);
	SetTextureCoords(glm::vec2(1.0f, 1.0f));
	m_animate = false;
}

void IRenderable::LoadTexture( const std::string& fileName )
{
	OGL::Bitmap bmp = OGL::Bitmap::bitmapFromFile(ResourcePath(fileName));
	bmp.flipVertically();
	m_asset->texture = new OGL::Texture(bmp);
}


OGL::Texture* IRenderable::GetTexture()
{
	return m_asset->texture;
}


IRenderable::~IRenderable()
{
	delete m_asset->texture;
	glDeleteBuffers(1, &m_asset->vao);
	glDeleteBuffers(1, &m_asset->vbo);
}

void IRenderable::SetTexture( OGL::Texture* texture )
{
	m_asset->texture = texture;

}
