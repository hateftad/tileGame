#ifndef RENDERABLE_H
#define RENDERABLE_H

#include "Graphics.h"
#include "RigidBody.h"


static std::string ResourcePath(std::string fileName) {
	char executablePath[1024] = {'\0'};
	DWORD charsCopied = GetModuleFileName(NULL, executablePath, 1024);
	if(charsCopied > 0 && charsCopied < 1024)
		return std::string(executablePath) + "\\..\\" + fileName;
	else
		throw std::runtime_error("GetModuleFileName failed a bit");
}

class IRenderable
{
public:

	IRenderable(){}
	IRenderable(const std::string& filePath, const glm::vec3& pos, const glm::vec2& size);
	virtual ~IRenderable();
	virtual void Render(Graphics* graphics) = 0;
	virtual void Update(float timeElapsed) = 0;

	glm::vec3 GetPosition() const {return m_position;}
	float GetZ()const {return m_zdepth;}
	void SetPosition(const glm::vec3& pos){m_position = pos;}

	glm::vec3 GetScale() const { return m_scale; }
	void SetScale(const glm::vec3 &val) { m_scale = val; }

	float GetAngle() const { return m_angle; }
	void SetAngle(float val) { m_angle = val; }

	glm::vec2 GetDimension() const {return m_dimensions;}
	void SetDimension(const glm::vec2& size){m_dimensions = size;}

	glm::vec2 GetTextureCoords() const { return m_textureCoords; }
	void SetTextureCoords(const glm::vec2& val) { m_textureCoords = val; }

	bool IsAnimating() const { return m_animate; }
	void Animate(bool val) { m_animate = val; }

	OGL::Texture* GetTexture();
	void LoadTexture(const std::string& filePath);
	void SetTexture(OGL::Texture* texture);

	//RigidBody* GetRigidBody() const { return m_body; }
	//void SetRigidBody(RigidBody* val) { m_body = val; }

	ModelAsset * GetAsset() const { return m_asset; }
	void SetAsset(ModelAsset * val) { m_asset = val; }

protected:

	ModelAsset *m_asset;
	//RigidBody* m_body;

	glm::vec3 m_position;
	float m_angle;

	float m_zdepth;
	glm::vec3 m_scale;
	glm::vec2 m_dimensions;
	glm::vec2 m_textureCoords;

	float m_textureOffset;
	bool m_animate;
	
	

};


#endif