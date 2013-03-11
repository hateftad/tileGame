#include "Timer.h"

void Timer::SetUpTextures()
{
	OGL::Bitmap bmp = OGL::Bitmap::bitmapFromFile(ResourcePath("zero.png"));
	bmp.flipVertically();
	m_textures[0] = new OGL::Texture(bmp);

	bmp = OGL::Bitmap::bitmapFromFile(ResourcePath("one.png"));
	bmp.flipVertically();
	m_textures[1] = new OGL::Texture(bmp);
	
	bmp = OGL::Bitmap::bitmapFromFile(ResourcePath("two.png"));
	bmp.flipVertically();
	m_textures[2] = new OGL::Texture(bmp);

	bmp = OGL::Bitmap::bitmapFromFile(ResourcePath("three.png"));
	bmp.flipVertically();
	m_textures[3] = new OGL::Texture(bmp);

	bmp = OGL::Bitmap::bitmapFromFile(ResourcePath("four.png"));
	bmp.flipVertically();
	m_textures[4] = new OGL::Texture(bmp);

	bmp = OGL::Bitmap::bitmapFromFile(ResourcePath("five.png"));
	bmp.flipVertically();
	m_textures[5] = new OGL::Texture(bmp);

	bmp = OGL::Bitmap::bitmapFromFile(ResourcePath("six.png"));
	bmp.flipVertically();
	m_textures[6] = new OGL::Texture(bmp);

	bmp = OGL::Bitmap::bitmapFromFile(ResourcePath("seven.png"));
	bmp.flipVertically();
	m_textures[7] = new OGL::Texture(bmp);

	bmp = OGL::Bitmap::bitmapFromFile(ResourcePath("eight.png"));
	bmp.flipVertically();
	m_textures[8] = new OGL::Texture(bmp);

	bmp = OGL::Bitmap::bitmapFromFile(ResourcePath("nine.png"));
	bmp.flipVertically();
	m_textures[9] = new OGL::Texture(bmp);

}

Timer::Timer(DrawableFactory* tf, const int startTime)
{

	m_shapes.push_back(tf->CreateStaticShape("five.png", glm::vec3(142, 478, 0.3f), glm::vec2(30,30)));//left
	m_shapes.push_back(tf->CreateStaticShape("nine.png", glm::vec3(171, 478, 0.3f), glm::vec2(30,30)));//right
	
	SetUpTextures();

	m_lastSecond= (float) glfwGetTime();
	m_lastMinute = (float) glfwGetTime() - 1.f;
	m_seconds = startTime;
	m_tenSeconds = m_seconds / 10;
	m_stop = false;
}

Timer::~Timer()
{

}

void Timer::Update( float timeElapsed )
{
	if (m_seconds == 0)
	{
		m_stop = true;
		return;
	}
	
	if (glfwGetTime() - m_lastMinute > 11.1f)
	{
		m_tenSeconds--;
		m_shapes.at(0)->SetTexture(m_textures[m_tenSeconds]);
		m_lastMinute = (float) glfwGetTime() - 1.0f;
	}

	if (glfwGetTime() - m_lastSecond > 1.0f)
	{
		m_seconds--;
		m_shapes.at(1)->SetTexture(m_textures[m_seconds % 10]);
		m_lastSecond = (float) glfwGetTime();
	}
	

}
