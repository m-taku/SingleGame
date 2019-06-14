#include "stdafx.h"
#include "EnemyStateMove.h"
#include"Enemy.h"
#include"../Stage.h"

EnemyStateMove::EnemyStateMove(Enemy* enamy, const CVector3* pos):EnemyState(enamy, pos)
{
	//移動の初期化
	m_path = m_enemy->CopyPath();
	m_path->Course(m_enemy->Get2DPosition(), GetTarget2DPosition());
	m_nextpos = m_path->PathPos();
	m_enemy->SetSpeed(1.0f);
	m_enemy->ChangeAnimation(Enemy::idle);
}
EnemyStateMove::~EnemyStateMove()
{

}
void EnemyStateMove::Update()
{
	m_enemy->ChangeAnimation(Enemy::walk);
	CVector3 speed = CVector3::Zero();
	CVector3 nowpos = m_enemy->Get2DPosition();
	//現在位置と目標位置を減算する
	speed = m_nextpos - nowpos;
	if (++m_fream > 30) {
		//きれいにするために約１秒で更新
		m_path->Course(m_enemy->Get2DPosition(), GetTarget2DPosition());
		m_nextpos = m_path->PathPos();
		m_nextpos = m_path->PathPos();
		m_fream = 0;
	}
	//ポリゴンを内包する円に入ったら
	if (speed.Length() <= 100.0f)
	{
		//次のパスを検索する
		m_nextpos = m_path->PathPos();
		if (m_nextpos.x == m_oldposition.x&&m_nextpos.y == m_oldposition.y&&m_nextpos.z == m_oldposition.z)
		{
			//もしも終点ならば探索しなおす
			m_path->Course(m_enemy->Get2DPosition(), GetTarget2DPosition());
			m_nextpos = m_path->PathPos();
		}
		m_oldposition = m_nextpos;
		speed = m_nextpos - nowpos;
	}
	speed.y = 0.0;
	speed.Normalize();

	m_enemy->AddAngle(speed);
	CVector3 distance = GetTarget2DPosition() - m_enemy->Get2DPosition();
	if (distance.Length() <= 300.0f)
	{
		//目標に近づいたらアタックに遷移する
		m_enemy->SetSpeed(1.0f/2.0f);
		m_enemy->TransitionState(Enemy::State_Attack);
	}
}