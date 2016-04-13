#include "beta.h"
#include "basicenemy.h"
#include "player.h"
#include "../GameState/level.h"
#include "../Main/fission.h"

using namespace sparky;
using namespace maths;
using namespace audio;


Beta::Beta(float x, float y, sparky::graphics::Window* window)
: Entity(x, y), m_Window(window)
{
    m_Sprite = new graphics::Sprite(x, y, 16, 16, graphics::TextureManager::get("Purple"));
    int negX = 1;
    int negY = 1;
    if (rand() % 2 == 0)
        negX = -1;
    if (rand() % 10 < 5)
        negY = -1;
    
    moveX = 10 + rand() % 8 * negX;
    moveY = 10 + rand() % 8 * negY;
    m_Renderable = m_Sprite;
    m_Type = BETA;
}

void Beta::update()
{
    m_Sprite->p_Position.x = m_Sprite->p_Position.x + moveX;
    m_Sprite->p_Position.y = m_Sprite->p_Position.y + moveY;
 
    setPosition(m_Sprite->p_Position.x, m_Sprite->p_Position.y);
    
    if (m_Sprite->getPosition().x > m_Window->getWidth() - m_Sprite->getSize().x)
    {
    }
    if (m_Sprite->getPosition().x < 0)
    {
    }
    if (m_Sprite->getPosition().y > m_Window->getHeight() - m_Sprite->getSize().y)
    {
    }
    if (m_Sprite->getPosition().y < 0)
    {
    }
}

void Beta::render()
{
    getRenderable();
}


void Beta::setPosition(float x, float y)
{
    m_Position.x = x;
    m_Position.y = y;
}