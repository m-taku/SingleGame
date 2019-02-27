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
	if (distance.Length() <= 150.0f)
	{
		m_enemy->ChangeLeaderState(Enemyleader::gathering);
		m_enemy->SetSpeed(0.0f);
		m_enemy->RollCall();
		return;
	}
	CVector3 speed = CVector3::Zero();
	speed = m_nextpos - nowpos;
	if (speed.Length() <= 50.0f)
	{
		m_nextpos = m_path->PathPos();
		if (m_nextpos.x == m_oldposition.x&&m_nextpos.y == m_oldposition.y&&m_nextpos.z == m_oldposition.z)
		{
			m_enemy->ChangeLeaderState(Enemyleader::gathering);
			m_enemy->SetSpeed(0.0f);
			m_enemy->RollCall();
			return;
		}
		m_oldposition = m_nextpos;
	}
	speed.y = 0.0;
	speed.Normalize();
	m_enemy->FindAngle(speed);
	m_enemy->SetSpeed(1.0f);
}