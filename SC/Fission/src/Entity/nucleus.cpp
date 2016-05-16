#include "nucleus.h"
#include "player.h"
#include "../GameState/level.h"
#include "../Main/fission.h"

using namespace sparky;
using namespace maths;
using namespace audio;

Nucleus::Nucleus(float x, float y, float width, float height, bool isTop, sparky::graphics::Window* window)
	: Entity(x, y, window), m_Window(window), m_Group(new graphics::Group(mat4::identity())), m_Transformation(m_Group->getTransformRef()), m_IsTop(isTop)
{
    m_Sprite = new graphics::Sprite(x, y, width, height, graphics::TextureManager::get("Red"));
    int negX = 1;
    int negY = 1;
    if (rand() % 2 == 0)
        negX = -1;
    if (rand() % 10 < 5)
        negY = -1;
	m_Removed = false;
	m_Group->add(m_Sprite);
    m_Renderable = m_Group;
    m_Flinching = false;
	moveX = 5 + rand() % 8 * negX;
	moveY = 5 + rand() % 8 * negY;
    m_Type = ENEMY;
}

void Nucleus::update()
{   
    m_Position.x = m_Position.x + moveX;
    m_Position.y = m_Position.y + moveY;
	m_Sprite->setPosition(m_Position);
	
    if (m_Position.x > (m_Window->getWidth() - 26) - getSize().x)
    {
        moveX = -moveX;
    }
	if (m_Position.x < 30)
    {
        m_Position.x = 30;
        moveX = -moveX;
    }

	if (m_IsTop)
	{
		if (m_Position.y > (m_Window->getHeight() - (46 + m_Sprite->getSize().y)))
		{
			m_Position.y = (m_Window->getHeight() - (46 + m_Sprite->getSize().y));
			moveY = -moveY;
		}
		if (m_Position.y < m_Window->getHeight() / 2)
		{
			m_Position.y = m_Window->getHeight() / 2;
			moveY = -moveY;
		}
	}
	else
	{
		if (m_Position.y > (m_Window->getHeight() / 2) - (m_Sprite->getSize().y))
		{
			m_Position.y = (m_Window->getHeight() / 2) - (m_Sprite->getSize().y);
			moveY = -moveY;
		}
		if (m_Position.y < 38)
		{
			m_Position.y = 38;
			moveY = -moveY;
		}
	}
}

void Nucleus::render()
{
    getRenderable();
}

void Nucleus::setPosition(float x, float y)
{
    m_Position.x = x;
    m_Position.y = y;
}