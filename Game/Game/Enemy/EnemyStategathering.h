#pragma once
#include"EnemyState.h"
#include"../../Path.h"
class EnemyStategathering :public EnemyState
{
public:
	EnemyStategathering(Enemy* enamy, Player* player);
	~EnemyStategathering();
	void Update();
private:
	Path path;
	CVector3 m_oldposition = CVector3::Zero();					//1フレーム前のポジション（壁擦りなどの判定などなど）
	CVector3 m_nextpos = CVector3::Zero();
};

