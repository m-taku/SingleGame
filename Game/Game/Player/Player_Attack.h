#pragma once
#include "Player_State.h"
class Player_Attack :public Player_State
{
public:
	Player_Attack(Player* player);
	~Player_Attack();
	void Update();
	void FindSwordpos();
private:
	CVector3 m_oldhandpos = CVector3::Zero();				//�ړ��O�̎�̃|�W�V����
	CVector3 m_handpos = CVector3::Zero();					//�ړ���̎�̃|�W�V����
	CVector3 m_oldSwordcenter = CVector3::Zero();			//�ړ��O�̌��̒��S�|�W�V����
	CVector3 m_Swordcenter = CVector3::Zero();				//�ړ���̌��̒��S�|�W�V����
	CVector3 m_Up;											//��̏�����x�N�g��
	bool m_Hit = false;										//�U���𓖂Ă����ǂ����i���Ă��画��������j
};

