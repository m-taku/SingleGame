#pragma once
#include"EnemyState.h"
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
private:
}; 

