#include "player.h"
#include "../GameState/level.h"
#include "../Main/fission.h"

using namespace sparky;
using namespace maths;
using namespace audio;

Player::Player (float x, float y, sparky::graphics::Window* window)
: Entity(x, y), m_Window(window), m_Speed(300.0f), m_Group(new graphics::Group(mat4::identity())), m_Transformation(m_Group->getTransformRef())
{
    m_Sprite = new graphics::Sprite(0, 0, 32, 32, graphics::TextureManager::get("Green"));
    m_Delta = maths::vec2(0, 0);
    m_ScreenPos = vec3(0, 0, 0);
    moveY = 10;
    moveX = 10;
    m_Transformation = mat4::translation(m_Position);
    m_Group->add(m_Sprite);
    m_Flinching = false;
    m_Hit = false;
    
    m_Renderable = m_Group;
    m_Type = PLAYER;
    
    m_PosSpin = false;
    j = 0.0;
    
}

void Player::update()
{
    m = 20.0f;
    j += 5;
    
    setPosition(m_Sprite->getPosition().x, m_Sprite->getPosition().y);
    m_Group->position = m_Position;
    if (m_Window->isKeyPressed(GLFW_KEY_W))
    {

        if (m_Sprite->getPosition().y > m_Window->getHeight() - (1.3 * m_Sprite->getSize().y))
            m = 0.0f;
        
        m_Sprite->p_Position.y += m;
        m_Delta.y += m;
    }
    else if (m_Window->isKeyPressed(GLFW_KEY_S))
    {
     
        if (m_Sprite->getPosition().y <  m_Sprite->getSize().y)
            m = 0.0f;
            
        m_Sprite->position.y -= m;
        m_Delta.y -= m;
    }
    
    if (m_Window->isKeyPressed(GLFW_KEY_A))
    {
        if (m_Sprite->getPosition().x < m_Sprite->getSize().x)
            m = 0.0f;
            
            m_Sprite->p_Position.x -= m;
            m_Delta.x -= m;
    }
    else if (m_Window->isKeyPressed(GLFW_KEY_D))
    {
       
        if (m_Sprite->getPosition().x  > m_Window->getWidth() - (1.3 * m_Sprite->getSize().x))
            m = 0.0f;
        
        
            m_Sprite->p_Position.x += m;
            m_Delta.x += m;
    }
    
    if (m_Window->isKeyTyped(GLFW_KEY_SPACE))
    {
        if (!m_PosSpin)
        {
            m_PosSpin = true;
            changeMoment(m_Moment);
        }
        else
        {
            m_PosSpin = false;
            m_Group->remove(m_Moment->getRenderable());
        }
    }
    
    if (m_PosSpin)
        m_Moment->update();
    
    for (int i = 0; i < m_Alphas.size(); i++)
    {
        m_Alphas[i]->update();
        m_Alphas[i]->collidedList(m_Level->getEnemies());
        
        if (getAlpha(i)->getRemoved())
            getAlpha(i)->setPosition(1000, 1000);
        
        if (isOutOfBounds(getAlpha(i)))
        {
            m_Alphas.erase(m_Alphas.begin() + i);
        }

    }
    
    for (int i = 0; i < m_Gammas.size(); i++)
    {
        m_Gammas[i]->update();
    }
    
    if(j > 180)
        j = 0;
    
    float xdest = m_Delta.x;
    float ydest = m_Delta.y;
    
    move(xdest, ydest);
    
    if (m_Delta.x < 0.0f)
        m_Delta.x += 0.85f;
    else if (m_Delta.x > 0.0f)
        m_Delta.x -= 0.85f;
    
    if (m_Delta.x < 0.85f && m_Delta.x > -0.85f)
        m_Delta.x = 0.0f;
}

void Player::changeMoment(Moment* moment)
{
    moment = new Moment(15, 15, this, m_Window);
    m_Moment = moment;
    m_Group->add(moment->getRenderable());
}

void Player::fission()
{
    addAlpha(new Alpha(getPosition().x + sinf(j) * 100, getPosition().y + cosf(j) * 100 , m_Window));
    addGamma(new Gamma(getPosition().x  +cosf(j) * 50 , getPosition().y + sinf(j) * 50, m_Window));
    addGamma(new Gamma(getPosition().x  +cosf(j) * 50 , getPosition().y + sinf(j) * 50, m_Window));
    addGamma(new Gamma(getPosition().x  +cosf(j) * 50 , getPosition().y + sinf(j) * 50, m_Window));
    //addGamma(new Gamma(m_Enemies[i]->getPosition().x  +cosf(t) * 100 ,
    //addAlpha(new Alpha(getPosition().x + cosf(j) * -100, getPosition().y + sinf(j) * -100 , m_Window));
}

void Player::addAlpha(Alpha* alpha)
{
    alpha->init(m_Level);
    if (getPosition().x < alpha->getPosition().x)
        alpha->moveX = -alpha->moveX * sinf(j);
    
    if (getPosition().y < alpha->getPosition().y)
        alpha->moveY = -alpha->moveY * cosf(j);
    
    m_Alphas.push_back(alpha);
    m_Group->add(alpha->getRenderable());
}

void Player::addGamma(Gamma* gamma)
{
    gamma->init(m_Level);
    m_Gammas.push_back(gamma);
    m_Group->add(gamma->getRenderable());
}

bool Player::isOutOfBounds(Entity *entity)
{
    if (entity->getPosition().x < 0 || entity->getPosition().x > m_Level->getWindow()->getWidth() ||
        entity->getPosition().y < 0 || entity->getPosition().y > m_Level->getWindow()->getHeight())
        return true;
    
    return false;
}

void Player::render()
{
    getRenderable();
    if (m_Health < 0)
    {
        //SoundManager::getSFX("dead")->play();
        m_Health = 0.0f;
    }
}

void Player::setPosition(float x, float y)
{
    m_Position.x = x;
    m_Position.y = y;
}