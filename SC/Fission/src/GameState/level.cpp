#include "level.h"

using namespace sparky;
using namespace graphics;
using namespace maths;
using namespace audio;

Level::Level(Window* window)
: m_Window(window)
{
    m_LevelLayer = new LevelLayer();
	m_OverlayLayer = new UILayer();
	m_Overlay = new Sprite(0, 0, 960, 540, TextureManager::get("Overlay"));
	if (!GameState::isMenu())
		m_OverlayLayer->add(m_Overlay);
    addBackground(m_BG);
	if (!GameState::isMenu())
	{
		FontManager::get()->setScale(1.5, 1.5);
		m_TopUI = new Group(mat4::identity());
		m_TopLabel = new Label("", 10, 500, 0xffffffff);
		m_ShotDisplay = new Sprite(10, 470, 16, 16, TextureManager::get("Yellow"));
		m_ShotCount = new Label("", 30, 470, 0xffffffff);
		m_TopUI->add(m_ShotCount);
		m_TopUI->add(m_ShotDisplay);
		m_TopUI->add(m_TopLabel);
		m_BottomUI = new Group(mat4::identity());
		m_BottomLabel = new Label("", 10, 20, 0xffffffff);
		m_BottomUI->add(m_BottomLabel);
		m_OverlayLayer->add(m_TopUI);
		m_OverlayLayer->add(m_BottomUI);
		m_IsFlash = false;
		populateLevel();
		m_TopPts = 0;
		m_BottomPts = 0;
		m_CritMassTop = false;
		m_CritMassBtm = false;
		m_SuperCritMass = false;
		m_HyperCritMass = false;
	}
	flashcount = 0;
    t = 0.0f;
    j = 0.0f;
}

Level::~Level()
{
    
}

void Level::addEntity(Entity *entity)
{
    entity->init(this);
    m_Entities.push_back(entity);
    m_LevelLayer->add(entity->getRenderable());
}

void Level::addPlayer(Player *player)
{
    player->init(this);
    m_Player = player;
    m_OverlayLayer->add(player->getRenderable());
}

void Level::addNucleus(Nucleus* nucleus)
{
    nucleus->init(this);
    m_Nuclei.push_back(nucleus);
	m_Entities.push_back(nucleus);
    m_LevelLayer->add(nucleus->getRenderable());
}

void Level::addGamma(Gamma* gamma)
{
	gamma->init(this);
	m_Gammas.push_back(gamma);
	m_LevelLayer->add(gamma->getRenderable());
}

void Level::addFlash(Flash* flash)
{
	flash->init(this);
	m_Flash = flash;
	m_LevelLayer->add(flash->getRenderable());
}

void Level::addBackground(Sprite* background)
{
    background = new Sprite(0, 0, 960, 540, TextureManager::get("Background"));
    m_BG = background;
    m_LevelLayer->add(m_BG);
}

std::vector<LevelObject*> Level::getObjects(const Entity* entity, float radius)
{
    std::vector<LevelObject*> result;
    for (LevelObject* o : m_Objects)
    {
        if (entity->getCenter().distance(o->getCenter()) < radius)
            result.push_back(o);
    }
    return result;
}

void Level::populateLevel()
{
	addNucleus(new Nucleus(400, 400, 128, 128, true, m_Window));
	addNucleus(new Nucleus(100, 500, 128, 128, true, m_Window));
	//addNucleus(new Nucleus(200, 500, 128, 128, true, m_Window));
	//addNucleus(new Nucleus(100, 300, 128, 128, true, m_Window));
	addNucleus(new Nucleus(400, 400, 128, 128, true, m_Window));
	addNucleus(new Nucleus(500, 400, 128, 128, true, m_Window));
	addNucleus(new Nucleus(800, 300, 128, 128, true, m_Window));
	addNucleus(new Nucleus(100, 450, 128, 128, true, m_Window));
	addNucleus(new Nucleus(400, 200, 128, 128, false, m_Window));
	addNucleus(new Nucleus(100, 200, 128, 128, false, m_Window));
	addNucleus(new Nucleus(200, 200, 128, 128, false, m_Window));
	addNucleus(new Nucleus(100, 100, 128, 128, false, m_Window));
	addNucleus(new Nucleus(400, 100, 128, 128, false, m_Window));
	//addNucleus(new Nucleus(500, 250, 128, 128, false, m_Window));
	//addNucleus(new Nucleus(600, 150, 128, 128, false, m_Window));
	addNucleus(new Nucleus(100, 250, 128, 128, false, m_Window));
}

void Level::addScores()
{
	if (m_TopPts > 500)
	{
		m_CritMassTop = true;
	}
	if (m_BottomPts > 500)
	{
		m_CritMassBtm = true;
	}
	if (m_TopPts == m_BottomPts)
	{
		m_SuperCritMass = true;
	}
	if (m_TopPts == m_BottomPts && m_TopPts > 700)
	{
		m_HyperCritMass = true;
	}
}

void Level::addPoints(int pts, bool top)
{
	SoundManager::get("Points")->play();
	if (top)
		m_TopPts += pts;
	else
		m_BottomPts += pts;
}

void Level::fission(Nucleus* nucleus)
{
	float t;

	addFlash(new Flash(nucleus->getPosition().x, nucleus->getPosition().y, m_Window));
	m_IsFlash = true;
	t = rand() % 360;
	addNucleus(new Nucleus(nucleus->getPosition().x + cosf(t) * 100, nucleus->getPosition().y + sinf(t) * 100, nucleus->getSize().x / 1.5f, nucleus->getSize().y / 1.5f, nucleus->getIsTop(), m_Window));
	t = rand() % 360;
	addNucleus(new Nucleus(nucleus->getPosition().x + cosf(t) * 100, nucleus->getPosition().y + sinf(t) * 100, nucleus->getSize().x / 1.5f, nucleus->getSize().y / 1.5f, nucleus->getIsTop(), m_Window));
	

	if (m_Gammas.size() < 8)
	{
		t = rand() % 360;
		addGamma(new Gamma(nucleus->getPosition().x + cosf(t) * 50, nucleus->getPosition().y + sinf(t) * 50, m_Window));
		t = rand() % 360;
		addGamma(new Gamma(nucleus->getPosition().x + cosf(t) * 50, nucleus->getPosition().y + sinf(t) * 50, m_Window));
		t = rand() % 360;
		addGamma(new Gamma(nucleus->getPosition().x + cosf(t) * 50, nucleus->getPosition().y + sinf(t) * 50, m_Window));
	}
}


void Level::update()
{
	if (m_GameOver)
	{
		if (GameState::isMenu())
			return;
	}

	m_TopLabel->text = "TScore: " + std::to_string(m_TopPts);
	m_BottomLabel->text = "BScore: " + std::to_string(m_BottomPts);
	m_ShotCount->text = std::to_string(m_Player->getShots());

    for (int i = 0; i < m_Entities.size(); i++)
    {
		if (m_GameOver)
			break;

        const vec2& pos = m_Entities[i]->getPosition();
        m_Entities[i]->getSprite()->position = vec3(pos.x, pos.y, 0);

		if (m_Entities[i]->outOfRange())
		{
			m_Entities[i]->remove();
		}

        m_Entities[i]->render();
    }

    j += 5;
    t += 0.1;

	for (int i = 0; i < m_Nuclei.size(); i++)
		m_Nuclei[i]->update();
    
	for (int i = 0; i < m_Nuclei.size(); i++)
	{
		m_Nuclei[i]->detectCollisions();
		if (m_Player->hasFired())
		{	
			if (m_Player->getNeutron()->getCenter().distance(m_Nuclei[i]->getCenter()) 
				< m_Player->getNeutron()->getRadius() + m_Nuclei[i]->getRadius())
			{
				if (m_Nuclei[i]->getIsTop())
					m_TopPts += 33;
				if (!m_Nuclei[i]->getIsTop())
					m_BottomPts += 33;

				m_Player->getNeutron()->calculateNewVelocities(m_Player->getNeutron(), m_Nuclei[i]);
				std::cout << "HIT" << std::endl;
				SoundManager::get("Boom")->play();
				SoundManager::get("Points")->play();
				fission(m_Nuclei[i]);
				m_Nuclei[i]->remove();
				if (m_Nuclei[i]->getRemoved())
				{
					m_Nuclei[i]->setPosition(1000, 1000);
					m_Nuclei[i]->getSprite()->setPosition(maths::vec3(1000, 1000, 0));
					m_Nuclei.erase(m_Nuclei.begin() + i);
				}
			}
		}
		
    }
    
    for (int i = 0; i < m_Gammas.size(); i++)
    {
		m_Gammas[i]->update();
		m_Gammas[i]->detectCollisions();
        
		//if (m_Gammas[i]->getRemoved())
			//m_Gammas[i]->setPosition(1000, 1000);
        
		if (m_Player->isOutOfBounds(m_Gammas[i]))
        {
			//m_Gammas.erase(m_Gammas.begin() + i);
        }
        
    }

	if (m_IsFlash)
	{
		flashcount++;
		m_Flash->update();
	}

	if (flashcount > 10)
	{
		flashcount = 0;
		m_IsFlash = false;
		m_LevelLayer->remove(m_Flash);
		m_Flash->setIntensity(1);
	}

    if(t > 180)
        t = 0;
    
    m_Player->update();
	
}

void Level::render()
{
	if (GameState::isMenu())
	{
		m_OverlayLayer->render();
		//m_Player->render();
	}
	else
	{

		m_LevelLayer->render();
		if (m_IsFlash)
			m_Flash->render();
		m_OverlayLayer->render();
		m_Player->render();

		for (Nucleus* nucleus : m_Nuclei)
			nucleus->render();
	}

}

void Level::start()
{

}

void Level::endGame()
{
	if (m_GameOver)
		return;

	m_GameOver = true;
}