#ifndef EVENTLISTENER_H
#define EVENTLISTENER_H


class EventListener
{
public:
	virtual void onKeyPressed(const int &key) = 0;
	virtual void onKeyReleased(const int &key) = 0;
	virtual void onMouseMoved(const int &xpos, const int &ypos) = 0;
	virtual void onMouseButtonPressed(const int &xpos, const int &ypos, const int &key) = 0;
	virtual void onMouseButtonReleased(const int &xpos, const int &ypos, const int &key) = 0;
	virtual void onMouseWheel(const int &xpos, const int &ypos, const int &wheelpos) = 0;
};


#endif