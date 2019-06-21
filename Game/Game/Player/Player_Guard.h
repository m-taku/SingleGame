#pragma once
#include "Player_State.h"
class Player_Guard :public Player_State
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="player">
	///�v���C���[�̃|�C���^�B�iPlayer*�j
	/// </param>
	Player_Guard(Player* player);
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~Player_Guard();
	/// <summary>
	/// �A�b�v�f�[�g�֐�
	/// </summary>
	void Update();
private:
	Effekseer::Effect* m_sampleEffect = nullptr;			//�G�t�F�N�g�̎��Ԃ̃|�C���^�i�H�j
	Effekseer::Handle m_playEffectHandle;					//�G�t�F�N�g�̂����n���h��
};

