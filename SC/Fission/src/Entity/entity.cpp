#include "entity.h"
#include "../GameState/level.h"
#include "../Main/fission.h"

Entity::Entity(float x, float y, sparky::graphics::Window* window)
:m_Window(window), m_Position(sparky::maths::vec3(x, y, 0.0f)), m_Removed(false), m_CollisionDirection(NONE), m_Type(NIL), m_Hit(false), m_Flinching(false)
{
    
}

Entity::~Entity()
{
    
}

void Entity::init(Level* level)
{
    m_Level = level;
}

void Entity::remove()
{
    m_Removed = true;
}


void Entity::detectCollisions()
{
	for (int i = 0; i < m_Level->getNuclei().size(); i++)
	{
		if (m_Level->getNucleus(i) != this)
		{
			if (getCenter().x + getRadius() + m_Level->getNucleus(i)->getRadius() > m_Level->getNucleus(i)->getCenter().x
				&& getCenter().x < m_Level->getNucleus(i)->getCenter().x + getRadius() + m_Level->getNucleus(i)->getRadius()
				&& getCenter().y + getRadius() + m_Level->getNucleus(i)->getRadius() > m_Level->getNucleus(i)->getCenter().y
				&& getCenter().y < m_Level->getNucleus(i)->getCenter().y + getRadius() + m_Level->getNucleus(i)->getRadius())
			{
				if (getCenter().distance(m_Level->getNucleus(i)->getCenter()) < getRadius() + m_Level->getNucleus(i)->getRadius())
				{
					if (m_Type == GAMMA)
						m_Level->addPoints(5, m_Level->getNucleus(i)->getIsTop());
					else
						calculateNewVelocities(this, m_Level->getNucleus(i));
						
				}
			}
		}
	}
}

void Entity::calculateNewVelocities(Entity* first, Entity* second)
{
	float mass1 = first->getRadius();
	float mass2 = second->getRadius();

	float velX1 = first->moveX;
	float velY1 = first->moveY;
	float velX2 = second->moveX;
	float velY2 = second->moveY;

	float newVelX1 = (velX1 * (mass1 - mass2) + (2 * mass2 * velX2)) / (mass1 + mass2);
	float newVelY1 = (velY1 * (mass1 - mass2) + (2 * mass2 * velY2)) / (mass1 + mass2);
	float newVelX2 = (velX2 * (mass2 - mass1) + (2 * mass1 * velX1)) / (mass1 + mass2);
	float newVelY2 = (velY2 * (mass2 - mass1) + (2 * mass1 * velY1)) / (mass1 + mass2);

	first->moveX = newVelX1;
	first->moveY = newVelY1;
	second->moveX = newVelX2;
	second->moveY = newVelY2;

	first->m_Position.x += newVelX1;
	first->m_Position.y += newVelY1;
	second->m_Position.x += newVelX2;
	second->m_Position.y += newVelY2;
}

bool Entity::outOfRange()
{
	if (m_Position.x < 0 || m_Position.x > m_Window->getWidth() ||
		m_Position.y < 0 || m_Position.y > m_Window->getHeight())
		return true;
	else
		return false;
}

void Entity::setFlinching(bool flinching)
{
    m_Flinching = flinching;
}

void Entity::flinchTimer()
{
    if (m_Timer.seconds_elapsed() % 2 == 0)
    {
        m_Flinching = false;
    }
    
}