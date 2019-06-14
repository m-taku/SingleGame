#include "stdafx.h"
#include "EnemyStategathering.h"
#include"Enemy.h"
EnemyStategathering::EnemyStategathering(Enemy* enamy,const CVector3* pos) :EnemyState(enamy, pos)
{
	//経路探査
	m_path = m_enemy->CopyPath();
	m_path->Course(m_enemy->Get3DPosition(),m_enemy->GetLeaderPosition());
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
	//目標位置と現在位置を引く
	CVector3 distance = leaderpos - nowpos;
	m_enemy->ChangeAnimation(Enemy::walk);
	CVector3 speed = CVector3::Zero();
	if (distance.Length() <= 150.0f)
	{
		//グループの集合位置についたのでストップする
		m_enemy->SetSpeed(0.0f);
		m_enemy->RollCall();
		return;
	}
	speed = m_nextpos - nowpos;
	//ポリゴンを内包する円に入ったら
	if (speed.Length() <= 100.0f)
	{
		//次のパスを検索する
		m_nextpos = m_path->PathPos();
		if (m_nextpos.x == m_oldposition.x&&m_nextpos.y == m_oldposition.y&&m_nextpos.z == m_oldposition.z)
		{
			//もしも終点ならば探索しなおす
			m_path->Course(m_enemy->Get2DPosition(), m_enemy->GetLeaderPosition());
			m_nextpos = m_path->PathPos();
		}
		m_oldposition = m_nextpos;
		speed = m_nextpos - nowpos;
	}
	speed.y = 0.0;
	speed.Normalize();
	m_enemy->AddAngle(speed);
}