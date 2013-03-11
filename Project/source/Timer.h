#ifndef TIMER_H
#define TIMER_H

#include "StaticShape.h"
#include "DrawableFactory.h"

class Timer 
{
public:
	Timer(DrawableFactory* df, const int startTime);
	~Timer();
	void Update(float timeElapsed);
	void SetUpTextures();
	bool IsTimeUp(){return m_stop;}
	std::vector<IRenderable*> Shapes() const { return m_shapes; }
	OGL::Texture** GetTextures(){return m_textures;}
protected:
private:
	
	OGL::Texture* m_textures[10];
	std::vector<IRenderable*> m_shapes;
	
	float m_lastSecond;
	float m_lastMinute;
	int m_seconds;
	int m_tenSeconds;
	
	bool m_stop;
};



#endif