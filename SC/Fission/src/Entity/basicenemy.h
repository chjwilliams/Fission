#pragma once

#include "../../../src/sparky.h"
#include "entity.h"
#include "moment.h"

class BasicEnemy : public Entity
{
friend class Moment;
private:
    sparky::graphics::Window* m_Window;
    sparky::graphics::Group* m_Group;
    sparky::maths::mat4& m_Transformation;
    int m_HitCount;
    Moment* m_Moment;
    bool m_PosSpin;
    float j;
    
public:
    BasicEnemy(float x, float y, float width, float height, sparky::graphics::Window* window);
    BasicEnemy(float x, float y, sparky::graphics::Window* window);
    
    void update() override;
    void render() override;
    
    void toggleMoment(Moment* moment);
    void setPosition(float x, float y);
    inline const bool getPosSpin() const { return m_PosSpin; }
};