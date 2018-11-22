#include "stdafx.h"
#include "EnemyStateAttack.h"
#include"../../Player/Player.h"
#include"Enemy.h"


EnemyStateAttack::EnemyStateAttack(Enemy* enamy, Player* player) :EnemyState(enamy, player)
{
	int num = enamy->CopyModel().GetSkeleton().GetNumBones();
	for (int i = 0; i < num;i++) {
		auto bonename = enamy->CopyModel().GetSkeleton().GetBone(i)->GetName();
		
		int result = wcscmp(L"Bip001 R Hand", bonename);
		if (result == 0)
		{
			enamy->CopyModel().GetSkeleton().GetBone(i);
			break;
		}
	}
}


EnemyStateAttack::~EnemyStateAttack()
{
}
void EnemyStateAttack::Update()
{

	m_player->Damage(0.001f);
	auto distance = m_player->Get2Dposition() - m_enemy->Get2DPosition();
	if (distance.Length() >= 200.0f)
	{
		//speed.y = 800.0f;
		//m_enemy->TransitionState(Enemy::State_Tracking);
	}
}