#pragma once
#include"EnemyState.h"
class EnemyStateDead :public EnemyState
{
public:	/// <summary>
		/// �R���X�g���N�^
		/// </summary>
		/// <param name="enemy_point">
		/// �G�l�~�[�̃|�C���^�iEnemy*�j
		/// </param>
		/// <param name="pla">
		/// �v���C���[�̃|�C���^�iPlayer*�j
		/// </param>
	EnemyStateDead(Enemy* enemy_point, Player* pla);
	/// <summary>
	///�f�X�g���N�^
	/// </summary>
	~EnemyStateDead();
	/// <summary>
	/// EnemyState����p�������A�b�v�f�[�g�֐��B
	/// </summary>
	void Update() override;
};

