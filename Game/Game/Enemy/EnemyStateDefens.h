#pragma once
#include"EnemyState.h"
class EnemyStateDefens :public EnemyState
{
public:
	EnemyStateDefens(Enemy* enemy_point, const CVector3* pos);
	~EnemyStateDefens();
	/// <summary>
	/// EnemyState����p�������A�b�v�f�[�g�֐��B
	/// </summary>
	void Update() override;
private:
	enum attack
	{
		Wait,
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
	int m_boneNo = 0;
	int count = 0;//��̃{�[���̔ԍ�
	attack m_steat = Chase;
	int m_raitspeed = 1.0f;
	int m_kakudo = 1.0f;		//���O���߂Ȃ���
	bool m_Hit = false;										//�U���𓖂Ă����ǂ����i���Ă��画��������j
															//VectorDraw* m_debugVecor = nullptr;						//�f�o�b�N�p�̃x�N�g���\��
};

