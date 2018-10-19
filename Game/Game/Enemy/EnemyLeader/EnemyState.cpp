#include "stdafx.h"
#include "EnemyState.h"
#include"../../Player/Player.h"
#include"Enemy.h"

EnemyState::EnemyState(Enemy* enemy_point,Player* pla)
{
	enemy = enemy_point;
	player = pla;
}
EnemyState::~EnemyState()
{
}

