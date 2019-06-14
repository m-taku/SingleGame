#pragma once
#include "NPCState.h"
class NPCStateAttack :public  NPCState
{
public:
	NPCStateAttack(NPC* enemy_point, const CVector3* pos);
	~NPCStateAttack();
	/// <summary>
	/// Enemy�̃A�^�b�N�X�e�[�g�N���X�B
	/// </summary>
public:

	void Update() override;
	//// <summary>
	//// ���ɑ΂��ăv���C���[�������������ǂ���
	//// </summary>
	//void CollisionTest();
private:
	enum attack
	{
		Wait,
		Attack,
		Chase
	};
	/// <summary>
	/// ���̓����蔻��p�̉�]�p�x�擾
	/// </summary>
	/// <param name="vector1">
	/// �P�ڂ̃x�N�g���iNormalize�j
	/// </param>
	/// <param name="vector2">
	/// 2�ڂ̃x�N�g���iNormalize�j
	/// </param>
	/// <returns>
	/// ��]�N�I�[�^�j�I��
	/// </returns>
	//	CQuaternion anglecalculation(CVector3 vector1, CVector3 vector2);
	/// <summary>
	/// ���̒��S�Ǝ�̈ʒu����������
	/// </summary>
	void FindSwordpos();
	int m_boneNo = 0;
	int count = 0;//��̃{�[���̔ԍ�
	CVector3 m_oldhandpos = CVector3::Zero();				//�ړ��O�̎�̃|�W�V����
	CVector3 m_handpos = CVector3::Zero();					//�ړ���̎�̃|�W�V����
	CVector3 m_oldSwordcenter = CVector3::Zero();			//�ړ��O�̌��̒��S�|�W�V����
	CVector3 m_Swordcenter = CVector3::Zero();				//�ړ���̌��̒��S�|�W�V����
	CVector3 m_Up;											//��̏�����x�N�g��
	attack m_steat = Wait;
	bool m_Hit = false;										//�U���𓖂Ă����ǂ����i���Ă��画��������j
	//VectorDraw* m_debugVecor = nullptr;						//�f�o�b�N�p�̃x�N�g���\��
};

