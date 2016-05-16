#include "AboutMenu.h"
#include "../GameState.h"
#include "../../Main/fission.h"
using namespace sparky;
using namespace graphics;

static void AboutMenu_okay()
{
	FissionGAME::INSTANCE->setMainMenu();
}

AboutMenu::AboutMenu(Window* window)
	: Menu(window, new Sprite(0, 0, 960, 540, TextureManager::get(
#ifdef SPARKY_EMSCRIPTEN
	"Menu_Help_About"
#else
	"Menu_About"
#endif
	)))
{
#ifdef SPARKY_EMSCRIPTEN
	std::vector<maths::vec2> uv(4);
	uv[0] = maths::vec2(0, 0.3515625f);
	uv[1] = maths::vec2(0, 0.3515625f * 2.0f);
	uv[2] = maths::vec2(0.625f, 0.3515625f * 2.0f);
	uv[3] = maths::vec2(0.625f, 0.3515625f);
	m_Sprite->setUV(uv);
#endif

	m_Layer->add(new Label("Back", 800, 60, 0xffffffff));
	m_SelectedMapping[0] = maths::vec2(780, 65);
	create();

	m_ActionMapping[0] = AboutMenu_okay;
}

void AboutMenu::update()
{
	Menu::update();
}

void AboutMenu::render()
{
	Menu::render();
}