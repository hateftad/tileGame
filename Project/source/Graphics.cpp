#include "Graphics.h"
#include "IRenderable.h"

Graphics::Graphics()
{

}

Graphics::~Graphics()
{

}

void Graphics::Initialize(int width, int height)
{
	m_window.x = width;
	m_window.y = height;

	if(!glfwInit())
		throw std::runtime_error("glfwInit failed");


	glfwOpenWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwOpenWindowHint(GLFW_OPENGL_VERSION_MAJOR, 3);
	glfwOpenWindowHint(GLFW_OPENGL_VERSION_MINOR, 3);
	glfwOpenWindowHint(GLFW_WINDOW_NO_RESIZE, GL_TRUE);
	if(!glfwOpenWindow(width, height, 8, 8, 8, 8, 16, 0, GLFW_WINDOW))
		throw std::runtime_error("glfwOpenWindow failed. Can your hardware handle OpenGL 3.2?");


	glewExperimental = GL_TRUE; 
	if(glewInit() != GLEW_OK)
		throw std::runtime_error("glewInit failed");


	while(glGetError() != GL_NO_ERROR) {}


	std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;
	std::cout << "GLSL version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
	std::cout << "Vendor: " << glGetString(GL_VENDOR) << std::endl;
	std::cout << "Renderer: " << glGetString(GL_RENDERER) << std::endl;


	if(!GLEW_VERSION_3_2)
		throw std::runtime_error("OpenGL 3.2 API is not available.");


	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glEnable(GL_BLEND);
	//glDepthMask(GL_TRUE);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	//LoadShaders();
}


OGL::Program* Graphics::LoadShaders( const std::string& vertFilename, const std::string& fragFilename )
{
	std::vector<OGL::Shader> shaders;
	shaders.push_back(OGL::Shader::shaderFromFile(ResourcePath(vertFilename), GL_VERTEX_SHADER));
	shaders.push_back(OGL::Shader::shaderFromFile(ResourcePath(fragFilename), GL_FRAGMENT_SHADER));
	return new OGL::Program(shaders);
}


void Graphics::Render(IRenderable* drawable)
{

	ModelAsset *asset = drawable->GetAsset();
	asset->shaders->use();
	asset->shaders->setUniform("orthoMat4", glm::ortho(0.0f, m_window.x, 0.0f, m_window.y));
	asset->shaders->setUniform("model", glm::translate(glm::mat4(), drawable->GetPosition()));
	asset->shaders->setUniform("scale", glm::scale(glm::mat4(), drawable->GetScale()));
	asset->shaders->setUniform("rotation", glm::rotate(glm::mat4(), glm::degrees(drawable->GetAngle()), glm::vec3(0,0,1)));

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, asset->texture->object());
	asset->shaders->setUniform("tex", 0);

	glBindVertexArray(asset->vao);

	glDrawArrays(asset->drawType, asset->drawStart, asset->drawCount);

	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
	asset->shaders->stopUsing();
}

void Graphics::Update( float timeElapsed )
{

}

void Graphics::Start()
{

	glViewport(0, 0, SCREEN_SIZE.x, SCREEN_SIZE.y);
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Graphics::End()
{
	glfwSwapBuffers();
}

void Graphics::SetUpTriangles( const glm::vec2& size,const std::string& textureName, IRenderable *drawable )
{
	ModelAsset* asset = drawable->GetAsset();
	asset->shaders = LoadShaders("vertex-shader.txt", "fragment-shader.txt");
	asset->drawStart = 0;
	asset->drawCount = 6;
	asset->drawType = GL_TRIANGLES;
	asset->texture = LoadTexture(textureName);
	

	glGenVertexArrays(1, &asset->vao);
	glBindVertexArray(asset->vao);


	glGenBuffers(1, &asset->vbo);
	glBindBuffer(GL_ARRAY_BUFFER, asset->vbo);

	GLfloat vertexData[] = {

		0.0f, 0.0f, 0.0f,		0.0f, 0.0f,
		size.x, 0.0f, 0.0f,		1.0f, 0.0f,
		size.x, size.y, 0.0f,	1.0f, 1.0f,

		0.0f, 0.0f, 0.0f,		0.0f, 0.0f,
		size.x, size.y, 0.0f,	1.0f, 1.0f,
		0.0f, size.y, 0.0f,		0.0f, 1.0f
	};

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);

	glEnableVertexAttribArray(asset->shaders->attrib("vert"));
	glVertexAttribPointer(asset->shaders->attrib("vert"), 3, GL_FLOAT, GL_FALSE, 5*sizeof(GLfloat), 0);

	glEnableVertexAttribArray(asset->shaders->attrib("vertTexCoord"));
	glVertexAttribPointer(asset->shaders->attrib("vertTexCoord"), 2, GL_FLOAT,  GL_TRUE,  5*sizeof(GLfloat), (const GLvoid*)(3 * sizeof(GLfloat)));

	glBindVertexArray(0);
}

OGL::Texture* Graphics::LoadTexture( const std::string& fileName )
{
	OGL::Bitmap bmp = OGL::Bitmap::bitmapFromFile(ResourcePath(fileName));
	bmp.flipVertically();
	return new OGL::Texture(bmp);
}




