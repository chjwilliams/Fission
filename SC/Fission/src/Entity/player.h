#pragma once

#include <vector>

#include "../../../src/sparky.h"
#include "entity.h"
#include "alpha.h"
#include "gamma.h"
#include "moment.h"

class Player : public Entity
{
friend class Moment;
private:
    sparky::graphics::Window* m_Window;
    sparky::graphics::Group* m_Group;
    float m_Speed;
    float moveX;
    float moveY;
    std::vector<Alpha*> m_Alphas;
    std::vector<Gamma*> m_Gammas;
    sparky::maths::vec2 m_Delta;
    sparky::maths::mat4& m_Transformation;
    sparky::maths::vec3 m_ScreenPos;
    unsigned int m_FlinchTime;
    
    Moment* m_Moment;
    float m;
    float j;
    
public:
    Player(float x, float y, sparky::graphics::Window* window);
    
    void update() override;
    void render() override;
    
    bool isOutOfBounds(Entity* entity);
    void setPosition(float x, float y);
    void fission();
    void addAlpha(Alpha* alpha);
    void addGamma(Gamma* gamma);
    Alpha* getAlpha(int i) { return m_Alphas[i]; }
    const float getHealth() const { return m_Health; }
    void setHealth(float health) { m_Health = health; }
    inline const bool isSpinPositive() const { return m_PosSpin; }
    inline const unsigned int getAlphaCount() { return m_Alphas.size(); }
    inline std::vector<Alpha*> getAlphaList() { return m_Alphas; }
    void changeMoment(Moment* moment);
};