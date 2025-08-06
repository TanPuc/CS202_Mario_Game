#include "enemyFSMBuilder.h"
#include "enemyStateTransition.h"
#include "enemyEnum.h"
#include "enemyState.h"

FSMBuilder& FSMBuilder::addState(EnemyState* state) {
    m_stateMap[state->getName()] = state;
    return *this;
}

FSMBuilder& FSMBuilder::addTransition(StateType from, EnemyStateCondition* cond, StateType to) {
    m_transitions.emplace_back(m_stateMap[from], cond, m_stateMap[to]);
    return *this;
}

FSMBuilder& FSMBuilder::setInitialState(StateType name) {
    m_initialState = m_stateMap[name];
    return *this;
}

FiniteStateMachine* FSMBuilder::build() {
    auto fsm = new FiniteStateMachine();
    fsm->setInitialState(m_initialState);
    fsm->addTransitions(move(*this->m_transitions));
    fsm->addStateMap(move(*this->m_stateMap));
    return fsm;
}