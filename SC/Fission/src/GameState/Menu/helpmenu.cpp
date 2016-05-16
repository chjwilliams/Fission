#include "HelpMenu.h"
#include "../GameState.h"
#include "../../Main/fission.h"

using namespace sparky;
using namespace graphics;

static void HelpMenu_okay()
{
	FissionGAME::INSTANCE->setMainMenu();
}

HelpMenu::HelpMenu(Window* window)
	: Menu(window, new Sprite(0, 0, 960, 540, TextureManager::get(
#ifdef SPARKY_EMSCRIPTEN
	"Menu_Help_About"
#else
	"Menu_Help"
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

	m_Layer->add(new Label("Back", 800, 60, 0xffffffff));
	m_Overlay = new sparky::graphics::Sprite(0, 0, 960, 540, TextureManager::get("HelpMenuOverlay"));
	m_Level = new Level(m_Window);
	m_SandboxLayer = new LevelLayer();
	m_SelectedMapping[0] = maths::vec2(780, 65);
	create();
	m_Player = new Player(m_Window->getWidth() / 2 - 64, m_Window->getHeight() / 2 - 32, m_Window);
	m_Level->addPlayer(m_Player);
	m_SandboxLayer->add(m_Overlay);
	m_ActionMapping[0] = HelpMenu_okay;
}

void HelpMenu::update()
{
	m_Player->update();
	Menu::update();
}

void HelpMenu::render()
{
	
	Menu::render();
	m_Level->render();
	m_Player->render();
	m_SandboxLayer->render();
}