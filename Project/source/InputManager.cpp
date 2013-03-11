#include "InputManager.h"
#include <gl/glfw.h>

InputManager *InputManager::instance = 0;

int	InputManager::m_xpos = 0;
int	InputManager::m_ypos = 0;
int	InputManager::m_mouseWheel = 0;
std::vector<EventListener*> InputManager::m_listeners = std::vector<EventListener*>();

InputManager::InputManager()
{

}

InputManager& InputManager::getInstance()
{
	return *getInstancePtr();
}

InputManager* InputManager::getInstancePtr()
{
	if(!instance) instance = new InputManager();
	return instance;
}

void InputManager::initialise()
{	

	glfwSetKeyCallback(InputManager::keyboardCallback);
	glfwSetMousePosCallback(InputManager::mousePosCallback);
	glfwSetMouseButtonCallback(InputManager::mouseButtonCallback);
	glfwSetMouseWheelCallback(InputManager::mouseWheelCallback);

	glfwSetWindowCloseCallback(InputManager::windowClosedCallback);

}

void InputManager::keyboardCallback(int key,int state)
{
	if(state==GLFW_PRESS) {
		for (std::vector<EventListener*>::iterator it = m_listeners.begin(); it != m_listeners.end(); ++it)
		{
			(*it)->onKeyPressed(key);
		}
	}

}

void InputManager::mousePosCallback(int x,int y)
{

	m_xpos = x;
	m_ypos = y;
	for (std::vector<EventListener*>::iterator it = m_listeners.begin(); it != m_listeners.end(); ++it)
	{
		(*it)->onMouseMoved(x, y);
	}

}

void InputManager::mouseButtonCallback(int button,int state)
{

	if(state == GLFW_PRESS)
	{
		for (std::vector<EventListener*>::iterator it = m_listeners.begin(); it != m_listeners.end(); ++it)
		{
			(*it)->onMouseButtonPressed(m_xpos, m_ypos, button);
		}
	}
	else
	{
		for (std::vector<EventListener*>::iterator it = m_listeners.begin(); it != m_listeners.end(); ++it)
		{
			(*it)->onMouseButtonReleased(m_xpos, m_ypos, button);
		}
	}
}

void InputManager::mouseWheelCallback(int pos)
{
	m_mouseWheel = pos;
}

int InputManager::windowClosedCallback()
{

	return GL_TRUE;
}


void InputManager::Attach( EventListener* listener )
{
	if (IsAttached(listener)) return;
	m_listeners.push_back(listener);
}

bool InputManager::IsAttached( EventListener* listener )
{
	if(listener == nullptr) return false;
	for (std::vector<EventListener*>::iterator it = m_listeners.begin(); it != m_listeners.end(); ++it)
	{
		if ((*it) == listener)
		{
			return true;
		}
	}
	return false;
}

void InputManager::Detach( EventListener* listener )
{
	if (listener == nullptr) return;

	for (std::vector<EventListener*>::iterator it = m_listeners.begin(); it != m_listeners.end(); ++it)
	{
		if ((*it) == listener)
		{
			m_listeners.erase(it);
			return;
		}
	}
}
