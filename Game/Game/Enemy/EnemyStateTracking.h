#pragma once
#include"EnemyState.h"
/// <summary>
/// Enemy�̒ǔ������X�e�[�g�N���X�B
/// </summary>
class EnemyStateTracking:public EnemyState
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
	EnemyStateTracking(Enemy* enemy_point, Player* pla);
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~EnemyStateTracking();
	/// <summary>
	/// EnemyState����p�������A�b�v�f�[�g�֐��B
	/// </summary>
	void Update() override;
private:
	VectorDraw* vector = nullptr;			//�f�o�b�N�p�̃x�N�g���\���C���X�^���X
};

