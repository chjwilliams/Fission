#include "entity.h"
#include "../GameState/level.h"
#include "../Main/fission.h"

Entity::Entity(float x, float y)
:m_Position(sparky::maths::vec3(x, y, 0.0f)), m_Removed(false), m_CollisionDirection(NONE), m_Health(40.0f), m_Type(NIL), m_Hit(false), m_Dead(false), m_Flinching(false)
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
    //small flash bang
}

bool Entity::hasCollided(float xdest, float ydest) const
{
    using namespace sparky;
    using namespace maths;
    
    std::vector<LevelObject*> objects = m_Level->getObjects(this, 640);
     
     for (LevelObject* object : objects)
     {
        if (!object->isCollidable())
            continue;
     
        const vec3& pos = object->getPosition();
        const vec2& size = object->getSize();
     
        if (m_Position.x + xdest <= pos.x + size.x && 
            m_Position.x + xdest + m_Sprite->getSize().x >= pos.x)
            if (m_Position.y + ydest <= pos.y + size.y &&
                m_Position.y + ydest + m_Sprite->getSize().y >= pos.y)
                    return true;
     }
    
    return false;
}

int Entity::collision(float& xdest,float& ydest) const
{
    using namespace sparky;
    using namespace maths;
    
    if (xdest == 0 && ydest == 0)
        return NONE;
    
    float xtemp = xdest;
    float ytemp = ydest;
    
    bool x = false;
    bool y = false;
    
    float dx = sign(xtemp);
    float xx = std::abs(xdest);
    while (xx >= 1.0f)
    {
        x = hasCollided(dx, 0);
        if (x)
        {
            xdest = dx - sign(xtemp) - 0.5f * sign(xtemp);
            break;
        }
        dx += sign(xtemp);
        xx--;
    }
    
    if (xx < 1.0f)
        x = hasCollided(dx + xx * sign(xtemp), 0);
    
    float dy = sign(ytemp);
    float yy = std::abs(ydest);
    while (yy >= 1.0f)
    {
        y = hasCollided(0, dy);
        if (y)
        {
            ydest = dy - sign(ytemp) - 0.5f * sign(ytemp);
            break;
        }
        dy += sign(ytemp);
        yy--;
    }
    
    if (yy < 1.0f)
        y = hasCollided(0, dy + yy * sign(ytemp));
    
    
    int result = 0x0;
    if (x)
        result |= xtemp < 0 ? 0x0F00 : 0xF000;
    if (y)
        result |= ytemp < 0 ? 0x00F0 : 0x000F;
    
    return result;
}

bool Entity::collided(Entity* entity)
{
    using namespace maths;
    
    const vec2& a = entity->getPosition();
    const vec2 sa = entity->getSprite()->getSize();
    const vec2& b = getPosition();
    const vec2 sb = getSprite()->getSize() + 16;
    
    if (m_Flinching)
        return false;
    
    if (a.x + sa.x > b.x && a.x < b.x + sb.x)
    {
        if (a.y + sa.y > b.y && a.y < b.y + sb.y)
        {
            m_Flinching = true;
            if (!(m_Type == BETA || m_Type == GAMMA))
            {
                entity->moveX = entity->moveX * -1;
                entity->moveY = entity->moveY * -1;
            }
            return true;
        }
    }
    
    return false;
}

void Entity::collidedList(std::vector<Entity*> entities)
{
    using namespace maths;
    
    for (int i = 0; i < entities.size(); i++)
    {
       if( collided(entities[i]) && entities[i]->m_Type == ENEMY && !entities[i]->m_Flinching)
       {
           entities[i]->m_Hit = true;
           entities[i]->moveX = entities[i]->moveX * -1;
           entities[i]->moveY = entities[i]->moveY * -1;
           if (m_Type == ALPHA)
               m_Removed = true;
           
       }
    }
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

void Entity::damage(unsigned int d)
{
    m_Health -= d;
    if (m_Health <= 0)
        m_Dead = true;
}

void Entity::move(float xdest, float ydest)
{
    float xtemp = xdest;
    float ytemp = ydest;
    int collDir = collision(xdest, ydest);
    /*
    if ((collDir & 0x00F0) > 0x0)
        m_CollisionDirection = BOTTOM;
    else
        m_CollisionDirection = NONE;
     */
    
    if (xtemp != xdest)
        m_Position.x += xdest;
    
    if (ytemp != ydest)
        m_Position.y += ydest;
}