#pragma once
#include "Player_State.h"
class Player_Attack :public Player_State
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="player">
	///�v���C���[�̃|�C���^�B�iPlayer*�j
	/// </param>
	Player_Attack(Player* player);
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~Player_Attack(); 
	/// <summary>
	/// �A�b�v�f�[�g�֐�
	/// </summary>
	void Update();
	/// <summary>
	/// ���̒��S���擾
	/// </summary>
	void FindSwordPos();
private:
	CVector3 m_oldhandpos = CVector3::Zero();				//�ړ��O�̎�̃|�W�V����
	CVector3 m_handpos = CVector3::Zero();					//�ړ���̎�̃|�W�V����
	CVector3 m_oldSwordcenter = CVector3::Zero();			//�ړ��O�̌��̒��S�|�W�V����
	CVector3 m_Swordcenter = CVector3::Zero();				//�ړ���̌��̒��S�|�W�V����
	CVector3 m_Up;											//��̏�����x�N�g��
	bool m_Hit = false;										//�U���𓖂Ă����ǂ����i���Ă��画��������j
	Effekseer::Effect* m_sampleEffect = nullptr;			//�G�t�F�N�g�̎��Ԃ̃|�C���^�i�H�j
	Effekseer::Handle m_playEffectHandle;					//�G�t�F�N�g�̂����n���h��
};

