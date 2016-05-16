#pragma once

#include "Menu.h"

class GameOverMenu : public Menu
{
private:
	sparky::graphics::Label* m_TopScore;
	sparky::graphics::Label* m_BtmScore;
	sparky::graphics::Label* m_CritTop;
	sparky::graphics::Label* m_CritBtm;
	sparky::graphics::Label* m_SuperCrit;
	sparky::graphics::Label* m_HyperCrit;
	sparky::graphics::Label* m_IntScore;
	sparky::graphics::Label* m_Score;
public:
	GameOverMenu(sparky::graphics::Window* window);
	void update() override;
	void render() override;

	void setScore(unsigned int topScore, unsigned int btmScore, bool critTop, bool critBtm, bool superCrit, bool hyperCrit);
};