#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <Windows.h>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "tdogl/Texture.h"
#include "tdogl/Bitmap.h"
#include "tdogl/Program.h"
#include "ModelAsset.h"
#include <gl/glfw.h>
#include <cassert>
#include <iostream>
#include <stdexcept>
#include <cmath>
#include <glm/gtx/compatibility.hpp>

class IRenderable;

const glm::vec2 SCREEN_SIZE(800, 600);

class Graphics
{
public:
	Graphics();
	~Graphics();
	void Initialize(int w, int h);
	void SetUpTriangles(const glm::vec2& size, const std::string& textureName, IRenderable *drawable);
	void Render(IRenderable* drawable);
	void LoadShaders();
	OGL::Program* LoadShaders(const std::string& vertFilename, const std::string& fragFilename);
	OGL::Texture* LoadTexture(const std::string& fileName);
	void Update(float timeElapsed);
	void Start();
	void End();
	glm::vec2 GetWindow() const { return m_window; }
	
protected:
private:
	glm::vec2 m_window;
	glm::mat4 m_camera;
};

#endif