#pragma once
#include "Player_State.h"
class Player_Special :public Player_State
{
public:
	Player_Special(Player* player);
	~Player_Special();
	/// <summary>
	/// �A�b�v�f�[�g�֐�
	/// </summary>
	void Update();
private:
	float m_scuea = 1.0f;
	Effekseer::Effect* m_sampleEffect = nullptr;			//�G�t�F�N�g�̎��Ԃ̃|�C���^�i�H�j
	Effekseer::Handle m_playEffectHandle;					//�G�t�F�N�g�̂����n���h��
};

