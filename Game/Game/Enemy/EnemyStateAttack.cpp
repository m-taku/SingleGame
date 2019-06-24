#include "stdafx.h"
#include "EnemyStateAttack.h"
#include"../../Player/Player.h"
//#include"../HitObjict.h"
#include "Physics/CollisionAttr.h"
#include"Enemy.h"
namespace {
	//剣のサイズ（aabb用）(縦、横、高さ)
	//const CVector3 SWODSIZE = { 10.0f, 10.0f,60.0f };
}
EnemyStateAttack::EnemyStateAttack(Enemy* enamy, const CVector3* pos) :EnemyState(enamy, pos)
{
	m_boneNo = m_enemy->GetNo();
}
EnemyStateAttack::~EnemyStateAttack()
{
}
void EnemyStateAttack::Update()
{
	auto distance = GetTarget2DPosition() - m_enemy->Get2DPosition();
	float lengh = 150.0f;
	if (m_enemy->GetStatus()->m_Spawnnum <= 1)
	{
		lengh *= 1.5f;
	}
	switch (m_steat)
	{
	case Wait:
		if (distance.Length() <= lengh) {
			m_enemy->AddAngle(distance);
			m_enemy->SetFrontSpeed(0.0f);
			m_enemy->ChangeAnimation(Enemy::idle);
			count++;
			if (distance.Length() <= 50.0f || count >= 30)
			{
				distance.y = 0.0f;
				distance.Normalize();
				auto front = m_enemy->Get2DFront();
				float kaku=min(1.0000f, front.Dot(distance));
				if (acos(kaku) <= CMath::DegToRad(10.0f))
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
			//m_enemy->AddAngle(distance);
			//m_enemy->ChangeAnimation(Enemy::walk);
			//m_enemy->SetSpeed(1.0f / 2.0f);
			//m_enemy->SetDebugPos({ 0.0f,0.0f,0.0f });
			m_steat = Chase;
		}
		break;
	case Attack:

		m_enemy->SetFrontSpeed(0.0f);
		m_enemy->ChangeAnimation(Enemy::attack);
		FindSwordpos();
		if (!m_Hit)
		{
			if (m_enemy->GetIsEvent())
			{
				auto attackMove = (m_Swordcenter - m_oldSwordcenter) / 2;
				auto hitpoint = attackMove + m_Swordcenter;
				float bai = 1.0f;
				if (m_enemy->GetStatus()->m_Spawnnum <= 1)
				{
					bai *= 5.0f;
				}
				m_Hit = GetHitObjict().HitTest(hitpoint, attackMove.Length()*bai, m_enemy->GetStatus()->m_Attack, HitReceive::player);
				m_enemy->SetDebugPos(hitpoint);
			}
		}
		m_oldSwordcenter = m_Swordcenter;
		if (!m_enemy->GetanimationPlaying()) {
			m_Hit = false;
			m_enemy->ChangeAnimation(Enemy::idle);
			m_enemy->AIDecision();
		}
		break;
	case Chase:
		m_enemy->AddAngle(distance);
		m_enemy->ChangeAnimation(Enemy::walk);
		m_enemy->SetFrontSpeed(1.0f / 2.0f);
		//m_enemy->SetDebugPos({ 0.0f,0.0f,0.0f });

		if (distance.Length() <= lengh)
		{
			m_steat = Wait;
		}
		break;
	default:
		break;
	}
	if (distance.Length() >= 300.0f)
	{
		m_enemy->SetFrontSpeed(1.0f);
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
	m_Swordcenter.x = m_handpos.x + m_Up.x*m_enemy->GetStatus()->m_WeaponSize.z;
	m_Swordcenter.y = m_handpos.y + m_Up.y*m_enemy->GetStatus()->m_WeaponSize.z;
	m_Swordcenter.z = m_handpos.z + m_Up.z*m_enemy->GetStatus()->m_WeaponSize.z;
}