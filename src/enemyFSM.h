#pragma once

#include <vector>
#include <unordered_map>

#include <enemyEnum.h>

using namespace std;

class EnemyState;
class EnemyStateCondition;
class Enemy;
class Transition;

class FiniteStateMachine
{
public:
    ~FiniteStateMachine();

    void setInitialState(EnemyState* initial);

    void addTransitions(vector<Transition>&&);
    void addStateMap(unordered_map<StateType, EnemyState*>&&);

    void update(Enemy& e);

private:
	EnemyState* m_currentState = nullptr;
	vector<Transition> m_transitions;
    unordered_map<StateType, EnemyState*> m_stateMap;
};
