#pragma once
#include <chrono>

#include "../../../Sparky-core/src/sparky.h"
#include "levelobject.h"


class Level;

enum Direction
{
    NONE = 0x0000, TOP = 0x000F, BOTTOM = 0x00F0, LEFT = 0x0F00, RIGHT = 0xF000
};


enum EntityType
{
    NIL, PLAYER, ENEMY, ALPHA, BETA, GAMMA, NEUTRON
};

class Entity
{
    struct Timer
    {
        typedef std::chrono::steady_clock clock ;
        typedef std::chrono::seconds seconds ;
        
        void reset() { start = clock::now() ; }
        
        unsigned long long seconds_elapsed() const
        { return std::chrono::duration_cast<seconds>( clock::now() - start ).count() ; }
        
    private:
        clock::time_point start = clock::now() ;
    };

protected:
    
    sparky::maths::vec3 m_Position;
	Timer m_Timer;
    bool m_Removed;
    bool m_Hit;
    bool m_Flinching;
    Level* m_Level;
    sparky::graphics::Sprite* m_Sprite;
    sparky::graphics::Renderable2D* m_Renderable;
	sparky::graphics::Window* m_Window;
    EntityType m_Type;
    float moveX;
    float moveY;
protected:
    Entity(float x, float y, sparky::graphics::Window* window);
    Direction m_CollisionDirection;
    
public:
    virtual ~Entity();
    virtual void init(Level* level);
    
    void move(float xdest, float ydest);
    
    virtual void update() = 0;
    virtual void render() = 0;
    
	void detectCollisions();
	void calculateNewVelocities(Entity* first, Entity* second);
    
    void remove(); 
    
    const bool isFlinching() const { return m_Flinching; }
    void flinchTimer();
    void setFlinching(bool flinching);
    
	bool outOfRange();

    inline const sparky::maths::vec3& getPosition() const { return m_Position; }
    inline const sparky::maths::vec2& getSize() const { return m_Sprite->getSize(); }
    inline sparky::maths::vec2 getCenter() const { return sparky::maths::vec2(m_Position.x + m_Sprite->getSize().x / 2.0f, m_Position.y + m_Sprite->getSize().y / 2.0f); }
	inline const float getRadius() const { return (m_Sprite->getSize().x / 2) * 0.6875; }
    inline sparky::graphics::Sprite* getSprite() const { return m_Sprite; }
    inline sparky::graphics::Renderable2D* getRenderable() const { return m_Renderable; }
    inline const bool getRemoved() const { return m_Removed; }
};