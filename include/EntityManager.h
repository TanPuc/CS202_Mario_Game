#ifndef ENTITY_MANAGER_H
#define ENTITY_MANAGER_H

#include <vector>
#include <memory>
#include "Entity.h"
#include "Level.h"

class EntityManager
{
private:
    std::vector<std::unique_ptr<Entity>> entities;

public:
    void AddEntity(std::unique_ptr<Entity> entity);
    void UpdateEntities(Level &level);
    void DrawEntities();
};

#endif // ENTITY_MANAGER_H