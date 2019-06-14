#pragma once
#include"EnemyState.h"
#include"Path.h"
/// <summary>
/// Enemy�̃O���[�v�ɏW������Ƃ��̏����X�e�[�g�N���X�B
/// </summary>
class EnemyStategathering :public EnemyState
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
	EnemyStategathering(Enemy* enemy_point, const CVector3* pos);
	/// <summary>
	/// �f�X�g���N�^�B
	/// </summary>
	~EnemyStategathering();
	/// <summary>
	/// EnemyState����p�������A�b�v�f�[�g�֐��B
	/// </summary>
	void Update() override;
private:
	Path* m_path = nullptr;										//�o�H�T���̃C���X�^���X
	CVector3 m_oldposition = CVector3::Zero();					//1�t���[���O�̃|�W�V�����i�ǎC��Ȃǂ̔���ȂǂȂǁj
	CVector3 m_nextpos = CVector3::Zero();						//�o�H�T���ŏo�����̃|�W�V����
};

