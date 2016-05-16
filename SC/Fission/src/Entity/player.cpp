#include "player.h"
#include "../GameState/level.h"
#include "../Main/fission.h"

using namespace sparky;
using namespace maths;
using namespace audio;

Player::Player (float x, float y, sparky::graphics::Window* window)
: Entity(x, y, window), m_Window(window), m_Group(new graphics::Group(mat4::identity())), m_Transformation(m_Group->getTransformRef())
{
    m_Sprite = new graphics::Sprite(0, 0, 64, 64, graphics::TextureManager::get("Player"));
	
    m_ScreenPos = vec3(m_Window->getWidth() / 2 - 64, m_Window->getHeight() / 2 - 32, 0);
	setPosition(m_ScreenPos.x, m_ScreenPos.y);
	m_HasFired = false;
	m_FireAngle = 1.5f;
	m_ShotMark = new graphics::Sprite(cos(m_FireAngle) + m_ScreenPos.x, sin(m_FireAngle) + m_ScreenPos.y, 16, 16, graphics::TextureManager::get("Yellow1"));
	m_Group->add(m_Sprite);
	m_Group->add(m_ShotMark);
	m_Renderable = m_Group;
    m_Type = PLAYER;

	m_Shots = 5;
}

void Player::update()
{
    m = 20.0f;
	m_ShotMark->setPosition(vec2((cos(m_FireAngle) * 50 + m_Position.x + 25), (sin(m_FireAngle) * 50 + m_Position.y + 25)));
	m_Sprite->setPosition(m_Position);

    if (m_Window->isKeyPressed(GLFW_KEY_W) || m_Window->isKeyPressed(GLFW_KEY_UP))
    {
		m_FireAngle += 0.15f;
     
    }
    else if (m_Window->isKeyPressed(GLFW_KEY_S) || m_Window->isKeyPressed(GLFW_KEY_DOWN))
    {
		m_FireAngle -= 0.15f;
    }
    
    if (m_Window->isKeyPressed(GLFW_KEY_A) || m_Window->isKeyPressed(GLFW_KEY_LEFT))
    {
        if (m_Position.x < m_Sprite->getSize().x)
            m = 0.0f;
            
            m_Position.x -= m;
    }
    else if (m_Window->isKeyPressed(GLFW_KEY_D) || m_Window->isKeyPressed(GLFW_KEY_RIGHT))
    {
       
        if (m_Position.x  > m_Window->getWidth() - 128)
            m = 0.0f;
        
        
            m_Position.x += m;
    }
    
    if (m_Window->isKeyTyped(GLFW_KEY_SPACE))
    {
		fireNeutron(m_Neutron);
		m_Level->getEntities().push_back(m_Neutron);
		m_HasFired = true;
    }

	if (m_HasFired)
	{
		m_Neutron->update();
		if (m_Neutron->getPosition().x < 0 || m_Neutron->getPosition().x > m_Window->getWidth() ||
			m_Neutron->getPosition().y < 0 || m_Neutron->getPosition().y > m_Window->getHeight())
		{
			m_Neutron->remove();
			m_Group->remove(m_Neutron->getRenderable());
			if (GameState::isGame())
				m_Shots--;
			m_HasFired = false;
		}
	}

	if (m_Shots == 0)
	{
		GameState::setGameOver(true);
		FissionGAME::INSTANCE->end();
	}
}

void Player::fireNeutron(Neutron* neutron)
{
	if (!m_HasFired)
	{
		neutron = new Neutron(16, 16, vec2((cos(m_FireAngle)), (sin(m_FireAngle))), this, m_Window);
		m_Neutron = neutron;
		//m_Group->add(neutron->getRenderable());
		if (GameState::isMenu())
			m_Level->m_OverlayLayer->add(neutron->getRenderable());
		else
			m_Level->m_LevelLayer->add(neutron->getRenderable());
		m_Level->getEntities().push_back(neutron);
	}
}

bool Player::isOutOfBounds(Entity *entity)
{
    if (entity->getPosition().x < 0 || entity->getPosition().x > m_Window->getWidth() ||
        entity->getPosition().y < 0 || entity->getPosition().y > m_Window->getHeight())
        return true;
    
    return false;
}

void Player::render()
{
    getRenderable();
}

void Player::setPosition(float x, float y)
{
    m_Position.x = x;
    m_Position.y = y;
}