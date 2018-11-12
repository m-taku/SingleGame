#pragma once
#include"EnemyState.h"
#include"../../Path.h"
/// <summary>
/// Enemy�̈ړ��X�e�[�g�N���X�B
/// </summary>
class EnemyStateMove :public EnemyState
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="enemy_point">
	/// �G�l�~�[�̃|�C���^�iEnemy*�j
	/// </param>
	/// <param name="pla">
	/// �v���C���[�̃|�C���^�iPlayer*�j
	/// </param>
	EnemyStateMove(Enemy* enemy_point, Player* pla);
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~EnemyStateMove();
	/// <summary>
	/// EnemyState����p�������A�b�v�f�[�g�֐��B
	/// </summary>
	void Update() override;
private:
	Path * path = nullptr;										//�o�H�T���̃C���X�^���X
	CVector3 m_oldposition = CVector3::Zero();					//1�t���[���O�̃|�W�V�����i�ǎC��Ȃǂ̔���ȂǂȂǁj
	CVector3 m_nextpos = CVector3::Zero();						//�o�H�T���ŏo�����̃|�W�V����
};

