
#ifndef HELPER_H
#define HELPER_H

#include <Windows.h>
#include <iostream>
#include "Tile.h"
#include <Box2D/Box2D.h>

namespace Utils
{
	static inline b2Vec2 Vec2TobVec(const glm::vec2& inVec )
	{
		return b2Vec2(inVec.x, inVec.y);
	}
	static inline b2Vec2 Vec3TobVec(const glm::vec3& inVec )
	{
		return b2Vec2(inVec.x, inVec.y);
	}
	static inline glm::vec3 bVecToVec3(const b2Vec2& inVec, float z )
	{
		return glm::vec3(inVec.x, inVec.y, z);
	}
// 	static inline b2Vec2 Vec3TobVec(const glm::vec3& inVec )
// 	{
// 		return b2Vec2(inVec.x, inVec.y);
// 	}


	static inline bool IsDiagonal( const glm::vec3& pos1, const glm::vec3& pos2 )
	{
		if(pos1.y < pos2.y && pos1.x < pos2.x) return true;
		if(pos1.y < pos2.y && pos1.x > pos2.x) return true;
		if(pos1.y > pos2.y && pos1.x > pos2.x) return true;
		if(pos1.y > pos2.y && pos1.x < pos2.x) return true;

		return false;
	}


	static inline bool ValidMove( const Tile *tile1 , const Tile* tile2)
	{
		const glm::vec3 pos1 = tile1->GetPosition();
		const glm::vec3 pos2 = tile2->GetPosition();

		const glm::vec2 dim1 = tile1->GetDimension();
		const glm::vec2 dim2 = tile2->GetDimension();

		if (Utils::IsDiagonal(pos1, pos2)) return false;

		float left1, left2;
		float right1, right2;
		float top1, top2;
		float bottom1, bottom2;

		left1 = pos1.x;
		left2 = pos2.x;
		right1 = pos1.x + (dim1.x);
		right2 =  pos2.x + dim2.x;
		top1 =  pos1.y - (dim1.y );
		top2 =  pos2.y;
		bottom1 =  pos1.y + (dim1.y);
		bottom2 =  pos2.y;


		if (bottom1 < top2) return false;
		if (top1 > bottom2) return false;

		if (right1 < left2) return false;
		if (left1 > right2) return false;

		return true;

	}


	static inline Animation::Direction MoveType( const glm::vec3& pos1, const glm::vec3& pos2 )
	{
		if (pos1.x > pos2.x)
		{
			return Animation::LEFT;
		}
		if (pos1.x < pos2.x)
		{
			return Animation::RIGHT;
		}
		if (pos1.y > pos2.y)
		{
			return Animation::UP;
		}
		if (pos1.y < pos2.y)
		{
			return Animation::DOWN;
		}
		return Animation::STILL;
	}

	static inline Animation::Direction Opposite( Animation::Direction d )
	{
		switch (d)
		{
		case Animation::LEFT:
			return Animation::RIGHT;
		case Animation::RIGHT:
			return Animation::LEFT;
		case Animation::UP:
			return Animation::DOWN;
		case Animation::DOWN:
			return Animation::UP;
		default:
			break;
		}
	}

	static inline bool TileClick( const Tile* tile, const int& xpos, const int& ypos )
	{
		int y = 600;
		int yposition =  y - ypos;
		int xposition = xpos;
		float left;
		float right;
		float top;
		float bottom;
		glm::vec2 dim = tile->GetDimension();
		glm::vec3 pos = tile->GetPosition();

		left = pos.x;
		right = pos.x + dim.x;
		top = pos.y + dim.y;
		bottom = pos.y;

		if(yposition < bottom) return false;
		if(yposition > top) return false;
		if(xposition > right) return false;
		if(xposition < left) return false;

		return true;
	}

	static inline std::string Randomize(int ind)
	{

		int random_integer = 1; 
		int lowest=1, highest=5; 
		int range=(highest-lowest)+1; 
		for(int index=0; index<ind+1; index++){ 
			random_integer = lowest+int(range*rand()/(RAND_MAX + 1.0));  
		} 

		switch (random_integer)
		{
		case 1:
			return "Purple.png";
		case 2:
			return "Blue.png";
		case 3:
			return "Yellow.png";
		case 4:
			return "Red.png";
		case 5:
			return "Green.png";
		default:
			break;
		}

		return "";
	}

	static inline bool AtPosition(IRenderable* object, const glm::vec3& pos, const glm::vec3& direction)
	{
		bool atStop = false;
		if(glm::length(object->GetPosition() - pos ) < 10.f)
		{
			atStop = true;
		}
		return atStop;
	}

	static inline glm::vec3 Direction(const glm::vec3& from, const glm::vec3& to )
	{

		switch(Utils::MoveType(from, to))
		{
		case Animation::LEFT:
			return glm::vec3(-80.0f,0.0f,0.0f);
			break;
		case Animation::RIGHT:
			return glm::vec3(80.0f,0.0f,0.0f);
			break;
		case Animation::UP:
			return glm::vec3(0.0f,-80.0f,0.0f);
			break;
		case Animation::DOWN:
			return glm::vec3(0.0f,80.0f,0.0f);
			break;
		default:
			break;
		}
		return glm::vec3();
	}

	static inline glm::vec3 SetAtTop(const glm::vec3& pos)
	{
		return glm::vec3(pos.x, 500, 0);
	}

}
#endif