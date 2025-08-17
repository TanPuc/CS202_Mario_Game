#include "Enemy/enemyFSM.h"

#include "Enemy/enemyState.h"
#include "Enemy/enemyStateTransition.h"
#include "Enemy/enemyStateCondition.h"
#include "Enemy/enemyFSMBuilder.h"

void FiniteStateMachine::setInitialState(EnemyState* initial) {
    m_currentState = initial;
}
void FiniteStateMachine::runInitialState(Enemy& e)
{
    if (m_currentState) m_currentState->enter(e);
}

void FiniteStateMachine::addTransitions(vector<Transition>&& builder) {
    m_transitions = move(builder);
}
void FiniteStateMachine::addStateMap(unordered_map<StateType, EnemyState*>&& builder)
{
    m_stateMap = move(builder);
}

StateType FiniteStateMachine::getCurrentState()
{
    if (m_currentState) {
        return m_currentState->getName();
    }
    return StateType::Nothing;
}

void FiniteStateMachine::update(Enemy& e) {
    for (const auto& t : m_transitions) {
        if (t.m_from == m_currentState && t.m_condition->evaluate(e)) {
            m_currentState->exit(e);
            m_currentState = t.m_to;
            m_currentState->enter(e);
            break;
        }
    }
    if (m_currentState) m_currentState->update(e);
}

FiniteStateMachine::~FiniteStateMachine()
{
    for (auto& e : m_transitions)
    {
        delete e.m_condition;
        e.m_condition = nullptr;
    }
    for (auto& pair : m_stateMap) {
        delete pair.second;  
    }
    m_stateMap.clear();
}
