#include "Game.h"

#include "Helpers.h"
#include "SoundManager.h"
#include <ctime>
#include <algorithm>




Game::Game( )
{
	InputManager::getInstancePtr()->Attach(this);
	m_swapped = false;
	m_lastTime = 10.0f;
	m_exit = false;
	m_firstTile = -1;
}

void Game::Initalize( DrawableFactory* tf, Graphics* graphics )
{
	m_particles = new Particles("Red.png", glm::vec3(300, 300, 0.0f), 100);
	m_particles->Initialize(graphics);

	SoundManager::Instance()->Initialize("Audio//", "GameSounds.fev");

	//m_world = new PhysicsWorld(b2Vec2(0.0f,-100.8f), true);
	//m_tile = tf->CreateTile("Red.png", glm::vec3(300.0f, 500.0f, 0.0f), glm::vec2(30.0f, 30.0f));
	//m_tiler2 = tf->CreateTile("Red.png", glm::vec3(200.0f, 500.0f, 0.0f), glm::vec2(30.0f, 30.0f));
	//m_ground = tf->CreateStaticShape("Red.png", glm::vec3(0.0f, 100.0f, 0.0f), glm::vec2(6000.0f, 30.0f));

	//m_debugDrawer = new DebugDrawer(graphics);
	
	//m_world->AddBody(m_ground->GetRigidBody());
	//m_world->AddBody(m_tile->GetRigidBody());
	//m_world->AddBody(m_tiler2->GetRigidBody());
	//m_world->SetDebugDrawer(m_debugDrawer);
	//m_debugDrawer->SetFlags(b2Draw::e_aabbBit);


	m_staticShapes.push_back(tf->CreateStaticShape("BackGround.png", glm::vec3(0,0,0.1f), glm::vec2(800,600)));
	m_staticShapes.push_back(tf->CreateMovableShape("spark.png", glm::vec3(260, 30, 0.2f), glm::vec2(40,40)));
	m_staticShapes.push_back(tf->CreateStaticShape("TimeBacks.png", glm::vec3(60, 470, 0.2f), glm::vec2(150,80)));
	m_staticShapes.push_back(tf->CreateStaticShape("PointsBack.png", glm::vec3(60, 370, 0.2f), glm::vec2(150,80)));
	m_timeUp = tf->CreateStaticShape("TimeUp.png", glm::vec3(120, 200, 0.5f), glm::vec2(500, 200));

	m_timer = new Timer(tf, 59);
	std::vector<IRenderable*> shapes = m_timer->Shapes();
	m_staticShapes.insert(m_staticShapes.end(), shapes.begin(), shapes.end());
	shapes.clear();
	m_pointsCounter = new Points(tf, m_timer->GetTextures());
	shapes = m_pointsCounter->Shapes();
	m_staticShapes.insert(m_staticShapes.end(), shapes.begin(), shapes.end());


	SoundManager::Instance()->PlayEvent("Music");
}

void Game::Draw(Graphics* graphics)
{
	
	


	graphics->Start();

	//m_world->GetWorld()->DrawDebugData();

	//m_tile->Render(graphics);
	//m_ground->Render(graphics);
	//m_tiler2->Render(graphics);

	
	//m_particles->Draw();
	
 	for (tItr itr = m_grid->Begin(); itr != m_grid->End(); ++itr)
 	{
 		(*itr)->Render(graphics);
 	}
 
 	for (rItr itr = m_staticShapes.begin(); itr != m_staticShapes.end(); ++itr )
 	{
 		(*itr)->Render(graphics);
 	}
 
 	if (m_timer->IsTimeUp())
 	{
 		graphics->Render(m_timeUp);
 	}
	
	graphics->End();

}

void Game::Update(Graphics* graphics, float timeElapsed )
{
	
	graphics->Update(timeElapsed);
	SoundManager::Instance()->Update();
	m_pointsCounter->Update(timeElapsed);
	//m_world->Update(timeElapsed);
	
	//m_tile->Update(timeElapsed);
	//m_tiler2->Update(timeElapsed);
	
//  	if (m_draw)
//  	{
//  		m_particles->Update(timeElapsed);
//  	}
	
	m_timer->Update(timeElapsed);

	for (tItr itr = m_grid->Begin(); itr != m_grid->End(); ++itr)
	{
		(*itr)->Update(timeElapsed);
	}

	for (rItr itr = m_staticShapes.begin(); itr !=m_staticShapes.end(); ++itr)
	{
		(*itr)->Update(timeElapsed);
	}
	
	if (!MovingBoard())
	{
		if (glfwGetTime() - m_lastTime > 2.f && !m_timer->IsTimeUp())
		{			
			if (m_grid->CheckMatch())
			{
				m_pointsCounter->Add();
			}
			
			m_lastTime = (float) glfwGetTime();
		}
		if (m_swapped)
		{
			CheckMatch();
			m_swapped = false;
		}
 		
	}

}

void Game::Generate(Graphics* graphics,float startX, float startY, float w, int widthCount)
{
	srand((unsigned) 4);
	
	Grid::GridSpace gridSpace;
	gridSpace.startGridX = startX;
	gridSpace.startGridY = startY;
	gridSpace.aboveGridY = 400;
	gridSpace.tileWidth = w;
	gridSpace.widthCount = widthCount;
	gridSpace.topOfGrid = startY;
	
	DrawableFactory* tf = new DrawableFactory(graphics);
	m_grid = new Grid(gridSpace);
	Initalize(tf, graphics);
	m_grid->Initialize(tf);


}



bool Game::MovingBoard()
{
	bool animating = false;
	for (tItr itr = m_grid->Begin(); itr != m_grid->End(); ++itr)
	{
		if((*itr)->IsAnimating())
		{
			animating = true;
			break;
		}
		else
		{
			(*itr)->GetAnimation()->Reset();
			animating = false;
		}
	}
	return animating;
}


void Game::onMouseButtonPressed( const int &xpos, const int &ypos, const int &key )
{
	m_lastTime = (float) glfwGetTime();
	if (m_timer->IsTimeUp())return;
	if (MovingBoard()) return;
	if (key == InputManager::LEFT)
	{
		for(unsigned int i = 0; i < m_grid->GetGrid()->size(); i++)
		{
			if (Utils::TileClick(m_grid->Get(i), xpos, ypos))
			{
				if(i != m_firstTile && m_firstTile >= 0)
				{
					Swap(m_firstTile, i);
					m_firstTile = -1;
					break;
				}
				else
				{
					m_firstTile = i;
					break;
				}
			}

		}
		
	}

}

void Game::CheckMatch()
{
	if (m_tile1 < 0 || m_tile2 < 0) return;
	Tile* t1 = m_grid->Get(m_tile1);
	Tile* t2 = m_grid->Get(m_tile2);

	glm::vec3 pos1 = t1->GetPosition();
	glm::vec3 pos2 = t2->GetPosition();

	m_grid->Swap(m_tile1, m_tile2);
	
	bool match = m_grid->CheckMatch();

	if (!match)
	{
		t1->GetAnimation()->PlayAnimation(Animation::MATCH, pos1, pos2);
		t2->GetAnimation()->PlayAnimation(Animation::MATCH, pos2, pos1);
		t1->Animate(true);
		t2->Animate(true);
		m_grid->Swap(m_tile2, m_tile1);
		match= false;
	}
	else
		m_pointsCounter->Add();
	t1 = nullptr;
	t2 = nullptr;
	m_tile1 = -1;
	m_tile2 = -1;
	
	
}

void Game::Swap(int tile1, int tile2)
{
	Tile* t1 = m_grid->Get(tile1);
	Tile* t2 = m_grid->Get(tile2);

	glm::vec3 pos1 = t1->GetPosition();
	glm::vec3 pos2 = t2->GetPosition();

	if (Utils::ValidMove(t1, t2))
	{
		m_tile1 = tile1;
		m_tile2 = tile2;
		t1->GetAnimation()->PlayAnimation(Animation::MATCH, pos1, pos2);
		t2->GetAnimation()->PlayAnimation(Animation::MATCH, pos2, pos1);
		t1->Animate(true);
		t2->Animate(true);
		m_swapped = true;
	}

}


void Game::onKeyPressed( const int &key )
{
	//developed on a mac, so keys might be different
	if (m_timer->IsTimeUp())
	{
		if (key == 257)
		{
			m_exit = true;
		}
		if (key == 27)
		{
			m_exit = true;
		}

	}
	/*
	if (key == 65)
	{
		
		m_tile->GetRigidBody()->GetBody()->SetAngularVelocity(10.0f);
	}
	if (key == 68)
	{
		b2Vec2 vel = m_tile->GetRigidBody()->GetBody()->GetLinearVelocity();
		vel += b2Vec2(0, -500.0f);
		m_tile->GetRigidBody()->GetBody()->SetLinearVelocity(vel);
	}
	std::cout << key <<std::endl;
	*/
}

Game::~Game()
{

	delete m_grid;
	//delete m_timer;
	delete m_timeUp;
	SoundManager::Instance()->Destroy();

}



