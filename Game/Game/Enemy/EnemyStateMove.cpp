#include "stdafx.h"
#include "EnemyStateMove.h"
#include"Enemy.h"
#include"../Stage.h"

EnemyStateMove::EnemyStateMove(Enemy* enamy,Player* player):EnemyState(enamy,player)
{
	m_path = m_enemy->CopyPath();
	m_path->Course(m_enemy->Get2DPosition(), player->Get2Dposition());
	m_enemy->SetSpeed(300.0f);
	m_nextpos = m_path->PathPos();
}
EnemyStateMove::~EnemyStateMove()
{

}
void EnemyStateMove::Update()
{
	m_enemy->ChangeAnimation(Enemy::walk);
	CVector3 speed = CVector3::Zero();
	CVector3 nowpos = m_enemy->Get3DPosition();
	speed = m_nextpos - nowpos;
	if (++m_fream > 30) {
		m_path->Course(m_enemy->Get2DPosition(), m_player->Get2Dposition());
		m_nextpos = m_path->PathPos();
		m_nextpos = m_path->PathPos();
		m_fream = 0;
	}
	//�|���S��������~�ɓ�������
	if (speed.Length() <= 100.0f)
	{
		//���̃p�X����������
		m_nextpos = m_path->PathPos();
		if (m_nextpos.x == m_oldposition.x&&m_nextpos.y == m_oldposition.y&&m_nextpos.z == m_oldposition.z)
		{
			//�������I�_�Ȃ�ΒT�����Ȃ���
			m_path->Course(m_enemy->Get2DPosition(), m_player->Get2Dposition());
			m_nextpos = m_path->PathPos();
		}
		m_oldposition = m_nextpos;
		speed = m_nextpos - nowpos;
	}
	speed.y = 0.0;
	speed.Normalize();
	m_enemy->FindAngle(speed);
	CVector3 distance = m_player->Get2Dposition() - m_enemy->Get2DPosition();
	if (distance.Length() <= 150.0f)
	{
		m_enemy->SetSpeed(100.0f);
		m_enemy->TransitionState(Enemy::State_Attack);
	}
	//���ꂢ�ɂ��邽�߂ɖ�P�b�ōX�V

}