#include "level.h"

using namespace sparky;
using namespace graphics;
using namespace maths;
using namespace audio;

Level::Level(Window* window)
: m_Window(window)
{
    m_LevelLayer = new LevelLayer();
    addBackground(m_BG);
    addEnemy(new BasicEnemy(300, 350, 256, 256, m_Window));
    addPlayer(new Player(0, 0, m_Window));
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
    m_LevelLayer->add(player->getRenderable());
}

void Level::addEnemy(BasicEnemy* enemy)
{
    enemy->init(this);
    m_Enemies.push_back(enemy);
    m_LevelLayer->add(enemy->getRenderable());
}


void Level::addBeta(Beta* beta)
{
    beta->init(this);
    if (m_Player->getPosition().x < beta->getPosition().x)
        beta->moveX = -beta->moveX * sinf(j);
    
    if (m_Player->getPosition().y < beta->getPosition().y)
        beta->moveY = -beta->moveY * cosf(j);

    m_Betas.push_back(beta);
    m_LevelLayer->add(beta->getSprite());
}

void Level::addBackground(Sprite* background)
{
    background = new Sprite(0, 0, 960, 540, TextureManager::get("bg"));
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

std::vector<Entity*> Level::getEnemies()
{
    for (int i = 0; i < m_Enemies.size(); i++)
    {
        m_EnemyList.push_back(getEnemy(i));
    }
    return m_EnemyList;
}

void Level::update()
{
    /*
    for (int i = 0; i < m_Objects.size(); i++)
    {
        LevelObject* object = m_Objects[i];
        const vec2& pos = object->getPosition();
        if (object->isCollidable())
            object->getSprite()->position = vec3(pos.x - m_Offset.x, pos.y - m_Offset.y, 0);
        else
            object->getSprite()->position = vec3(pos.x - m_Offset.x * 0.3f, pos.y - m_Offset.y * 0.3f, 0);
    }
    */
    for (int i = 0; i < m_Entities.size(); i++)
    {
        const vec2& pos = m_Entities[i]->getPosition();
        m_Entities[i]->getSprite()->pp_position = vec3(pos.x - m_Offset.x, pos.y - m_Offset.y, 0);
        m_Entities[i]->render();
    }
    j += 5;
    t += 0.1;
    
    for (int i = 0; i < m_Enemies.size(); i++)
    {
        m_Enemies[i]->update();
        if ((m_Enemies[i]->collided(m_Player) && !m_Player->isFlinching()) || m_Player->collided(m_Enemies[i]))
            {
                m_Player->fission();
                //SoundManager::getSFX("damage")->play();
                getPlayer()->setFlinching(true);
                m_Enemies[i]->setFlinching(true);
                m_Enemies[i]->flinchTimer();
                m_Enemies[i]->getRenderable()->setSize(maths::vec2(m_Enemies[i]->getSize().x / 1.5f, m_Enemies[i]->getSize().y / 1.5f));
                getPlayer()->damage(10);
                addBeta(new Beta(getPlayer()->getPosition().x + sinf(j) * 100, getPlayer()->getPosition().y + cosf(j) * 100 , m_Window));
                addBeta(new Beta(getPlayer()->getPosition().x + cosf(j) * -100, getPlayer()->getPosition().y + sinf(j) * -100 , m_Window));
                addBeta(new Beta(getPlayer()->getPosition().x + sinf(j) * -100, getPlayer()->getPosition().y + cosf(j) * 100 , m_Window));
                //addBeta(new Beta(getPlayer()->getPosition().x + cosf(j) * -100, getPlayer()->getPosition().y + sinf(j) * 100 , m_Window));
                
                if (m_Player->isSpinPositive() == m_Enemies[i]->getPosSpin() && m_Enemies.size() < 8)
                {
                    addEnemy(new BasicEnemy(m_Enemies[i]->getPosition().x  +cosf(t) * 100 , m_Enemies[i]->getPosition().y + sinf(t) * 100, m_Enemies[i]->getSize().x / 1.5f, m_Enemies[i]->getSize().y / 1.5f, m_Window));
                    addEnemy(new BasicEnemy(m_Enemies[i]->getPosition().x  +cosf(t) * 100 , m_Enemies[i]->getPosition().y + sinf(t) * 100, m_Enemies[i]->getSize().x / 1.5f, m_Enemies[i]->getSize().y / 1.5f, m_Window));
                    m_Enemies[i]->remove();
                    //m_Enemies.erase(m_Enemies.begin() + i);
                }
            }
        if (m_Enemies[i]->getRemoved())
        {
            m_Enemies[i]->getSprite()->setPosition(maths::vec3(1000,1000,0));
            m_Enemies[i]->getRenderable()->setPosition(maths::vec3(1000,1000,0));
            m_Enemies.erase(m_Enemies.begin() + i);
        }
    }
    
    if (getPlayer()->isFlinching())
        getPlayer()->flinchTimer();
    /*
    for (int i = 0; i < m_Player->getAlphaList().size(); i++)
    {
        m_Player->getAlpha(i)->update();
        m_Player->getAlpha(i)->collidedList(getEnemies());
        
        if (m_Player->getAlpha(i)->getRemoved())
            m_Player->getAlpha(i)->setPosition(1000, 1000);
        
        if (m_Player->isOutOfBounds(m_Player->getAlpha(i)))
        {
            m_Player->getAlphaList().erase(m_Player->getAlphaList().begin() + i);
        }
        
    }
    */
    for (int i = 0; i < m_Betas.size(); i++)
    {
        m_Betas[i]->update();
        m_Betas[i]->collidedList(getEnemies());
        
         if (m_Betas[i]->getRemoved())
          m_Betas[i]->setPosition(1000, 1000);
        
        if (m_Player->isOutOfBounds(m_Betas[i]))
        {
            m_Betas.erase(m_Betas.begin() + i);
        }
    }
    
    
    
    if(t > 180)
        t = 0;
    
    m_Player->update();
}

void Level::render()
{
    m_LevelLayer->render();
    m_Player->render();
    
    for (BasicEnemy* enemies : m_Enemies)
        enemies->render();
    /*
    for (Alpha* alphas : m_Alphas)
        alphas->render();
     */
}