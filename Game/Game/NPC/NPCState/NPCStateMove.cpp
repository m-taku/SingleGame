#include "stdafx.h"
#include "NPCStateMove.h"
#include "NPC.h"


NPCStateMove::NPCStateMove(NPC* enemy_point, const CVector3* pos) :NPCState(enemy_point, pos)
{
	//�ړ��̏�����
	m_path = m_npc->CopyPath();
	m_path->Course(m_npc->Get2DPosition(), GetTarget2DPosition());
	m_nextpos = m_path->PathPos();
	m_npc->SetSpeed(1.0f);
	m_npc->ChangeAnimation(NPC::idle);
}


NPCStateMove::~NPCStateMove()
{
}
void NPCStateMove::Update()
{
	m_npc->ChangeAnimation(NPC::walk);
	CVector3 speed = CVector3::Zero();
	CVector3 nowpos = m_npc->Get2DPosition();
	//���݈ʒu�ƖڕW�ʒu�����Z����
	speed = m_nextpos - nowpos;
	if (++m_fream > 30) {
		//���ꂢ�ɂ��邽�߂ɖ�P�b�ōX�V
		m_path->Course(m_npc->Get2DPosition(), GetTarget2DPosition());
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
			m_path->Course(m_npc->Get2DPosition(), GetTarget2DPosition());
			m_nextpos = m_path->PathPos();
		}
		m_oldposition = m_nextpos;
		speed = m_nextpos - nowpos;
	}
	speed.y = 0.0;
	speed.Normalize();

	m_npc->AddAngle(speed);
	CVector3 distance = GetTarget2DPosition() - m_npc->Get2DPosition();
	if (distance.Length() <= 300.0f)
	{
		//�ڕW�ɋ߂Â�����A�^�b�N�ɑJ�ڂ���
		m_npc->SetSpeed(1.0f / 2.0f);
		//m_npc->TransitionState(Enemy::State_Attack);
	}
}
