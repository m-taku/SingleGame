#pragma once
#include"EnemyState.h"
#include"../Path.h"

class EnemyStateMove :public EnemyState
{
public:
	EnemyStateMove(Enemy* enamy, Player* player);
	~EnemyStateMove();
	void Update();
private:
	int m_time = 0;
	Path path;
	CVector3 m_oldposition = CVector3::Zero();
	CVector3 m_nextpos = CVector3::Zero();
};

