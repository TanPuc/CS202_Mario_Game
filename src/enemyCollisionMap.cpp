#include "enemyCollisionMap.h"
#include "enemy.h"
#include "Physics.h"

#include "iostream"
CollisionMap::CollisionMap(ICollisionMapStrategy* X, ICollisionMapStrategy* Y):
    m_X(X), m_Y(Y)
{}
CollisionMap::~CollisionMap()
{
    delete m_X;
    delete m_Y;
}
void CollisionMap::CalculateOverlap(const Rectangle& A, const Rectangle& B)
{
    //A moving, B stand
    if (m_velocity.x > 0)//right to left
    {
        m_overlap.x = B.x - (A.width + A.x); //negative
    }
    else if (m_velocity.x < 0)//left to right
    {
        m_overlap.x = (B.x + B.width) - A.x; //positive
    }

    if (m_velocity.y > 0)//up to down
    {
        m_overlap.y = B.y - (A.y + A.height);
    }
    else if (m_velocity.y < 0)//down to up
    {
        m_overlap.y = (B.y + B.height) - A.y;
    }
}



void CollisionMap::handleCollide(const Rectangle& A, const Rectangle& B)
{
    if (CheckOverlap(A, B))
    {
        //Detecting direction
        if ((m_velocity.x < 0 && m_overlap.x > 0) || (m_velocity.x > 0 && m_overlap.x < 0))
        {
            if (m_velocity.y < 0)
            {
                m_choice = 1;
                //do something for up
            }
            else if (m_velocity.y > 0)
            {
                m_choice = 2;
                //down
            }
        }
        if ((m_velocity.y < 0 && m_overlap.y > 0) || (m_velocity.y > 0 && m_overlap.y < 0))
        {
            m_choice = 3;
            //left and right
        }

        //Handling
        CalculateOverlap(A, B);

        switch (m_choice)
        {
        case 1:
        {

            //down
        }
        case 2:
        {

            //up
            break;
        }

        case 3:
        {

            //left right
            break;
        }

        default:
            break;
        }
    }
}
void CollisionMap::handleCollide(Enemy& e, const Level& level)
{
    if (CheckCollision(e.GetBounds(), level))
    {
        std::cout << "bruh";
        Vector2 prev = e.getPrevPosition();
        Rectangle now = e.GetBounds();
        if (CheckCollision(Rectangle{ prev.x,now.y,now.width,now.height}, level))
        {
            e.position.y = (int)((e.position.y + 16) / 32) * 32;
            if (m_Y) m_Y->collide(e);
        }
        else if (CheckCollision(Rectangle{ now.x,prev.x,now.width,now.height }, level))
        {
            e.position.x = (int)((e.position.x + 16) / 32) * 32;
            if (m_X) m_X->collide(e);
        }
        else 
        {
            e.position.x = (int)((e.position.x + 16) / 32) * 32;
            e.position.y = (int)((e.position.y + 16) / 32) * 32;
            if (m_X) m_X->collide(e);
            if (m_Y) m_Y->collide(e);
        }
    } 
}

CollisionStrategyYJump::CollisionStrategyYJump(float mag):
	m_magnitude(mag)
{}
void CollisionStrategyYJump::collide(Enemy& e)
{
	e.setVelocityY(m_magnitude);
}
void CollisionStrategyYPushOut::collide(Enemy& e)
{
	e.setVelocityY(0);
}

void CollisionStrategyXReverse::collide(Enemy& e)
{
	e.reverseDirection();

}
void CollisionStrategyXPushOut::collide(Enemy& e)
{
    e.setVelocityX(0);
}

void CollisionMapStrategyCombined::collide(Enemy& e)
{
	for (auto s : m_strategies)
	{
		s->collide(e);
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