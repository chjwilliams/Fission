#pragma once

#include "../../../Sparky-core/src/sparky.h"
#include "entity.h"
#include "neutron.h"

class Nucleus : public Entity
{
friend class Neutron;
private:
	bool m_IsTop;
    sparky::graphics::Window* m_Window;
    sparky::graphics::Group* m_Group;
    sparky::maths::mat4& m_Transformation;
    
    
public:
	Nucleus(float x, float y, float width, float height, bool isTop ,sparky::graphics::Window* window);
    
    void update() override;
    void render() override;
   
    void setPosition(float x, float y);
	inline const bool getIsTop() const { return m_IsTop; }
};