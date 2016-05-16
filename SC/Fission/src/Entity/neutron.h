#pragma once

#include "../../../Sparky-core/src/sparky.h"
#include "entity.h"

class Player;

class Neutron : public Entity
{
private:
    sparky::graphics::Window* m_Window;
	sparky::maths::vec2 m_Angle;
    Entity* m_Entity;
    float t;
    
public:
    Neutron(float x, float y, sparky::maths::vec2 angle, Entity* entity , sparky::graphics::Window* window);
    
    void update() override;
    void render() override;
};