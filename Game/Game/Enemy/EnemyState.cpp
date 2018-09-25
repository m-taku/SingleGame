#include "stdafx.h"
#include "EnemyState.h"
#include"../Player.h"

EnemyState::EnemyState(Enemy* enemy_point,Player* pla)
{
	enemy = enemy_point;
	player = pla;
}
EnemyState::~EnemyState()
{
}
