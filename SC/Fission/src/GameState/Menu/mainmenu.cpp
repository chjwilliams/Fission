#include "MainMenu.h"
#include "../gamestate.h"
#include "../../Main/fission.h"

using namespace sparky;
using namespace graphics;

static void MainMenu_play()
{
	GameState::setGameState(STATE_GAME);
	FissionGAME::INSTANCE->begin();
}

static void MainMenu_help()
{
	FissionGAME::INSTANCE->setHelpMenu();
}

static void MainMenu_about()
{
	FissionGAME::INSTANCE->setAboutMenu();
}

#ifndef SPARKY_EMSCRIPTEN
static void MainMenu_quit()
{
	std::exit(0);
}
#endif

MainMenu::MainMenu(Window* window)
	: Menu(window, new Sprite(0, 0, 960, 540, TextureManager::get(
#ifdef SPARKY_EMSCRIPTEN
	"Menu_Main_Gameover"
#else
	"Menu_Main"
#endif
	)))
{
#ifdef SPARKY_EMSCRIPTEN
	std::vector<maths::vec2> uv(4);
	uv[0] = maths::vec2(0, 0);
	uv[1] = maths::vec2(0, 0.3515625f);
	uv[2] = maths::vec2(0.625f, 0.3515625f);
	uv[3] = maths::vec2(0.625f, 0);
	m_Sprite->setUV(uv);
#endif

	m_Layer->add(new Label("Play", 440, 250, 0xffffffff));
	m_Layer->add(new Label("Help", 440, 200, 0xffffffff));
	m_Layer->add(new Label("About", 430, 150, 0xffffffff));
	create();

	m_SelectedMapping[0] = maths::vec2(420, 255);
	m_SelectedMapping[1] = maths::vec2(420, 205);
	m_SelectedMapping[2] = maths::vec2(410, 155);

	m_ActionMapping[0] = MainMenu_play;
	m_ActionMapping[1] = MainMenu_help;
	m_ActionMapping[2] = MainMenu_about;

#ifndef SPARKY_EMSCRIPTEN
	m_ActionMapping[3] = MainMenu_quit;
	m_SelectedMapping[3] = maths::vec2(420, 105);
	m_Layer->add(new Label("Quit", 440, 100, 0xffffffff));
#endif
}

void MainMenu::update()
{
	Menu::update();
}

void MainMenu::render()
{
	Menu::render();
}