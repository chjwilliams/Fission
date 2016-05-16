#include "fission.h"
/* 
 
 ~TODO: EMSCRIPTEN
 
 */

using namespace audio;
using namespace graphics;
using namespace maths;

FissionGAME* FissionGAME::INSTANCE = nullptr;
unsigned int GameState::m_Current = 0;
bool GameState::m_GameOver = false;

FissionGAME::FissionGAME()
{
	INSTANCE = this;
	GameState::setGameState(STATE_MENU);
	m_Level = nullptr;
}

FissionGAME::~FissionGAME()
{
	delete m_UILayer;
	if (m_Level != nullptr)
		delete m_Level;

	delete m_MenuMain;
	delete m_MenuGameOver;
	delete m_MenuHelp;
	delete m_MenuAbout;
}

void FissionGAME::init()
{
    m_Window = createWindow("Fission", 960, 540);
    loadAssets();

	m_UILayer = new UILayer();
	m_FPS = new Label("", 900, 50, 0xffffffff);

	m_MenuMain = new MainMenu(m_Window);
	m_MenuGameOver = new GameOverMenu(m_Window);
	m_MenuHelp = new HelpMenu(m_Window);
	m_MenuAbout = new AboutMenu(m_Window);

	m_Menu = m_MenuMain;
    SoundManager::get("Song")->loop();
}

void FissionGAME::loadAssets()
{
	FontManager::get()->setScale(1, 1);
#ifdef TRICHROME_EMSCRIPTEN
    TextureManager::add(new Texture("player", "/res/test-images/Sushi_3.png"));
    TextureManager::add(new Texture("green", "/res/test-images/test1.png"));
    TextureManager::add(new Texture("blue", "/res/test-images/test2.png"));
    TextureManager::add(new Texture("red", "/res/test-images/test3.png"));
#else
	TextureManager::add(new Texture("Player", "res/Sprites/Player.png"));
    TextureManager::add(new Texture("Red", "res/Sprites/timg1.png"));
    TextureManager::add(new Texture("Green", "res/Sprites/timg2.png"));
    TextureManager::add(new Texture("Blue", "res/Sprites/timg3.png"));
    TextureManager::add(new Texture("Purple", "res/Sprites/timg4.png"));
    TextureManager::add(new Texture("Yellow", "res/Sprites/timg5.png"));
	TextureManager::add(new Texture("Yellow1", "res/Sprites/timg5.png"));
    TextureManager::add(new Texture("Orange", "res/Sprites/timg6.png"));
    TextureManager::add(new Texture("Background", "res/Background/FissionBG.png"));
	TextureManager::add(new Texture("HelpMenuOverlay", "res/Background/HelpMenuOverlay.png"));
	TextureManager::add(new Texture("Overlay", "res/Background/FissionScene.png"));
	TextureManager::add(new Texture("Menu_Main", "res/Background/MainMenu.png"));
	TextureManager::add(new Texture("Menu_Help", "res/Background/HelpMenu.png"));
	TextureManager::add(new Texture("Menu_About", "res/Background/AboutMenu.png"));
	TextureManager::add(new Texture("Menu_GameOver", "res/Background/GameOverMenu.png"));
#endif
    
#ifdef TRICHROME_EMSCRIPTEN
    SoundManager::add(new Sound("test", "/res/test-sounds/Level1Song.ogg"));
    SoundManager::add(new Sound("pop", "/res/test-sounds/Health_Pickup.ogg"));
#else
    SoundManager::add(new Sound("Song", "res/Audio/FissionSong.ogg"));
    SoundManager::add(new Sound("Boom", "res/Audio/Damage.ogg"));
    SoundManager::add(new Sound("Points", "res/Audio/Points.ogg"));
#endif

    
    
}

void FissionGAME::tick()
{
    std::cout << getUPS() << " ups, " << getFPS() << " fps" << std::endl;
}

void FissionGAME::update()
{
	switch (GameState::getGameState())
	{
		case STATE_MENU:
		{
			m_Menu->update();
			break;
		}
		case STATE_GAME:
		{
			if (GameState::isGameOver())
			{
				m_Level->endGame();
			}
			m_Level->update();
			break;
		}
	}
}

void FissionGAME::render()
{
	switch (GameState::getGameState())
	{
		case STATE_MENU:
		{
			m_Menu->render();
			break;
		}
		case STATE_GAME:
		{
			m_Level->render();
			break;
		}
	}
}

void FissionGAME::begin()
{
	m_Level = new Level(m_Window);
	m_Level->addPlayer(new Player(0, 0, m_Window));
	m_Level->start();
}

void FissionGAME::end()
{
	m_Level->addScores();
	((GameOverMenu*)m_MenuGameOver)->setScore(m_Level->getTopScore(), m_Level->getBtmScore(), m_Level->getCritTop(), m_Level->getCritBtm(), m_Level->getSuperCrit(),  m_Level->getHyperCrit());
	GameState::setGameState(STATE_MENU);
	m_Menu = m_MenuGameOver;
	delete m_Level;
	GameState::setGameOver(false);
}

void FissionGAME::setMainMenu()
{
	m_Menu = m_MenuMain;
}

void FissionGAME::setHelpMenu()
{
	m_Menu = m_MenuHelp;
}

void FissionGAME::setAboutMenu()
{
	m_Menu = m_MenuAbout;
}