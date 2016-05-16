#pragma once

#include "../../../Sparky-core/src/sparky.h"
#include "entity.h"

class Flash : public Entity
{
private:
	sparky::graphics::Shader* m_Shader, *m_BGShader;
	sparky::maths::vec2 m_Light;
	float m_Intensity;
	float m_FadeOut;
public:
	Flash(float x, float y, sparky::graphics::Window* window);

	void setIntensity(float i) { m_Intensity = i; }

	void init(Level* level) override;
	void update() override;
	void render() override;
};