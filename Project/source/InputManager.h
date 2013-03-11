#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include <iostream>
#include <glm/glm.hpp>
#include <algorithm>
#include <vector>
#include "EventListener.h"



class InputManager
{
public:
	enum MouseButton
	{
		LEFT = 0,
		RIGHT,
		MIDDLE
	};

	static InputManager& getInstance();
	static InputManager* getInstancePtr();
	void initialise();

	void Attach(EventListener* listener);
	bool IsAttached(EventListener* listener);
	void Detach(EventListener* listener);

private:
	static InputManager *instance;

	static int m_xpos;
	static int m_ypos;
	static int m_mouseWheel;
	InputManager();
	~InputManager();
	static void keyboardCallback(int key,int state);
	static void mousePosCallback(int x,int y);
	static void mouseButtonCallback(int key,int state);
	static void mouseWheelCallback(int pos);
	static int windowClosedCallback();
	static std::vector<EventListener*> m_listeners;
};


#endif