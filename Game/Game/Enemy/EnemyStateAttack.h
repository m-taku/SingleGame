#pragma once
#include"EnemyState.h"
#include "Physics/CapsuleCollider.h"
#include "Physics/RigidBody.h"
/// <summary>
/// Enemy�̃A�^�b�N�X�e�[�g�N���X�B
/// </summary>
class EnemyStateAttack :public EnemyState
{
public:
	/// <summary>
	/// �R���X�g���N�^�B
	/// </summary>
	/// <param name="enemy_point">
	/// �G�l�~�[�̃|�C���^�B�iEnemy*�j
	/// </param>
	/// <param name="pla">
	/// �v���C���[�̃|�C���^�B�iPlayer*�j
	/// </param>
	EnemyStateAttack(Enemy* enemy_point, Player* pla);
	/// <summary>
	/// �f�X�g���N�^�B
	/// </summary>
	~EnemyStateAttack();	
	/// <summary>
	/// EnemyState����p�������A�b�v�f�[�g�֐��B
	/// </summary>
	void Update() override;
	/// <summary>
	/// ���ɑ΂��ăv���C���[�������������ǂ���
	/// </summary>
	void CollisionTest();
private:
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
	CQuaternion anglecalculation(CVector3 vector1, CVector3 vector2);
	/// <summary>
	/// ���̒��S�Ǝ�̈ʒu����������
	/// </summary>
	void FindSwordpos();
	int m_boneNo = 0;										//��̃{�[���̔ԍ�
	CVector3 m_oldhandpos = CVector3::Zero();				//�ړ��O�̎�̃|�W�V����
	CVector3 m_handpos= CVector3::Zero();					//�ړ���̎�̃|�W�V����
	CVector3 m_oldSwordcenter = CVector3::Zero();			//�ړ��O�̌��̒��S�|�W�V����
	CVector3 m_Swordcenter = CVector3::Zero();				//�ړ���̌��̒��S�|�W�V����
	CVector3 m_Up;											//��̏�����x�N�g��
	VectorDraw* m_debugVecor = nullptr;						//�f�o�b�N�p�̃x�N�g���\��
}; 

