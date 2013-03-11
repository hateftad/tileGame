#ifndef TILE_H
#define TILE_H


#include "MoveableShape.h"
#include "Animation.h"
#include <map>

enum Colour
{
	BLUE = 1,
	GREEN,
	RED,
	PURPLE,
	YELLOW
};

class Tile : public MoveableShape
{
public:

	Tile(const Tile&);
	const Tile& operator=(const Tile&);
	Tile( std::string fileName, const glm::vec3& pos, const glm::vec2& size );
	~Tile();

	void Update(float timeElapsed);

	bool IsMatched() const { return m_isMatched; }
	void IsMatched(bool val) { m_isMatched = val; }

	void SetTexture(std::string fileName);
	Colour GetColor() const;
	void SetColour(std::string color);


private:

	Colour m_colour;
	bool m_isMatched;
};



#endif