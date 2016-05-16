#include "../../../Sparky-core/src/sparky.h"

#include "../GameState/uilayer.h"
#include "../GameState/level.h"
#include "../Entity/player.h"

#include "../GameState/Menu/menu.h"
#include "../GameState/Menu/mainmenu.h"
#include "../GameState/Menu/gameovermenu.h"
#include "../GameState/Menu/aboutmenu.h"
#include "../GameState/Menu/helpmenu.h"

#include "../GameState/gamestate.h"



#define APPLICATION FissionGAME

using namespace sparky;


class FissionGAME : public Sparky
{
public:
    static FissionGAME* INSTANCE;
private:
    graphics::Window* m_Window;
	graphics::Label* m_FPS;
	UILayer* m_UILayer;
    Level* m_Level;
	Menu* m_Menu;
	Menu *m_MenuMain, *m_MenuGameOver, *m_MenuHelp, *m_MenuAbout;
    int m_count;
    unsigned int m_TickCount;
public:
    FissionGAME();
    ~FissionGAME();
    
    const unsigned int getTickCount() const { return m_TickCount; }
    
    void init() override;
    void tick() override;
    void update() override;
    void render() override;
    
    void begin();
    void end();
    
	void setMainMenu();
	void setHelpMenu();
	void setAboutMenu();

private:
    void loadAssets();
};

