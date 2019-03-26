#include "stdafx.h"
#include "EnemyStateAttack.h"
#include"../../Player/Player.h"
//#include"../HitObjict.h"
#include "Physics/CollisionAttr.h"
#include"Enemy.h"
namespace {
	//剣のサイズ（aabb用）(縦、横、高さ)
	const CVector3 SWODSIZE = { 10.0f, 10.0f,80.0f };
}
EnemyStateAttack::EnemyStateAttack(Enemy* enamy, Player* player) :EnemyState(enamy, player)
{
	m_boneNo = m_enemy->GetNo();
}
EnemyStateAttack::~EnemyStateAttack()
{
}
void EnemyStateAttack::Update()
{
	auto distance = m_player->Get2DPosition() - m_enemy->Get2DPosition();
	switch (m_steat)
	{
	case Wait:
		if (distance.Length() <= 200.0f) {
			m_enemy->AddAngle(distance);
			m_enemy->SetSpeed(0.0f);
			m_enemy->ChangeAnimation(Enemy::idle);
			count++;
			if (distance.Length() <= 100.0f || count >= 30)
			{
				distance.y = 0;
				distance.Normalize();
				auto front = m_enemy->Get2DFront();
				if (acos(front.Dot(distance)) <= CMath::DegToRad(10.0f))
				{
					m_enemy->ChangeAnimation(Enemy::attack);
					FindSwordpos();
					m_oldSwordcenter = m_Swordcenter;
					m_steat = Attack;
					count = 0;
				}
			}
		}
		else
		{

			m_enemy->AddAngle(distance);
			m_enemy->ChangeAnimation(Enemy::walk);
			m_enemy->SetSpeed(1.0f / 2.0f);
			m_enemy->SetDebugPos({ 0.0f,0.0f,0.0f });
			m_steat = Chase;
		}
		break;
	case Attack:
		m_enemy->SetSpeed(0.0f);
		m_enemy->ChangeAnimation(Enemy::attack);
		FindSwordpos();
		if (!m_Hit)
		{
			if (m_enemy->GetIsEvent())
			{
				auto attackMove = (m_Swordcenter - m_oldSwordcenter) / 2;
				auto hitpoint = attackMove + m_Swordcenter;
				m_Hit = GetHitObjict().HitTest(hitpoint, attackMove.Length(), m_enemy->GetStatus()->m_Attack, HitReceive::player);
				m_enemy->SetDebugPos(hitpoint);
			}
		}
		m_oldSwordcenter = m_Swordcenter;
		if (!m_enemy->GetanimationPlaying()) {
			m_Hit = false;
			m_steat = Wait;
			m_enemy->ChangeAnimation(Enemy::idle);
		}
		break;
	case Chase:
		m_enemy->AddAngle(distance);
		m_enemy->ChangeAnimation(Enemy::walk);
		m_enemy->SetSpeed(1.0f / 2.0f);
		m_enemy->SetDebugPos({ 0.0f,0.0f,0.0f });
		if (150.0f)
		{
			m_steat = Wait;
		}
		break;
	default:
		break;
	}
	if (distance.Length() >= 300.0f)
	{
		m_enemy->SetSpeed(1.0f);
		m_enemy->TransitionState(Enemy::State_Move);
	}
}
void EnemyStateAttack::FindSwordpos()
{
	CMatrix BoneMatrix = m_enemy->CopyModel().GetSkeleton().GetBone(m_boneNo)->GetWorldMatrix();
	m_handpos.x = BoneMatrix.m[3][0];
	m_handpos.y = BoneMatrix.m[3][1];
	m_handpos.z = BoneMatrix.m[3][2];
	m_Up.x = BoneMatrix.m[2][0];
	m_Up.y = BoneMatrix.m[2][1];
	m_Up.z = BoneMatrix.m[2][2];
	m_Up.Normalize();
	m_Swordcenter.x = m_handpos.x + m_Up.x*SWODSIZE.z / 2;
	m_Swordcenter.y = m_handpos.y + m_Up.y*SWODSIZE.z / 2;
	m_Swordcenter.z = m_handpos.z + m_Up.z*SWODSIZE.z / 2;
}