#pragma once

#include <vector>

#include "../../../Sparky-core/src/sparky.h"
#include "entity.h"
#include "gamma.h"
#include "neutron.h"

class Player : public Entity
{
friend class Moment;
private:
	bool m_HasFired;
	float m;
	float j;
	float m_FireAngle;
	int m_Shots;
	sparky::maths::vec2 m_Angle;
	sparky::maths::vec3 m_ScreenPos;
	sparky::maths::mat4& m_Transformation;
    sparky::graphics::Window* m_Window;
    sparky::graphics::Group* m_Group;
	sparky::graphics::Sprite* m_ShotMark;
	Neutron* m_Neutron;
   
public:
    Player(float x, float y, sparky::graphics::Window* window);
    
    void update() override;
    void render() override;
    
    bool isOutOfBounds(Entity* entity);
    void setPosition(float x, float y);
    void fireNeutron(Neutron* neutron);

	inline const bool hasFired() const { return m_HasFired; }
	inline const int getShots() const { return m_Shots; }
	Neutron* getNeutron() { return m_Neutron; }
};