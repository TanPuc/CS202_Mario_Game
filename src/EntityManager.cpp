#include "EntityManager.h"
#include <algorithm>

void EntityManager::AddEntity(std::unique_ptr<Entity> entity)
{
    if (entity)
    {
        entities.push_back(std::move(entity));
    }
}

void EntityManager::UpdateEntities(Level &level)
{
    for (auto &entity : entities)
    {
        if (entity)
        {
            entity->Update(level);
        }
    }

    // Remove destroyed entities (optional)
    for (auto it = entities.begin(); it != entities.end();)
    {
        if (!(*it)->isActive)
        {
            it = entities.erase(it);
        }
        else
        {
            ++it;
        }
    }
}

void EntityManager::DrawEntities()
{
    for (const auto &entity : entities)
    {
        if (entity)
        {
            entity->Draw();
        }
    }
}