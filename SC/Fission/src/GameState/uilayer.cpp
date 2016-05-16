#include "uiLayer.h"

using namespace sparky;
using namespace graphics;

UILayer::UILayer()
	: Layer(new BatchRenderer2D(),
#ifdef SPARKY_EMSCRIPTEN
	new Shader("shaders/es3/ui.es3.vert", "shaders/es3/ui.es3.frag")
#else
	new Shader("res/Shaders/basic.vert", "res/Shaders/basic.frag")
#endif
	, maths::mat4::orthographic(0, 960, 0, 540, -1, 1))
{

}

UILayer::~UILayer()
{

}