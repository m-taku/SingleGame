#pragma once
#include"Player_State.h"
class Player_Hit :public Player_State
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="player">
	///�v���C���[�̃|�C���^�B�iPlayer*�j
	/// </param>
	Player_Hit(Player* player);
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~Player_Hit();
	/// <summary>
	/// �A�b�v�f�[�g�֐�
	/// </summary>
	void Update();
	
};

