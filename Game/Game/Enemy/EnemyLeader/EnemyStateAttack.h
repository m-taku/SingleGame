#pragma once
#include"EnemyState.h"
class EnemyStateAttack :public EnemyState
{
public:
	EnemyStateAttack(Enemy* enamy, Player* player);
	~EnemyStateAttack();
	void Update();
private:
	int ja;
}; 

