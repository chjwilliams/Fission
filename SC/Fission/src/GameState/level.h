#pragma once

#include <iostream>
#include <vector>

#include "../../../Sparky-core/src/sparky.h"
#include "../Entity/entity.h"
#include "../Entity/levelobject.h"
#include "../Entity/player.h"
#include "../Entity/nucleus.h"
#include "../Entity/gamma.h"
#include "../Entity/flash.h"
#include "levellayer.h"
#include "uilayer.h"
#include "gamestate.h"


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
	friend class Flash;
	friend class Entity;
    friend class Player;
	friend class Nucleus;
    
private:
    float t;
	float flashcount;
    float j;
	unsigned int m_TopPts;
	unsigned int m_BottomPts;
	unsigned int m_TotalScore;
	bool m_CritMassTop;
	bool m_CritMassBtm;
	bool m_SuperCritMass;
	bool m_HyperCritMass;
	bool m_GameOver;
	bool m_IsFlash;
    std::vector<Entity*> m_Entities;
	std::vector<Nucleus*> m_Nuclei;
	std::vector<Gamma*> m_Gammas;
    std::vector<LevelObject*> m_Objects;
    sparky::graphics::Window* m_Window;
    sparky::graphics::Sprite* m_BG;
	sparky::graphics::Sprite* m_Overlay;
	sparky::graphics::Sprite* m_ShotDisplay;
	sparky::graphics::Label* m_TopLabel;
	sparky::graphics::Label* m_ShotCount;
	sparky::graphics::Label* m_BottomLabel;
	sparky::graphics::Group* m_TopUI;
	sparky::graphics::Group* m_BottomUI;
    sparky::maths::vec2 m_Offset;
    LevelLayer* m_LevelLayer;
	LevelLayer* m_HelpMenuLayer;
	UILayer* m_OverlayLayer;
	Flash* m_Flash;
    Player* m_Player;
    
public:
    Level(sparky::graphics::Window* window);
    ~Level();
    
	void addBackground(sparky::graphics::Sprite* background);

    void addEntity(Entity* entity);
    void addPlayer(Player* player);
	void addNucleus(Nucleus* nucleus);
	void addGamma(Gamma* gamma);
	void addFlash(Flash* flash);
    
	void populateLevel();

    void update();
    void render();
	void start();
	void endGame();
    
	void fission(Nucleus* nucleus);

    Player* getPlayer() const { return m_Player; }
	Nucleus* getNucleus(int i) { return m_Nuclei[i]; }
	const int nucleiCount() { m_Nuclei.size(); }

	std::vector<Nucleus*> getNuclei() { return m_Nuclei; }
    std::vector<LevelObject*> getObjects(const Entity* entity, float radius);
	std::vector<Entity*> getEntities() { return m_Entities; }


    inline const sparky::maths::vec2& getOffset() const { return m_Offset; }
    inline const unsigned long getNucleiCount() const { return 1; }
	void addPoints(int pts, bool top);
	void addScores();

	inline const int getTopScore() const { return m_TopPts; }
	inline const int getBtmScore() const { return m_BottomPts; }
	inline const bool getCritTop() const { return m_CritMassTop; }
	inline const bool getCritBtm() const { return m_CritMassBtm; }
	inline const bool getSuperCrit() const { return m_SuperCritMass; }
	inline const bool getHyperCrit() const { return m_HyperCritMass; }

	inline sparky::graphics::Window* getWindow() const { return m_Window; }
        
private:
    void setOffset(const sparky::maths::vec2& offset) { m_Offset = offset; }
    
};