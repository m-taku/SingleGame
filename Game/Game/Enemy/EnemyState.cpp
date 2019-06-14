#include "stdafx.h"
#include "EnemyState.h"
#include"../../Player/Player.h"
#include"Enemy.h"

EnemyState::EnemyState(Enemy* enemy_point,const CVector3* pos)
{
	m_enemy = enemy_point;
	m_targetposition = pos;
}
EnemyState::~EnemyState()
{
}

