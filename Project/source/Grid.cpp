
#include "Grid.h"
#include <iostream>
#include <algorithm>
#include "Helpers.h"
#include "SoundManager.h"


Grid::Grid( GridSpace gspace )
{

	m_gridSpace = gspace;
}

Grid::~Grid()
{

}

bool Grid::CheckMatch(bool correct)
{

	bool onlyDown = false;
	bool onlyForward = false;
	bool match = false;
	int stopIndex = (m_gridSpace.widthCount*m_gridSpace.widthCount) - 2;

	for (unsigned int i = 0; i < m_grid.size(); i++)
	{

		if (i == stopIndex )
		{
			break;
		}
		if ((i != 0) &&  (((i % m_gridSpace.widthCount) == 6)) || (((i % m_gridSpace.widthCount) == 7)))
		{
			onlyDown = true;
		}
		if ((i / m_gridSpace.widthCount) == 6 )
		{
			onlyForward = true;
		}
		if (!onlyDown)//forward
		{
			if(CheckMatch(m_grid.at(i), m_grid.at(i+1)))
			{
				if(CheckMatch(m_grid.at(i), m_grid.at(i+1), m_grid.at(i+2)))
				{
					if (correct)
					{
						m_grid.at(i+1)->SetTexture(Utils::Randomize(i+1*2));
						m_grid.at(i+2)->SetTexture(Utils::Randomize(i*2));
					}						
					else
					{
						Matched(i, i+1, i+2, 0, 0 , true);
						match = true;
						break;
					}
				}
			}
		}
		if (!onlyForward)//down
		{
			if (CheckMatch(m_grid.at(i), m_grid.at(i+8)))
			{
				if(CheckMatch(m_grid.at(i), m_grid.at(i+8), m_grid.at(i+16)))
				{
					if (correct)
					{
						m_grid.at(i+8)->SetTexture(Utils::Randomize(i*2));
					}
					else
					{
						Matched(i, i+8, i+16, 0, 0, false);
						match = true;
						break;
					}
				}

			}
		}

		onlyDown = false;
	}

	return match;
}

bool Grid::CheckMatch( Tile* t1, Tile* t2 )
{
	if ((t1->GetColor() == t2->GetColor() && 
		t2->GetColor() == t1->GetColor()))
	{
		return true;
	}
	return false;
}

bool Grid::CheckMatch( Tile* t1, Tile* t2, Tile* t3 )
{
	if ((t1->GetColor() == t2->GetColor() && 
		t2->GetColor() == t3->GetColor() && 
		t1->GetColor() == t3->GetColor()))
	{
		return true;
	}

	return false;
}

void Grid::Swap( int idx1, int idx2 )
{
	std::swap(m_grid.at(idx1), m_grid.at(idx2));
	
}

std::vector<Tile*>* Grid::GetGrid()
{
	return &m_grid;
}

Tile* Grid::Get( int idx )
{
	return m_grid.at(idx);
}

void Grid::Matched(const int idx1,const int idx2,const int idx3,const int idx4,const int idx5, bool horizontal)
{
	int width = m_gridSpace.widthCount;

	SoundManager::Instance()->StopEvent("Drop");
	SoundManager::Instance()->PlayEvent("Match");

	TheMatchedOnes(idx1, idx2,idx3, 0,0, horizontal);
	int ind1 =0, ind2 =0, ind3=0;
	if (horizontal)
	{
		//can be done recursively
		for (unsigned int i = m_grid.size(); i > 0; i--)
		{

			if ((i / m_gridSpace.widthCount) == 0)
			{
				break;
			}
			
			if (i == idx3 || i == ind3)
			{
				Tile* above = m_grid.at(i-width);
				Tile* below = m_grid.at(i);
				above->SetToMove(true);
				below->SetToMove(true);
				above->GetAnimation()->PlayAnimation(Animation::MATCH, above->GetPosition(), below->GetPosition());
				ind3 = i - width;
			}
			
			if (i == idx2 || i == ind2)
			{
				Tile* aboves = m_grid.at(i-width);
				Tile* belows = m_grid.at(i);
				aboves->SetToMove(true);
				belows->SetToMove(true);
				aboves->GetAnimation()->PlayAnimation(Animation::MATCH, aboves->GetPosition(), belows->GetPosition());
				ind2 = i - width;
			}
			if (i == idx1 || i == ind1)
			{
				Tile* above = m_grid.at(i-width);
				Tile* below = m_grid.at(i);
				above->SetToMove(true);
				below->SetToMove(true);
				above->GetAnimation()->PlayAnimation(Animation::MATCH, above->GetPosition(), below->GetPosition());
				ind1 = i - width;

			}
		}

		ind1 = idx1; ind2 = idx2; ind3 = idx3;
		for (unsigned int x = m_grid.size(); x > 0; x--)
		{
			if ((x / m_gridSpace.widthCount) == 0)
			{
				break;
			}
			if (x == ind1)
			{
				std::swap(m_grid.at(x), m_grid.at(x-width));
				ind1 = x - width;

			}
			if (x == ind2)
			{
				std::swap(m_grid.at(x), m_grid.at(x-width));
				ind2 = x - width;
			}
			if (x == ind3)
			{
				std::swap(m_grid.at(x), m_grid.at(x-width));
				ind3 = x - width;
			}

		}

	}

	if (!horizontal)
	{

		ind1 =0, ind2 =0, ind3=0;
		int leWidth = (width * 3); 


		for (unsigned int z = m_grid.size(); z > 0; z--)
		{
			if ((z / m_gridSpace.widthCount) == 2)
			{
				break;
			}
			if (z == idx3 || z == ind3)
			{
					Tile* above = m_grid.at(z-leWidth);
					Tile* below = m_grid.at(z);
					above->SetToMove(true);
					below->SetToMove(true);
					above->GetAnimation()->PlayAnimation(Animation::MATCH, above->GetPosition(), below->GetPosition());
					ind3 = z - leWidth;
			}
			if (z == idx2 || z == ind2)
			{
				Tile* above = m_grid.at(z-leWidth);
				Tile* below = m_grid.at(z);
				above->SetToMove(true);
				below->SetToMove(true);
				above->GetAnimation()->PlayAnimation(Animation::MATCH, above->GetPosition(), below->GetPosition());
				ind2 = z - leWidth;
			}
			if (z == idx1 || z == ind1)
			{
				Tile* above = m_grid.at(z-leWidth);
				Tile* below = m_grid.at(z);
				above->SetToMove(true);
				below->SetToMove(true);
				above->GetAnimation()->PlayAnimation(Animation::MATCH, above->GetPosition(), below->GetPosition());
				ind1 = z - leWidth;
			}

		}
		ind1 = idx1; ind2 = idx2; ind3 = idx3;
		
		for (unsigned int j = 0; j < m_grid.size(); j++)
		{
			if ((ind1 / m_gridSpace.widthCount) == 0) break;
			if (j == ind1)
			{
				Swapper(ind1, ind1 - width, 0);
			}
			
			if (j == ind2)
			{
				Swapper(ind2, ind2 - width, 1);
			}
			if (j == ind3)
			{
				Swapper(ind3, ind3 - width, 2);
			}

		}

	}
	
	for (unsigned int f = 0; f < m_grid.size(); f++)
	{
		if (m_grid.at(f)->IsSetToMove())
		{
			m_grid.at(f)->Animate(true);
			m_grid.at(f)->SetToMove(false);

		}
		if (m_grid.at(f)->IsMatched())
		{
			m_grid.at(f)->SetTexture(Utils::Randomize(f*2));
			m_grid.at(f)->IsMatched(false);
		}
	}
	
}

void Grid::Swapper( int from, int to, int stopRow )
{
	
	Swap(from, to);
	if ((to / m_gridSpace.widthCount) == stopRow) return;
	Swapper(from - m_gridSpace.widthCount, to - m_gridSpace.widthCount, stopRow);
}


void Grid::TheMatchedOnes(const int idx1,const int idx2,const int idx3,const int idx4 /*= 0*/,const int idx5 /*= 0*/ , bool horizontal)
{

	Tile *t1 = m_grid.at(idx1);
	Tile *t2 = m_grid.at(idx2);
	Tile *t3 = m_grid.at(idx3);

	float w = t1->GetDimension().y;	
	float topOfGrid =(float) m_gridSpace.topOfGrid;
	glm::vec3 pos1 = glm::vec3();
	glm::vec3 pos2 = glm::vec3(); 
	glm::vec3 pos3 = glm::vec3();

	pos1 = t1->GetPosition();//top
	pos2 = t2->GetPosition();//middle
	pos3 = t3->GetPosition();//bottom
	
	t1->IsMatched(true);
	t2->IsMatched(true);
	t3->IsMatched(true);

	t1->GetAnimation()->PlayAnimation(Animation::SCALE,glm::vec3(), glm::vec3() , 1.f);
	t2->GetAnimation()->PlayAnimation(Animation::SCALE,glm::vec3(), glm::vec3(), 1.7f);
	t3->GetAnimation()->PlayAnimation(Animation::SCALE,glm::vec3(), glm::vec3(), 1.7f);

	if (!horizontal)
	{
		pos1.y = (topOfGrid);
		pos2.y = (topOfGrid - w);
		pos3.y = (topOfGrid - (w *2));

		t1->GetAnimation()->QueueAnim(glm::vec3(pos1.x,510,0), pos1 , 1.4f);
		t2->GetAnimation()->QueueAnim(glm::vec3(pos2.x,510,0), pos2 , .9f);
		t3->GetAnimation()->QueueAnim(glm::vec3(pos3.x,510,0), pos3 , .3f);
	}
	else
	{
		t1->GetAnimation()->QueueAnim(glm::vec3(pos1.x,510,0), glm::vec3(pos1.x, m_gridSpace.topOfGrid , 0) , .3f);
		t2->GetAnimation()->QueueAnim(glm::vec3(pos2.x,510,0), glm::vec3(pos2.x, m_gridSpace.topOfGrid, 0) , .3f);
		t3->GetAnimation()->QueueAnim(glm::vec3(pos3.x,510,0), glm::vec3(pos3.x, m_gridSpace.topOfGrid, 0) , .3f);
	}

	t1->Animate(true);
	t2->Animate(true);
	t3->Animate(true);
	t1 = nullptr;
	t2 = nullptr;
	t3 = nullptr;
}

std::vector<Tile*>::iterator Grid::End()
{
	return m_grid.end();
}

std::vector<Tile*>::iterator Grid::Begin()
{
	return m_grid.begin();
}

void Grid::Initialize(DrawableFactory* df)
{
	float wid = m_gridSpace.tileWidth;
	int xpos = m_gridSpace.startGridX;
	int ypos = m_gridSpace.startGridY;
	for (int i= 0; i < 8; i++)
	{
		for (int x = 0; x < 8; x++)
		{
			m_grid.push_back(df->CreateTile(Utils::Randomize(x), glm::vec3(xpos,ypos,0), glm::vec2(wid,wid)));
			xpos += wid;
		}
		ypos -= wid;
		xpos = m_gridSpace.startGridX;
	}
	CheckMatch(true);
}




