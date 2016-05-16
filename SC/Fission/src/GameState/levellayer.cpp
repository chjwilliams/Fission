#include "levellayer.h"

using namespace sparky;
using namespace graphics;

LevelLayer::LevelLayer()
    :Layer(new BatchRenderer2D(),
#ifdef TRICHROME_EMSCRIPTEN
           new Shader("vert", "frag")
#else
           new Shader("res/Shaders/level.vert", "res/Shaders/level.frag")
#endif
           , maths::mat4::orthographic(0, 960, 0, 540, -1, 1))
{
    
}

LevelLayer::~LevelLayer()
{
    
}

void LevelLayer::remove(void* pointer)
{
    for (int i = 0; i < m_Renderables.size(); i++)
    {
        if (m_Renderables[i] == pointer)
        {
            delete m_Renderables[i];
            m_Renderables.erase(m_Renderables.begin() + i);
            return;
        }
    }
}