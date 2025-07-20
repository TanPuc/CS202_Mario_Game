#pragma once

class Enemy;

class EnemyState
{
public:

	virtual void enter(Enemy& enemy) = 0;
	virtual void handleInput(Enemy& enemy, int input) = 0;
	virtual void update(Enemy& enemy) = 0;
private:

};

class AliveState : public EnemyState
{
public:

	void enter(Enemy& e) override;
	void handleInput(Enemy& enemy, int input) override;
	void update(Enemy& enemy) override;
private:
};

class DeadState : public EnemyState
{
public:

	void enter(Enemy& e) override;
	void handleInput(Enemy& enemy, int input) override;
	void update(Enemy& enemy) override;
private:
};