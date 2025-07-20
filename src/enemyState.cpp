#include "enemy.h"
#include "enemyState.h"
#include "enemyMoveStrategy.h"

void AliveState::handleInput(Enemy& e, int input)
{
	if (input == 0)
	{
		e.setState(new DeadState());
	}
}
void AliveState::enter(Enemy& e)
{
	e.setStrategy(new MoveStrategyWander(,e));
}

void DeadState::handleInput(Enemy& e, int input)
{
	if (input == 3)
	{
		e.destroy();
	}
}
void DeadState::enter(Enemy& e)
{
	e.setStrategy(new DeadMoveStrategy());
}