#include "Collision.h"
#include "Level.h"
#include "Tile.h"
#include <iostream>

namespace aabb
{
    bool CheckCollisionRecLine(Vector2 &start, Vector2 &direction, Rectangle &rect,
                               Vector2 &contact_point, Vector2 &contact_normal, float &t_hit_near)
    {
        contact_normal = {0, 0};
        contact_point = {0, 0};

        Vector2 inverse_direction = Vector2{1.0f / direction.x, 1.0f / direction.y};

        Vector2 t_near = Vector2{(rect.x - start.x) * inverse_direction.x, (rect.y - start.y) * inverse_direction.y};
        Vector2 t_far = Vector2{(rect.x + rect.width - start.x) * inverse_direction.x, (rect.y + rect.height - start.y) * inverse_direction.y};

        if (std::isnan(t_far.y) || std::isnan(t_far.x))
            return false;
        if (std::isnan(t_near.y) || std::isnan(t_near.x))
            return false;

        if (t_near.x > t_far.x)
            std::swap(t_near.x, t_far.x);
        if (t_near.y > t_far.y)
            std::swap(t_near.y, t_far.y);

        if (t_near.x > t_far.y || t_near.y > t_far.x)
            return false;

        t_hit_near = std::max(t_near.x, t_near.y);

        float t_hit_far = std::min(t_far.x, t_far.y);

        if (t_hit_far < 0)
            return false;

        contact_point.x = start.x + t_hit_near * direction.x;
        contact_point.y = start.y + t_hit_near * direction.y;

        if (t_near.x > t_near.y)
        {
            if (inverse_direction.x < 0)
                contact_normal = {1, 0};
            else
                contact_normal = {-1, 0};
        }
        else
        {
            if (t_near.x < t_near.y)
            {
                if (inverse_direction.y < 0)
                    contact_normal = {0, 1};
                else
                    contact_normal = {0, -1};
            }
        }
        return true;
    }

    bool CheckCollisionStaticRectDynamicRect(Rectangle &dynamic, Vector2 &velocity, Rectangle &r_static,
                                             Vector2 &contact_point, Vector2 &contact_normal, float &contact_time, float fElapsedTime)
    {
        contact_time = 0.0f;

        if (velocity.x == 0 && velocity.y == 0)
            return false;

        Rectangle expanded_target = Rectangle{r_static.x - dynamic.width / 2.0f, r_static.y - dynamic.height / 2.0f,
                                              r_static.width + dynamic.width, r_static.height + dynamic.height};

        Vector2 sourceCenPos = {dynamic.x + dynamic.width / 2.0f, dynamic.y + dynamic.height / 2.0f};
        Vector2 dir = {velocity.x * fElapsedTime, velocity.y * fElapsedTime};

        if (CheckCollisionRecLine(sourceCenPos, dir, expanded_target, contact_point, contact_normal, contact_time))
        {
            return (contact_time >= 0.0f && contact_time < 1.0f);
        }
        else
            return false;
    }

    bool ResolveStaticRectDynamicRect(Rectangle &dynamic, Vector2 &velocity, float fElapsedTime, Rectangle &r_static)
    {
        Vector2 cp, cn;
        float ct = 0.0f;
        if (CheckCollisionStaticRectDynamicRect(dynamic, velocity, r_static, cp, cn, ct, fElapsedTime))
        {
            velocity.x += cn.x * std::abs(velocity.x) * (1 - ct);
            velocity.y += cn.y * std::abs(velocity.y) * (1 - ct);
            return true;
        }
        return false;
    }
}

void Collision::CheckCollision(Vector2 &position, Rectangle &bbox, Vector2 &velocity, Level &level)
{
    float dt = GetFrameTime();
    Vector2 nextPos = {position.x + velocity.x * dt, position.y + velocity.y * dt};
    int minX = std::floor(std::min(position.x, nextPos.x) / (TILE_SIZE * SCALE));
    int minY = std::floor(std::min(position.y, nextPos.y) / (TILE_SIZE * SCALE));
    int maxX = std::floor(std::max(position.x + bbox.width, nextPos.x + bbox.width) / (TILE_SIZE * SCALE));
    int maxY = std::floor(std::max(position.y + bbox.height, nextPos.y + bbox.height) / (TILE_SIZE * SCALE));

    for (int y = minY; y <= maxY; y++)
    {
        for (int x = minX; x <= maxX; x++)
        {
            // Assume that player will never go out of grid map in x-direction
            if (x < 0 || x >= GRID_WIDTH || y < 0 || y >= GRID_HEIGHT)
                continue;
            if (level.tileInstancesGrid[y][x])
            {
                if (aabb::CheckCollisionStaticRectDynamicRect(bbox, velocity,
                                                              level.tileInstancesGrid[y][x]->bbox, contact_point, contact_normal, contact_time, dt))
                {
                    std::array<int, 2> temp = {y, x};
                    z.push_back({temp, contact_time});
                }
            }
        }
    }
}

void Collision::PlayerVsLevel(Vector2 &position, Rectangle &bbox, Vector2 &velocity, Level &level)
{
    float tile_size = TILE_SIZE * SCALE;
    float dt = GetFrameTime();
    Vector2 nextPos = {position.x + velocity.x * dt, position.y + velocity.y * dt};
    float minX = std::min(position.x, nextPos.x);
    float minY = std::min(position.y, nextPos.y);
    float maxX = std::max(position.x + bbox.width, nextPos.x + bbox.width);
    float maxY = std::max(position.y + bbox.height, nextPos.y + bbox.height);
    float min_coordinate_X = minX / tile_size;
    float min_coordinate_Y = minY / tile_size;
    float max_coordinate_X = maxX / tile_size;
    float max_coordinate_Y = maxY / tile_size;

    for (int y = min_coordinate_Y; y <= max_coordinate_Y; y++)
    {
        for (int x = min_coordinate_X; x <= max_coordinate_X; x++)
        {
            if (x < 0 || x >= level.getGridWidth() || y < 0 || y >= level.getGridHeight())
                continue;
            if (level.getTileInstance(y, x))
            {
                // Check collision with the original bounding box of interactble tiles
                // since we need to update bounding box for animation
                auto brick = dynamic_cast<BrickInstance *>(level.getTileInstance(y, x).get());
                auto question = dynamic_cast<QuestionInstance *>(level.getTileInstance(y, x).get());
                Rectangle tileBBox = brick ? brick->getOriginalBBox() : (question ? question->getOriginalBBox() : level.getTileInstance(y, x)->bbox);

                auto hidden = dynamic_cast<HiddenBlockInstance *>(level.getTileInstance(y, x).get());

                if (aabb::CheckCollisionStaticRectDynamicRect(bbox, velocity, tileBBox, contact_point, contact_normal, contact_time, dt))
                {
                    std::array<int, 2> temp = {y, x};
                    z.push_back({temp, contact_time});

                    if (hidden)
                    {
                        hidden->handleActivation();
                    }
                }
            }
        }
    }

    std::sort(z.begin(), z.end(), compare);
    for (auto j : z)
    {
        Vector2 cp, cn;
        float ct = 0.0f;

        auto brick = dynamic_cast<BrickInstance *>(level.getTileInstance(j.first[0], j.first[1]).get());
        auto question = dynamic_cast<QuestionInstance *>(level.getTileInstance(j.first[0], j.first[1]).get());
        Rectangle tileBBox = brick ? brick->getOriginalBBox() : (question ? question->getOriginalBBox() : level.getTileInstance(j.first[0], j.first[1])->bbox);

        if (aabb::CheckCollisionStaticRectDynamicRect(bbox, velocity, tileBBox, cp, cn, ct, dt))
        {
            velocity.x += cn.x * std::abs(velocity.x) * (1 - ct);
            velocity.y += cn.y * std::abs(velocity.y) * (1 - ct);
        }
    }
    z.clear();

    // Check collision with platforms
    Rectangle playerSweptBBox = getSweptBBox(position, bbox, velocity, dt);
    for (const auto &platform : level.entityManager.platforms)
    {
        if (CheckCollisionRecs(playerSweptBBox, platform->bbox))
        {
            aabb::ResolveStaticRectDynamicRect(bbox, velocity, dt, platform->bbox);
        }
    }
}

void Collision::MushroomVsLevel(Vector2 &position, Rectangle &bbox, Vector2 &velocity, Level &level)
{
    float tile_size = TILE_SIZE * SCALE;
    float dt = GetFrameTime();
    Vector2 nextPos = {position.x + velocity.x * dt, position.y + velocity.y * dt};
    float minX = std::min(position.x, nextPos.x);
    float minY = std::min(position.y, nextPos.y);
    float maxX = std::max(position.x + bbox.width, nextPos.x + bbox.width);
    float maxY = std::max(position.y + bbox.height, nextPos.y + bbox.height);
    float min_coordinate_X = minX / tile_size;
    float min_coordinate_Y = minY / tile_size;
    float max_coordinate_X = maxX / tile_size;
    float max_coordinate_Y = maxY / tile_size;

    for (int y = min_coordinate_Y; y <= max_coordinate_Y; y++)
    {
        for (int x = min_coordinate_X; x <= max_coordinate_X; x++)
        {
            if (x < 0 || x >= level.getGridWidth() || y < 0 || y >= level.getGridHeight())
                continue;
            if (level.getTileInstance(y, x))
            {
                if (aabb::CheckCollisionStaticRectDynamicRect(bbox, velocity,
                                                              level.getTileInstance(y, x)->bbox, contact_point, contact_normal, contact_time, dt))
                {
                    std::array<int, 2> temp = {y, x};
                    z.push_back({temp, contact_time});
                }
            }
        }
    }
    std::sort(z.begin(), z.end(), compare);
    for (auto j : z)
    {
        Vector2 cp, cn;
        float ct = 0.0f;
        if (aabb::CheckCollisionStaticRectDynamicRect(bbox, velocity, level.getTileInstance(j.first[0], j.first[1])->bbox, cp, cn, ct, dt))
        {
            velocity.y += cn.y * std::abs(velocity.y) * (1 - ct);
            if (cn.x != 0)
            {
                velocity.x *= -1; // Reflect if faces wall
            }
            else
            {
                velocity.x += cn.x * std::abs(velocity.x) * (1 - ct);
            }
        }
    }
    z.clear();

    for (int y = min_coordinate_Y; y <= max_coordinate_Y + 1; y++)
    {
        for (int x = min_coordinate_X; x <= max_coordinate_X; x++)
        {
            if (x < 0 || x >= level.getGridWidth() || y < 0 || y >= level.getGridHeight())
                continue;
            if (level.getTileInstance(y, x))
            {
                if (CheckCollisionRecs(bbox, level.getTileInstance(y, x)->bbox))
                {
                    if (level.getTileInstance(y, x)->getState() == STATE_INTERACTED)
                    {
                        velocity.y -= 40.0f;
                    }
                }
            }
        }
    }
}

void Collision::FireBallVsLevel(Vector2 &position, Rectangle &bbox, Vector2 &velocity, Level &level)
{
    CheckCollision(position, bbox, velocity, level);
    float dt = GetFrameTime();
    std::sort(z.begin(), z.end(), compare);
    for (auto j : z)
    {
        Vector2 cp, cn;
        float ct = 0.0f;
        if (aabb::CheckCollisionStaticRectDynamicRect(bbox, velocity, level.getTileInstance(j.first[0], j.first[1])->bbox, cp, cn, ct, dt))
        {
            velocity.x += cn.x * std::abs(velocity.x) * (1 - ct);
            velocity.y += cn.y * std::abs(velocity.y) * (1 - ct);
        }
    }
    z.clear();
}

bool Collision::IsCollideWithLevel(Vector2 &position, Rectangle &bbox, Vector2 &velocity, Level &level)
{
    float dt = GetFrameTime();
    Vector2 nextPos = {position.x + velocity.x * dt, position.y + velocity.y * dt};
    int minX = std::floor(std::min(position.x, nextPos.x) / (TILE_SIZE * SCALE));
    int minY = std::floor(std::min(position.y, nextPos.y) / (TILE_SIZE * SCALE));
    int maxX = std::floor(std::max(position.x + bbox.width, nextPos.x + bbox.width) / (TILE_SIZE * SCALE));
    int maxY = std::floor(std::max(position.y + bbox.height, nextPos.y + bbox.height) / (TILE_SIZE * SCALE));

    for (int y = minY; y <= maxY; y++)
    {
        for (int x = minX; x <= maxX; x++)
        {
            // Assume that player will never go out of grid map in x-direction
            if (x < 0 || x >= GRID_WIDTH || y < 0 || y >= GRID_HEIGHT)
                continue;
            if (level.tileInstancesGrid[y][x])
            {
                if (aabb::CheckCollisionStaticRectDynamicRect(bbox, velocity,
                                                              level.tileInstancesGrid[y][x]->bbox, contact_point, contact_normal, contact_time, dt))
                {
                    return true;
                }
            }
        }
    }
    return false;
}

bool Collision::IsCollideWithLevelHorizontally(Vector2 &position, Rectangle &bbox, Vector2 &velocity, Level &level)
{
    float dt = GetFrameTime();
    Vector2 nextPos = {position.x + velocity.x * dt, position.y + velocity.y * dt};
    int minX = std::floor(std::min(position.x, nextPos.x) / (TILE_SIZE * SCALE));
    int minY = std::floor(std::min(position.y, nextPos.y) / (TILE_SIZE * SCALE));
    int maxX = std::floor(std::max(position.x + bbox.width, nextPos.x + bbox.width) / (TILE_SIZE * SCALE));
    int maxY = std::floor(std::max(position.y + bbox.height, nextPos.y + bbox.height) / (TILE_SIZE * SCALE));

    for (int y = minY; y <= maxY; y++)
    {
        for (int x = minX; x <= maxX; x++)
        {
            // Assume that player will never go out of grid map in x-direction
            if (x < 0 || x >= GRID_WIDTH || y < 0 || y >= GRID_HEIGHT)
                continue;
            if (level.tileInstancesGrid[y][x])
            {
                if (aabb::CheckCollisionStaticRectDynamicRect(bbox, velocity,
                                                              level.tileInstancesGrid[y][x]->bbox, contact_point, contact_normal, contact_time, dt))
                {
                    return contact_normal.x != 0;
                }
            }
        }
    }
    return false;
}

bool Collision::IsCollideWithLevelVertically(Vector2 &position, Rectangle &bbox, Vector2 &velocity, Level &level)
{
    float dt = GetFrameTime();
    Vector2 nextPos = {position.x + velocity.x * dt, position.y + velocity.y * dt};
    int minX = std::floor(std::min(position.x, nextPos.x) / (TILE_SIZE * SCALE));
    int minY = std::floor(std::min(position.y, nextPos.y) / (TILE_SIZE * SCALE));
    int maxX = std::floor(std::max(position.x + bbox.width, nextPos.x + bbox.width) / (TILE_SIZE * SCALE));
    int maxY = std::floor(std::max(position.y + bbox.height, nextPos.y + bbox.height) / (TILE_SIZE * SCALE));

    for (int y = minY; y <= maxY; y++)
    {
        for (int x = minX; x <= maxX; x++)
        {
            // Assume that player will never go out of grid map in x-direction
            if (x < 0 || x >= GRID_WIDTH || y < 0 || y >= GRID_HEIGHT)
                continue;
            if (level.tileInstancesGrid[y][x])
            {
                if (aabb::CheckCollisionStaticRectDynamicRect(bbox, velocity,
                                                              level.tileInstancesGrid[y][x]->bbox, contact_point, contact_normal, contact_time, dt))
                {
                    return contact_normal.y != 0;
                }
            }
        }
    }
    return false;
}

Rectangle getSweptBBox(Vector2 &position, Rectangle &bbox, Vector2 &velocity, float dt)
{
    Vector2 nextPos = {position.x + velocity.x * dt, position.y + velocity.y * dt};
    float minX = std::min(position.x, nextPos.x);
    float minY = std::min(position.y, nextPos.y);
    float maxX = std::max(position.x + bbox.width, nextPos.x + bbox.width);
    float maxY = std::max(position.y + bbox.height, nextPos.y + bbox.height);
    return Rectangle{minX, minY, maxX - minX, maxY - minY};
}