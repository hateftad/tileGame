#ifndef GAMEGRID_H
#define GAMEGRID_H

#include "DebugDrawer.h"
#include "Helpers.h"
#include "PhysicsWorld.h"
#include "Tile.h"
#include "MoveableShape.h"
#include "Timer.h"
#include "Graphics.h"
#include "EventListener.h"
#include "InputManager.h"
#include "Grid.h"
#include "DrawableFactory.h"
#include "Particles.h"
#include "Points.h"
#include <iostream>

class Grid;

typedef std::vector<Tile*>::iterator tItr;
typedef std::vector<IRenderable*>::iterator rItr;

class Game : public EventListener
{
public:

	Game();
	~Game();
	void Generate(Graphics* graphics,float startX, float startY, float w, int widthCount);
	void Initalize(DrawableFactory* df, Graphics* graphics);
	void Swap(int tile1, int tile2);
	bool MovingBoard();
	void Update(Graphics* graphics, float timeElapsed);
	void Draw(Graphics* graphics);
	void CheckMatch();
	bool Exit(){return m_exit;}

	void onKeyPressed(const int &key);
	void onKeyReleased(const int &key){}
	void onMouseMoved(const int &xpos, const int &ypos){};
	void onMouseButtonPressed(const int &xpos, const int &ypos, const int &key);
	void onMouseButtonReleased(const int &xpos, const int &ypos, const int &key){};
	void onMouseWheel(const int &xpos, const int &ypos, const int &wheelpos){}

private:

	

	//--can go in a UI class--
	std::vector<IRenderable*>  m_staticShapes;
	StaticShape* m_timeUp;
	Timer* m_timer;
	Points* m_pointsCounter;
	//-------------
	
	Grid *m_grid;
	Particles *m_particles;
	PhysicsWorld *m_world;
	DebugDrawer *m_debugDrawer;

	Tile *m_tile;
	Tile * m_tiler2;
	StaticShape *m_ground;

	int m_firstTile;
	int m_tile1, m_tile2;

	bool m_swapped;
	bool m_exit;
	float m_lastTime;
};


#endif