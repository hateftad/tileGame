#ifndef MODELASSET_H
#define MODELASSET_H

#include "Graphics.h"

class ModelAsset
{
public:
	OGL::Program* shaders;
	OGL::Texture* texture;
	GLuint vbo;
	GLuint vao;
	GLenum drawType;
	GLint drawStart;
	GLint drawCount;

	ModelAsset() :
	shaders(NULL),
		texture(NULL),
		vbo(0),
		vao(0),
		drawType(GL_TRIANGLES),
		drawStart(0),
		drawCount(0)
	{}
};
#endif