#include "alpha.h"
#include "basicenemy.h"
#include "player.h"
#include "../GameState/level.h"
#include "../Main/fission.h"

using namespace sparky;
using namespace maths;
using namespace audio;


Alpha::Alpha(float x, float y, sparky::graphics::Window* window)
: Entity(x, y), m_Window(window)
{
    m_Sprite = new graphics::Sprite(x, y, 32, 32, graphics::TextureManager::get("Blue"));
    
    moveX = 10 + rand() % 8;
    moveY = 10 + rand() % 8;
    
    
    m_Renderable = m_Sprite;
    m_Type = ALPHA;
}

void Alpha::update()
{
    
    m_Sprite->p_Position.x = m_Sprite->p_Position.x + moveX;
    m_Sprite->p_Position.y = m_Sprite->p_Position.y + moveY;
    m_Position.y = m_Position.y + moveY;
    
    
    
    setPosition(m_Sprite->p_Position.x, m_Sprite->p_Position.y);
    
    if (m_Sprite->getPosition().x > m_Window->getWidth() - m_Sprite->getSize().x)
    {
        remove();
    }
    if (m_Sprite->getPosition().x < 0)
    {
        remove();
    }
    if (m_Sprite->getPosition().y > m_Window->getHeight() - m_Sprite->getSize().y)
    {
        remove();
    }
    if (m_Sprite->getPosition().y < 0)
    {
        remove();
    }
}

void Alpha::render()
{
    getRenderable();
}


void Alpha::setPosition(float x, float y)
{
    m_Sprite->p_Position.x = x;
    m_Sprite->p_Position.y = y;
}