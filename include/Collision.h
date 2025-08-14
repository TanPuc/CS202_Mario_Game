#ifndef COLLISION_H
#define COLLISION_H

#include <raylib.h>
#include <cmath>
#include <iostream>

namespace aabb {
    bool CheckCollisionRecLine( Vector2& start, Vector2& direction, Rectangle& rect,
    Vector2& contact_point, Vector2& contact_normal, float& t_hit_near);

    bool CheckCollisionStaticRectDynamicRect(Rectangle& dynamic, Vector2& velocity, Rectangle& r_static,
    Vector2& contact_point, Vector2& contact_normal, float& contact_time, float fElapsedTime);

    bool ResolveStaticRectDynamicRect ( Rectangle& dynamic, Vector2& velocity, float fElapsedTime, Rectangle& r_static );
}

#endif // COLLISION_H