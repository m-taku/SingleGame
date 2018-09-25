#pragma once
#include"EnemyState.h"

class EnemyStateMove :public EnemyState
{
public:
	EnemyStateMove(Enemy* enamy, Player* player);
	~EnemyStateMove();
	void Update();
private:
	int hanten = -1;
};

