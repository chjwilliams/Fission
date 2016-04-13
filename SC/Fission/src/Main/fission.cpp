#include "fission.h"
/* 
 
 ~TODO: EMSCRIPTEN
 
 */

using namespace audio;
using namespace graphics;
using namespace maths;

FissionGAME::FissionGAME()
{
}

FissionGAME::~FissionGAME()
{
}

void FissionGAME::init()
{
    m_Window = createWindow("Fission", 960, 540);
    loadAssets();
    m_Level = new Level(m_Window);
    //SoundManager::getSong("test")->play();
    m_count = 0;
    m_TickCount = 0;
}

void TriChromeGAME::loadAssets()
{
    
#ifdef TRICHROME_EMSCRIPTEN
    TextureManager::add(new Texture("player", "/res/test-images/Sushi_3.png"));
    TextureManager::add(new Texture("green", "/res/test-images/test1.png"));
    TextureManager::add(new Texture("blue", "/res/test-images/test2.png"));
    TextureManager::add(new Texture("red", "/res/test-images/test3.png"));
#else
    TextureManager::add(new Texture("Red","TriChrome/res/Sprites/timg1.png"));
    TextureManager::add(new Texture("Green","TriChrome/res/Sprites/timg2.png"));
    TextureManager::add(new Texture("Blue","TriChrome/res/Sprites/timg3.png"));
    TextureManager::add(new Texture("Purple","TriChrome/res/Sprites/timg4.png"));
    TextureManager::add(new Texture("Yellow","TriChrome/res/Sprites/timg5.png"));
    TextureManager::add(new Texture("Orange","TriChrome/res/Sprites/timg6.png"));
    TextureManager::add(new Texture("bg","TriChrome/res/Background/bg1.png"));
#endif
    
#ifdef TRICHROME_EMSCRIPTEN
    SoundManager::add(new Sound("test", "/res/test-sounds/Level1Song.ogg"));
    SoundManager::add(new Sound("pop", "/res/test-sounds/Health_Pickup.ogg"));
#else
    SoundManager::add(new Sound("test", "TriChrome-core/res/test-sounds/Level1Song.ogg"));
    SoundManager::add(new Sound("pop", "TriChrome-core/res/test-sounds/Health_Pickup.ogg"));
    SoundManager::add(new Sound("damage", "TriChrome-core/res/test-sounds/Damage.ogg"));
    SoundManager::add(new Sound("dead", "TriChrome-core/res/test-sounds/Dead.ogg"));
#endif

    
    
}

void FissionGAME::tick()
{
    std::cout << getUPS() << " ups, " << getFPS() << " fps" << std::endl;
}

void FissionGAME::update()
{
    m_Level->update();
}

void FissionGAME::render()
{
    m_Level->render();
}