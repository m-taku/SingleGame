#pragma once
class Enemy;
class Player;
/// <summary>
/// �X�e�[�g�̊��N���X�B
/// </summary>
class EnemyState:public Noncopyable
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
	EnemyState(Enemy* enemy_point,const CVector3* pos);
	/// <summary>
	/// �f�X�g���N�^�B
	/// </summary>
	virtual ~EnemyState();
	/// <summary>
	/// �A�b�v�f�[�g�B
	/// </summary>
	virtual void Update() = 0;
	CVector3 GetTarget3DPosition()
	{
		return *m_targetposition;
	}
	CVector3 GetTarget2DPosition()
	{
		auto pos = *m_targetposition;
		pos.y = 0;
		return pos;
	}
protected:
	Enemy* m_enemy=nullptr;			//�G�l�~�[�̃C���X�^���X
	const CVector3* m_targetposition = nullptr;
	//Player* m_player=nullptr;			//�v���C���[�̃C���X�^���X
};

