#include "stdafx.h"
#include "EnemyState.h"
#include"../../Player/Player.h"
#include"Enemy.h"

EnemyState::EnemyState(Enemy* enemy_point,Player* pla)
{
	m_enemy = enemy_point;
	m_player = pla;
}
EnemyState::~EnemyState()
{
}

