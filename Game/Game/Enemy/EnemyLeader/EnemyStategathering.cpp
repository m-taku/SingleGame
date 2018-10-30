#include "stdafx.h"
#include "EnemyStategathering.h"
#include"Enemy.h"



EnemyStategathering::EnemyStategathering(Enemy* enamy, Player* player) :EnemyState(enamy, player)
{
	path.course(enemy->GetLeaderposition(), enemy->Get3Dposition());
	m_nextpos = path.Pathpos();
}

EnemyStategathering::~EnemyStategathering()
{
}
void EnemyStategathering::Update()
{

}