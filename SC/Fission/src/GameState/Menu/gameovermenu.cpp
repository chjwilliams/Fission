#include "GameOverMenu.h"
#include "../GameState.h"
#include "../../Main/fission.h"

using namespace sparky;
using namespace graphics;

static void GameOverMenu_okay()
{
 	FissionGAME::INSTANCE->setMainMenu();
}

GameOverMenu::GameOverMenu(sparky::graphics::Window* window)
	: Menu(window, new Sprite(0, 0, 960, 540, TextureManager::get(
#ifdef SPARKY_EMSCRIPTEN
	"Menu_Main_Gameover"
#else
	"Menu_GameOver"
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
	m_TopScore = new Label("", 300, 390, 0xffffffff);
	m_BtmScore = new Label("", 300, 360, 0xffffffff);
	m_CritTop = new Label("", 300, 330, 0xffffffff);
	m_CritBtm = new Label("", 300, 300, 0xffffffffff);
	m_IntScore = new Label("", 300, 270, 0xfffffffff);
	m_SuperCrit = new Label("", 300, 240, 0xfffffffff);
	m_HyperCrit = new Label("", 300, 210, 0xfffffffff);
	m_Score = new Label("", 300, 150, 0xffffffff);
	m_Layer->add(m_TopScore);
	m_Layer->add(m_BtmScore);
	m_Layer->add(m_CritTop);
	m_Layer->add(m_CritBtm);
	m_Layer->add(m_IntScore);
	m_Layer->add(m_SuperCrit);
	m_Layer->add(m_HyperCrit);
	m_Layer->add(m_Score);
	m_Layer->add(new Label("End", 800, 50, 0xffffffff));
	m_SelectedMapping[0] = maths::vec2(780, 55);
	create();

	m_ActionMapping[0] = GameOverMenu_okay;
}

void GameOverMenu::update()
{
	Menu::update();
}

void GameOverMenu::render()
{
	Menu::render();
}

void GameOverMenu::setScore(unsigned int topScore, unsigned int btmScore, bool critTop, bool critBtm, bool superCrit, bool hyperCrit)
{
	m_TopScore->text = "TScore: " + std::to_string(topScore);
	m_BtmScore->text = "BScore: " + std::to_string(btmScore);
	if (critTop)
	{
		m_CritTop->text = "Critical Mass (top): 1.25 * " + std::to_string(topScore);
		topScore = topScore * 1.25;
	}
	else
		m_CritTop->text = "Critical Mass (top): NO :(";
	if (critBtm)
	{
		m_CritBtm->text = "Critical Mass(btm) : 1.25 * " + std::to_string(btmScore);
		btmScore = btmScore * 1.25;
	}
	else
		m_CritBtm->text = "Critical Mass(btm) : NO :(";

	unsigned int score = topScore + btmScore;

	m_IntScore->text = "Score:" + std::to_string(score);

	if (superCrit)
	{
		m_SuperCrit->text = "Super Critical Mass: 1.5 * " + std::to_string(score);
	}
	else
		m_SuperCrit->text = "Super Critical Mass: NO :(";
	if (hyperCrit)
		m_HyperCrit->text = "Ultra Critical Mass: 2 * " + std::to_string(score);
	else
		m_HyperCrit->text = "Ultra Critical Mass: NO :(";

	m_Score->text = "Score: " + std::to_string(score);
}
