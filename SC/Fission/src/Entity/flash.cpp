#include "flash.h"
#include "../GameState/level.h"

Flash::Flash(float x, float y, sparky::graphics::Window* window)
	: Entity(x, y, window)
{
	m_Sprite = new sparky::graphics::Sprite(0, 0, 0, 0, 0xff);
	m_Renderable = m_Sprite;
	m_Light = m_Position;
	m_Intensity = 500;
	m_FadeOut = 1.0f;
}

void Flash::init(Level* level)
{
	Entity::init(level);
	m_Shader = m_Level->m_LevelLayer->getShader();
	//m_BGShader = m_Level->m_OverlayLayer->getShader();
}

void Flash::update()
{
	m_Intensity += 100;


	if (m_Intensity > 500)
		m_Intensity -= 500;


}

void Flash::render()
{

	m_Shader->enable();
	m_Shader->setUniform2f("nuke_pos", m_Position);
	m_Shader->setUniform1f("nuke_intensity", m_Intensity);
	m_Shader->setUniform1f("fade_out", m_FadeOut);

	/*
	m_BGShader->enable();
	m_BGShader->setUniform2f("nuke_pos", m_Position);
	m_BGShader->setUniform1f("nuke_intensity", m_Intensity);
	m_BGShader->setUniform1f("fade_out", m_FadeOut);
*/	
}