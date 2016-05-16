#include "neutron.h"
#include "player.h"

using namespace sparky;
using namespace maths;
using namespace audio;

Neutron::Neutron(float x, float y, sparky::maths::vec2 angle, Entity* entity, sparky::graphics::Window* window) 
	: Entity(x, y, window), m_Window(window), m_Entity(entity)
{
    m_Sprite = new graphics::Sprite(x, y, 16, 16, graphics::TextureManager::get("Yellow"));
	m_Position = vec2(entity->getPosition().x + 25, entity->getPosition().y + 25);
	m_Angle = angle;
    m_Renderable = m_Sprite;
	moveX = m_Angle.x * 10;
	moveY = m_Angle.y * 10;
    m_Type = NEUTRON;
}

void Neutron::update()
{
	m_Position.x = m_Position.x + moveX;
	m_Position.y = m_Position.y + moveY;

	m_Sprite->setPosition(m_Position);

	if (outOfRange())
		m_Sprite->setPosition(vec3(-100, -100, 0));

}

void Neutron::render()
{
    getRenderable();
}