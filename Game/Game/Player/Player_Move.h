#pragma once
#include "Player_State.h"
class Player_Move :public Player_State
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="player">
	///�v���C���[�̃|�C���^�B�iPlayer*�j
	/// </param>
	Player_Move(Player* player);
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~Player_Move();
	/// <summary>
	/// �A�b�v�f�[�g�֐�
	/// </summary>
	void Update();
private:
};

