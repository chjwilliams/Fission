#include "../../../src/sparky.h"
#include "../GameState/level.h"

#define APPLICATION FissionGAME

using namespace sparky;


class FissionGAME : public Sparky
{
public:
    static FissionGAME* INSTANCE;
private:
    graphics::Window* m_Window;
    Level* m_Level;
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
    void nextLevel();
    void end();
    
private:
    void loadAssets();
};

