#pragma once

#include <unordered_map>

#include "enemyFSM.h"
#include "enemyEnum.h"

class EnemyState;
struct Transition;

using namespace std;

class FSMBuilder
{
	unordered_map<StateType, EnemyState*> m_stateMap;
	EnemyState* m_initialState = nullptr;
	vector<Transition> m_transitions;

public:
    FSMBuilder& addState(EnemyState* state);

    FSMBuilder& addTransition(StateType from, EnemyStateCondition* cond, StateType to);

    FSMBuilder& setInitialState(StateType name);

    FiniteStateMachine* build();
};