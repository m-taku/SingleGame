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
	CVector3 m_oldposition = CVector3::Zero();					//1�t���[���O�̃|�W�V�����i�ǎC��Ȃǂ̔���ȂǂȂǁj
	CVector3 m_nextpos = CVector3::Zero();
};

