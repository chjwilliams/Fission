#pragma once

#include "Menu.h"
#include "../../Entity/player.h"
#include "../level.h"
#include "../levellayer.h"

class HelpMenu : public Menu
{
private:
	Player* m_Player;
	Level* m_Level;
	sparky::graphics::Sprite* m_Overlay;
	LevelLayer* m_SandboxLayer;
public:
	HelpMenu(sparky::graphics::Window* window);
	void update() override;
	void render() override;
};