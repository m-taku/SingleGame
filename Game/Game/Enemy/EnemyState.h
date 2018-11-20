#pragma once
class Enemy;
class Player;
/// <summary>
/// �X�e�[�g�̊��N���X�B
/// </summary>
class EnemyState
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
	EnemyState(Enemy* enemy_point, Player* pla);
	/// <summary>
	/// �f�X�g���N�^�B
	/// </summary>
	virtual ~EnemyState();
	/// <summary>
	/// �A�b�v�f�[�g�B
	/// </summary>
	virtual void Update() = 0;
protected:
	Enemy* m_enemy=nullptr;			//�G�l�~�[�̃C���X�^���X
	Player* m_player=nullptr;			//�v���C���[�̃C���X�^���X
};

