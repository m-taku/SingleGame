#pragma once
#include"EnemyState.h"
class EnemyStateTracking:public EnemyState
{
public:
	EnemyStateTracking(Enemy* enemy, Player* player);
	~EnemyStateTracking();
	void Update();
	
private:
	int hanten = 1;
	VectorDraw* kasa = nullptr;
};

