#include "basicenemy.h"
#include "player.h"
#include "../GameState/level.h"
#include "../Main/fission.h"

using namespace sparky;
using namespace maths;
using namespace audio;

BasicEnemy::BasicEnemy(float x, float y, float width, float height, sparky::graphics::Window* window)
    : Entity(x, y), m_Window(window), m_Group(new graphics::Group(mat4::identity())), m_Transformation(m_Group->getTransformRef())
{
    m_Sprite = new graphics::Sprite(x, y, width, height, graphics::TextureManager::get("Red"));
    int negX = 1;
    int negY = 1;
    if (rand() % 2 == 0)
        negX = -1;
    if (rand() % 10 < 5)
        negY = -1;
    m_Group->position = m_Sprite->getPosition();
    m_Group->add(m_Sprite);
    m_PosSpin = false;
    m_HitCount = 0;
    m_Renderable = m_Group;
    m_Flinching = false;
    moveX = 7 + rand() % 8 * negX;
    moveY = 10 + rand() % 8 * negY;
    m_Type = ENEMY;
    j = 0.0f;
}

BasicEnemy::BasicEnemy(float x, float y, sparky::graphics::Window* window)
: Entity(x, y), m_Window(window), m_Group(new graphics::Group(mat4::identity())), m_Transformation(m_Group->getTransformRef())
{
    m_Sprite = new graphics::Sprite(x, y, 64, 64, graphics::TextureManager::get("Red"));
    int negX = 1;
    int negY = 1;
    if (rand() % 2 == 0)
        negX = -1;
    if (rand() % 10 < 5)
        negY = -1;
    
    m_Group->add(m_Sprite);
    m_PosSpin = false;
    m_HitCount = 0;
    m_Renderable = m_Group;
    m_Flinching = false;
    moveX = 7 + rand() % 8 * negX;
    moveY = 10 + rand() % 8 * negY;
    m_Type = ENEMY;
    j = 0.0f;
}

void BasicEnemy::update()
{
    j += 5;
    
    m_Group->position.x = m_Group->position.x + moveX;
    m_Group->position.y = m_Group->position.y + moveY;
    m_Sprite->setPosition(m_Group->getPosition());
    setPosition(m_Group->position.x, m_Group->position.y);
    
    if (m_Group->getPosition().x > m_Window->getWidth() - getSize().x)
    {
        moveX = -moveX;
    }
    if (m_Group->getPosition().x < 0)
    {
        m_Group->p_Position.x = 0;
        moveX = -moveX;
    }
    if (m_Group->getPosition().y > m_Window->getHeight() - m_Sprite->getSize().y)
    {
        m_Group->p_Position.y = m_Window->getHeight() - m_Sprite->getSize().y;
        moveY = -moveY;
    }
    if (m_Group->getPosition().y < 0)
    {
        m_Group->p_Position.y = 0;
        moveY = -moveY;
    }
    
    for (int i = 0; i < m_Level->m_Betas.size(); i++)
    {
        if (collided(m_Level->getBeta(i)))
            m_HitCount++;
    }
    
    if (m_HitCount % 2 == 0 && m_PosSpin == false)
    {
        toggleMoment(m_Moment);
        m_PosSpin = true;
        
    }
    else if (m_HitCount % 2 != 0 && m_PosSpin == true)
    {
        m_Group->remove(m_Moment->getRenderable());
    }
    
     if (m_PosSpin)
        m_Moment->update();
}

void BasicEnemy::render()
{
    getRenderable();
}

void BasicEnemy::toggleMoment(Moment* moment)
{
    moment = new Moment(128, 128, this, m_Window);
    m_Moment = moment;
    m_Group->add(moment->getRenderable());
}

void BasicEnemy::setPosition(float x, float y)
{
    m_Position.x = x;
    m_Position.y = y;
}