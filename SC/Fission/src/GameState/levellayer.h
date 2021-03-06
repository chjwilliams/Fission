#pragma once

#include "../../../Sparky-core/src/sparky.h"

class LevelLayer : public sparky::graphics::Layer
{
private:
public:
    LevelLayer();
    ~LevelLayer();
    sparky::graphics::Shader* getShader() const { return m_Shader; }
    void remove(void * pointer);
};