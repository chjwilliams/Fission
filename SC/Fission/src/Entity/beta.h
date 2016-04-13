#pragma once

#include "../../../src/sparky.h"
#include "entity.h"

class Beta : public Entity
{
private:
    sparky::graphics::Window* m_Window;
    
public:
    Beta(float x, float y, sparky::graphics::Window* window);
    float moveX, moveY;
    void update() override;
    void render() override;
    
    void setPosition(float x, float y);
};