#pragma once

#include <iostream>
#include <vector>

#include "../../../src/sparky.h"
#include "../Entity/entity.h"
#include "../Entity/levelobject.h"
#include "../Entity/player.h"
#include "../Entity/basicenemy.h"
#include "../Entity/alpha.h"
#include "../Entity/beta.h"
#include "../Entity/gamma.h"
#include "levellayer.h"


/*
    TODO: 
        Connect Sprite to Group.
        ALL: give points
        Gamma: Flux speed(?)
        Basic Enemy: If size is at 1/8 stop movement
        Connect Sprite and Renderable
        Reduce lag...
 
 */

class Level
{
    friend class Player;
    friend class BasicEnemy;
    
private:
    float t;
    float j;
    std::vector<Entity*> m_Entities;
    std::vector<BasicEnemy*> m_Enemies;
    std::vector<Entity*> m_EnemyList;
    std::vector<Beta*> m_Betas;
    std::vector<LevelObject*> m_Objects;
    sparky::graphics::Window* m_Window;
    sparky::graphics::Sprite* m_BG;
    sparky::maths::vec2 m_Offset;
    LevelLayer* m_LevelLayer;
    Player* m_Player;
    
public:
    Level(sparky::graphics::Window* window);
    ~Level();
    
    void addEntity(Entity* entity);
    void addPlayer(Player* player);
    void addEnemy(BasicEnemy* enemy);
    void addBeta(Beta* beta);
    
    void addBackground(sparky::graphics::Sprite* background);
    
    void update();
    void render();
    
    Player* getPlayer() const { return m_Player; }
    Beta* getBeta(int i) { return m_Betas[i]; }
    BasicEnemy* getEnemy(int i) { return m_Enemies[i] ; }
    
    std::vector<Entity*> getEnemies();
    std::vector<LevelObject*> getObjects(const Entity* entity, float radius);
    
    inline const sparky::maths::vec2& getOffset() const { return m_Offset; }
    inline const unsigned long getEnemyCount() const { return m_Enemies.size(); }
    
    inline sparky::graphics::Window* getWindow() { return m_Window; }
    
private:
    void setOffset(const sparky::maths::vec2& offset) { m_Offset = offset; }
    
};