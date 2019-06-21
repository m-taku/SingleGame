#pragma once
#include "Player_State.h"
class Player_Special :public Player_State
{
public:
	Player_Special(Player* player);
	~Player_Special();
	enum special
	{
		chrji,
		Attackc
	};
	/// <summary>
	/// �A�b�v�f�[�g�֐�
	/// </summary>
	void Update();
private:
	void Attack();
	float m_scuea = 1.0f;
	bool m_sound = false;
	CSoundSource m_bgmA;									//BGM�p�̃N���X
	special ka;
	Effekseer::Effect* m_sampleEffect = nullptr;			//�G�t�F�N�g�̎��Ԃ̃|�C���^�i�H�j
	Effekseer::Handle m_playEffectHandle;					//�G�t�F�N�g�̂����n���h��
};

