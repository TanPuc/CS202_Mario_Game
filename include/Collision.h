#ifndef COLLISION_H
#define COLLISION_H

#include <raylib.h>
#include <cmath>
#include <iostream>
#include <array>
#include <vector>

namespace aabb
{
    bool CheckCollisionRecLine(Vector2 &start, Vector2 &direction, Rectangle &rect,
                               Vector2 &contact_point, Vector2 &contact_normal, float &t_hit_near);

    bool CheckCollisionStaticRectDynamicRect(Rectangle &dynamic, Vector2 &velocity, Rectangle &r_static,
                                             Vector2 &contact_point, Vector2 &contact_normal, float &contact_time, float fElapsedTime);

    // Resolve collision by moving the dynamic rectangle out of the static rectangle
    bool ResolveStaticRectDynamicRect(Rectangle &dynamic, Vector2 &velocity, float fElapsedTime, Rectangle &r_static);
}

// Forward declaration
class Level;

class Collision
{
public:
    Vector2 contact_point, contact_normal;
    float contact_time = 0.0f;
    std::vector<std::pair<std::array<int, 2>, float>> z;

    void CheckCollision(Vector2 &position, Rectangle &bbox, Vector2 &velocity, Level &level);

    void PlayerVsLevel(Vector2 &position, Rectangle &bbox, Vector2 &velocity, Level &level);

    void MushroomVsLevel(Vector2& position, Rectangle& bbox, Vector2& velocity, Level& level);

    void FireBallVsLevel(Vector2& position, Rectangle& bbox, Vector2& velocity, Level& level);
};

Rectangle getSweptBBox(Vector2& position, Rectangle &bbox, Vector2 &velocity, float dt);

#endif // COLLISION_H