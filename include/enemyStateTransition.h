#pragma once

class EnemyState;

class EnemyStateCondition;

struct Transition
{
	EnemyState* m_from;
	EnemyStateCondition* m_condition;
	EnemyState* m_to;

	Transition(EnemyState* from, EnemyStateCondition* cond, EnemyState* to) :
		m_from(from), m_condition(cond), m_to(to) {}
	~Transition() {
		delete m_condition;
		m_condition = nullptr;
	}
};