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
	/// 
	/// </summary>
	bool CollisionTest();
private:
	int m_boneNo = 0;
	CVector3 center = CVector3::Zero();
	CVector3 m_center = CVector3::Zero();
	CVector3 swodaabb2 = CVector3::Zero();
	CVector3 swodaabb20 = CVector3::Zero();
	CQuaternion m_Rot = CQuaternion::Identity();
	//CapsuleCollider m_collide;
	RigidBody*	m_rigidBody=nullptr;					//���́B�f�o�b�N
	VectorDraw* m_debugVecor = nullptr;						//�f�o�b�N�p�̃x�N�g���\��
}; 

