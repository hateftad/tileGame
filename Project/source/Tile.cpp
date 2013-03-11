#include "Tile.h"
#include "Helpers.h"
#include <gl/glfw.h>

static std::map<std::string, Colour> m_colours;


Tile::Tile( std::string fileName, const glm::vec3& pos, const glm::vec2& size ) : MoveableShape(fileName, pos, size)
{
	m_colours["Red.png"] = RED;
	m_colours["Green.png"] = GREEN;
	m_colours["Yellow.png"] = YELLOW;
	m_colours["Purple.png"] = PURPLE;
	m_colours["Blue.png"] = BLUE;
	
	m_animation = new Animation();
	//m_body = new RigidBody(Utils::Vec3TobVec(pos),Utils::Vec2TobVec(size), b2_dynamicBody, 1.0f, 0.3f);

	m_setToMove = false;
	m_isMatched = false;

	m_animate = false;
	SetColour(fileName);

}

Tile::~Tile()
{
	delete m_animation;
}

void Tile::Update(float timeElapsed  )
{
	//m_position = Utils::bVecToVec3(m_body->GetBody()->GetPosition(), m_zdepth);
	//m_angle = m_body->GetBody()->GetAngle();
	//std::cout << " x : " << m_position.x << "  y : "<< m_position.y << std::endl;
	if (m_animate)
	{
		m_animation->Animate(this, timeElapsed);
	}
	
}

Colour Tile::GetColor() const
{
	return m_colour;
}

void Tile::SetColour( std::string color )
{
	switch (m_colours[color])
	{
	case RED:
		m_colour = RED;
		break;
	case BLUE:
		m_colour = BLUE;
		break;
	case YELLOW:
		m_colour = YELLOW;
		break;
	case PURPLE:
		m_colour = PURPLE;
		break;
	case GREEN:
		m_colour = GREEN;
		break;
	default:
		break;
	}
}

void Tile::SetTexture( std::string fileName )
{
	LoadTexture(fileName);
	SetColour(fileName);
}
