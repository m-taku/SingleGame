#pragma once
#include"Player_State.h"
class Player_Die :public Player_State
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="player">
	///�v���C���[�̃|�C���^�B�iPlayer*�j
	/// </param>
	Player_Die(Player* player);
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~Player_Die();
	/// <summary>
	/// �A�b�v�f�[�g
	/// </summary>
	void Update();
private:
	bool m_die = true;				//���S�f�f�t���O
};

