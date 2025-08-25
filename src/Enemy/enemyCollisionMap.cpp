#include "Enemy/enemyCollisionMap.h"
#include "Enemy/enemy.h"

#include "Physics.h"
#include "Tile.h"
#include "Level.h"
#include "GlobalVariables.h"

#include <iostream>
#include <algorithm>
#include "array"
using namespace std;

CollisionMap::CollisionMap(ICollisionMapStrategy* direction, ICollisionMapStrategy* rect):
    m_Direction(direction), m_Rectangle(rect)
{}
CollisionMap::~CollisionMap()
{
    delete m_Direction;
    delete m_Rectangle;
}

void CollisionMap::DetectCollisionMap(Enemy& e, const Level& level)
{
    Vector2 cp, cn;
    float et = GetFrameTime();
    Vector2 nextPos = e.GetPosition() + e.getVelocity() * et;
    int minX = std::floor(std::min(e.position.x, nextPos.x) / (TILE_SIZE * SCALE));
    int minY = std::floor(std::min(e.position.y, nextPos.y) / (TILE_SIZE * SCALE));
    int maxX = std::floor(std::max(e.position.x + e.getHurtBox().width, nextPos.x + e.getHurtBox().width) / (TILE_SIZE * SCALE));
    int maxY = std::floor(std::max(e.position.y + e.getHurtBox().height, nextPos.y + e.getHurtBox().height) / (TILE_SIZE * SCALE));
    float t;

    if (e.getVelocity().x > 0)
    {
        for (int y = minY; y <= maxY; y++) {
            for (int x = minX; x <= maxX; x++) {
                if (x < 0 || y < 0 || x >= level.getGridWidth() || y >= level.getGridHeight()) continue;
                if (level.tileInstancesGrid[y][x]) {
                    if (aabb::CheckCollisionStaticRectDynamicRect(e.getHurtBox(), e.getVelocity(),
                        level.tileInstancesGrid[y][x]->bbox, cp, cn, t, et)) {
                        array<int, 2> temp = { y , x };
                        m_UnResolvedTiles.push_back({ temp , t });
                    }
                }
            }
        }
    }
    else
    {
        for (int y = maxY; y >= minY; y--) {
            for (int x = maxX; x >= minX; x--) {
                if (x < 0 || y < 0 || x >= level.getGridWidth() || y >= level.getGridHeight()) continue;
                if (level.tileInstancesGrid[y][x]) {
                    if (aabb::CheckCollisionStaticRectDynamicRect(e.getHurtBox(), e.getVelocity(),
                        level.tileInstancesGrid[y][x]->bbox, cp, cn, t, et)) {
                        array<int, 2> temp = { y , x };
                        m_UnResolvedTiles.push_back({ temp , t });
                    }
                }
            }
        }
    }

   
}

void CollisionMap::ResolveCollisionMap(Enemy& e, const Level& level)
{
    std::sort(m_UnResolvedTiles.begin(), m_UnResolvedTiles.end(), compare);
    for (auto& tileID : m_UnResolvedTiles) {
        Vector2 cp, cn;
        float ct = 0.0f;
        //re-check for de-collide
        if (aabb::CheckCollisionStaticRectDynamicRect(e.getHurtBox(), e.getVelocity(),
            level.tileInstancesGrid[tileID.first[0]][tileID.first[1]]->bbox, cp, cn, ct, GetFrameTime())) {
            e.setVelocityX(e.getVelocity().x + cn.x * abs(e.getVelocity().x) * (1 - ct));
            e.setVelocityY(e.getVelocity().y + cn.y * abs(e.getVelocity().y) * (1 - ct));

            //resolve contact
            Rectangle contactDirection = { cn.x,cn.y,0,0 };
            if (m_Direction) m_Direction->collide(e,contactDirection);
        }
        //rresolve extra

        if (&tileID == &m_UnResolvedTiles.back())
        {
            if (m_Rectangle)
            {
                m_Rectangle->collide(e, level.tileInstancesGrid[tileID.first[0]][tileID.first[1]]->bbox);
                cout << tileID.first[0] << "  " << tileID.first[1] << endl;
            }
        }
    }

    m_UnResolvedTiles.clear();
}

void CollisionMap::update(Enemy& e, const Level& level)
{
    DetectCollisionMap(e, level);
    ResolveCollisionMap(e, level);
}

//collision 
CollisionStrategyYJump::CollisionStrategyYJump(float mag):
	m_magnitude(mag)
{}
void CollisionStrategyYJump::collide(Enemy& e, Rectangle contactNormal)
{
    if (contactNormal.y < 0)
	e.setVelocityY(-m_magnitude);
}
void CollisionStrategyYPushOut::collide(Enemy& e, Rectangle contactNormal)
{
    e.position.y = (int)((e.position.y) / 32) * 32;
	e.setVelocityY(0);
}

void CollisionStrategyXReverse::collide(Enemy& e, Rectangle contactNormal)
{
    if ( contactNormal.x != 0)
	e.reverseDirection();

}
void CollisionStrategyXPushOut::collide(Enemy& e, Rectangle contactNormal)
{
    e.position.x = (int)((e.position.x) / 32) * 32;
    e.setVelocityX(0);
}

void CollisionStrategyXReverseLedge::collide(Enemy& e, Rectangle tile)
{
    Vector2 VertexPosition, Directon = { 0, TILE_SIZE * SCALE };
    Vector2 cp, cn;
    float t;

    if (e.getVelocity().x >= 0)
    {
        VertexPosition = Vector2{ e.getHurtBox().x + e.getHurtBox().width - 5,e.getHurtBox().y + e.getHurtBox().height };
        //cout << VertexPosition.x << endl;
        Directon.x = -5;
    }
    else
    {
        VertexPosition = Vector2{ e.getHurtBox().x + 5,e.getHurtBox().y + e.getHurtBox().height };
        Directon.x = 5;
    }

    //DrawLineV(VertexPosition, VertexPosition + Directon, ORANGE);

    if (aabb::CheckCollisionStaticRectDynamicRect(Rectangle{ VertexPosition.x,VertexPosition.y,0,0 }, Directon*5, tile, cp, cn, t, 1) == false)
    {
        e.reverseDirection();
    }
    

   /* if (aabb::CheckCollisionRecLine(VertexPosition, Directon, tile, cp, cn, t) == false)
    {
        
        e.reverseDirection();
    }*/

}

void CollisionStrategyState::collide(Enemy& e, Rectangle contactNormal)
{
    e.setIsCollidedMap();
}

void CollisionMapStrategyCombined::collide(Enemy& e, Rectangle contactNormal)
{
	for (auto s : m_strategies)
	{
		s->collide(e, contactNormal);
	}
}
void CollisionMapStrategyCombined::addStrategy(ICollisionMapStrategy* s)
{
	m_strategies.push_back(s);
}
CollisionMapStrategyCombined::~CollisionMapStrategyCombined()
{
	for (auto s : m_strategies)
	{
		delete s;
	}
}


//void CollisionMap::handleCollide(const Rectangle& A, const Rectangle& B)
//{
//    if (CheckOverlap(A, B))
//    {
//        //Detecting direction
//        if ((m_velocity.x < 0 && m_overlap.x > 0) || (m_velocity.x > 0 && m_overlap.x < 0))
//        {
//            if (m_velocity.y < 0)
//            {
//                m_choice = 1;
//                //do something for up
//            }
//            else if (m_velocity.y > 0)
//            {
//                m_choice = 2;
//                //down
//            }
//        }
//        if ((m_velocity.y < 0 && m_overlap.y > 0) || (m_velocity.y > 0 && m_overlap.y < 0))
//        {
//            m_choice = 3;
//            //left and right
//        }
//
//        //Handling
//        CalculateOverlap(A, B);
//
//        switch (m_choice)
//        {
//        case 1:
//        {
//
//            //down
//        }
//        case 2:
//        {
//
//            //up
//            break;
//        }
//
//        case 3:
//        {
//
//            //left right
//            break;
//        }
//
//        default:
//            break;
//        }
//    }
//}
//void CollisionMap::handleCollide(Enemy& e, const Level& level)
//{
//    //if (CheckCollision(e.GetBounds(), level))
//    //{
//    //    std::cout << "bruh";
//    //    Vector2 prev = e.getPrevPosition();
//    //    Rectangle now = e.GetBounds();
//    //    if (!CheckCollision(Rectangle{ prev.x,now.y,now.width,now.height}, level))
//    //    {
//    //       /* e.position.y = (int)((e.position.y + 16) / 32) * 32;
//    //        if (m_Y) m_Y->collide(e);*/
//
//    //        e.position.x = (int)((e.position.x ) / 32) * 32;
//    //        if (m_X) m_X->collide(e);
//
//    //    }else
//
//    //    if (!CheckCollision(Rectangle{ now.x,prev.y,now.width,now.height }, level))
//    //    {
//    //        /*e.position.x = (int)((e.position.x + 16) / 32) * 32;
//    //        if (m_X) m_X->collide(e);*/
//
//    //        e.position.y = (int)((e.position.y ) / 32) * 32;
//    //        if (m_Y) m_Y->collide(e);
//    //    }else
//
//    //    
//    //    {
//    //        e.position.x = (int)((e.position.x + 16) / 32) * 32;
//    //        e.position.y = (int)((e.position.y + 16) / 32) * 32;
//    //        if (m_X) m_X->collide(e);
//    //        if (m_Y) m_Y->collide(e);
//    //    }
//    //} 
//}


//void CollisionMap::CalculateOverlap(const Rectangle& A, const Rectangle& B)
//{
//    //A moving, B stand
//    if (m_velocity.x > 0)//right to left
//    {
//        m_overlap.x = B.x - (A.width + A.x); //negative
//    }
//    else if (m_velocity.x < 0)//left to right
//    {
//        m_overlap.x = (B.x + B.width) - A.x; //positive
//    }
//
//    if (m_velocity.y > 0)//up to down
//    {
//        m_overlap.y = B.y - (A.y + A.height);
//    }
//    else if (m_velocity.y < 0)//down to up
//    {
//        m_overlap.y = (B.y + B.height) - A.y;
//    }
//}