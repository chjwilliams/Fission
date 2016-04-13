#include "moment.h"
#include "player.h"

using namespace sparky;
using namespace maths;
using namespace audio;

Moment::Moment(float x, float y, Entity* entity ,sparky::graphics::Window* window) : Entity(x, y), m_Window(window), m_Entity(entity)
{
    m_Sprite = new graphics::Sprite(x, y, 32, 32, graphics::TextureManager::get("Yellow"));
    m_Renderable = m_Sprite;
    m_Type = MOMENT;
    t = 0.0f;
}

void Moment::update()
{
    t += 0.1;
    m_Sprite->position = vec2(cosf(t) * 10 + m_Entity->getPosition().x - 8, sinf(t) * 10 + m_Entity->getPosition().y - 8);
    if(t > 180)
        t = 0;

}

void Moment::render()
{
    getRenderable();
}