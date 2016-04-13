#pragma once

#include "../../../src/sparky.h"
#include "entity.h"

class Player;

class Moment : public Entity
{
private:
    sparky::graphics::Window* m_Window;
    Entity* m_Entity;
    float t;
    
public:
    Moment(float x, float y, Entity* entity , sparky::graphics::Window* window);
    
    void update() override;
    void render() override;
};