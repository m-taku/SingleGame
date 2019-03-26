#include "stdafx.h"
#include "EnemyStategathering.h"
#include"Enemy.h"
EnemyStategathering::EnemyStategathering(Enemy* enamy, Player* player) :EnemyState(enamy, player)
{
	m_path = m_enemy->CopyPath();
	m_path->Course(m_enemy->GetLeaderPosition(), m_enemy->Get3DPosition());
	m_nextpos = m_path->PathPos();
}

EnemyStategathering::~EnemyStategathering()
{
}
void EnemyStategathering::Update()
{
	CVector3 nowpos = m_enemy->Get3DPosition();
	nowpos.y = 0.0f;
	auto leaderpos = m_enemy->GetLeaderPosition();
	leaderpos.y = 0;
	CVector3 distance = leaderpos - nowpos;
	m_enemy->ChangeAnimation(Enemy::walk);
	CVector3 speed = CVector3::Zero();
	if (distance.Length() <= 150.0f)
	{
		m_enemy->SetSpeed(0.0f);
		m_enemy->RollCall();
		return;
	}
	speed = m_nextpos - nowpos;
	//ƒ|ƒŠƒSƒ“‚ð“à•ï‚·‚é‰~‚É“ü‚Á‚½‚ç
	if (speed.Length() <= 100.0f)
	{
		//ŽŸ‚ÌƒpƒX‚ðŒŸõ‚·‚é
		m_nextpos = m_path->PathPos();
		if (m_nextpos.x == m_oldposition.x&&m_nextpos.y == m_oldposition.y&&m_nextpos.z == m_oldposition.z)
		{
			//‚à‚µ‚àI“_‚È‚ç‚Î’Tõ‚µ‚È‚¨‚·
			m_path->Course(m_enemy->Get2DPosition(), m_player->Get2Dposition());
			m_nextpos = m_path->PathPos();
		}
		m_oldposition = m_nextpos;
		speed = m_nextpos - nowpos;
	}
	speed.y = 0.0;
	speed.Normalize();
	m_enemy->AddAngle(speed);
}