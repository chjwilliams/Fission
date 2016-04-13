#pragma once

#include "../../../src/sparky.h"
#include "entity.h"

class Gamma : public Entity
{
private:
    sparky::graphics::Window* m_Window;
    
public:
    Gamma(float x, float y, sparky::graphics::Window* window);
    float moveX, moveY;
    void update() override;
    void render() override;
    
    void setPosition(float x, float y);
};