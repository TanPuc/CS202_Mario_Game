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
	Transition(Transition&& other) noexcept{
		m_from = other.m_from;
		m_to = other.m_to;
		m_condition = other.m_condition;

		other.m_condition = nullptr;
		other.m_from = nullptr;
		other.m_to = nullptr;
	}
	~Transition() {
		if (m_condition)
		{
			delete m_condition;
			m_condition = nullptr;
		}
	}
};