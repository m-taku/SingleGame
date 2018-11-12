#pragma once
#include"Player/Player.h"
/// <summary>
/// �Q�[���J�����N���X�B
/// </summary>
class Gamecamera:public Gameobject
{
public:
	/// <summary>
	/// �R���X�g���N�^�B
	/// </summary>
	Gamecamera();
	/// <summary>
	/// �f�X�g���N�^�B
	/// </summary>
	~Gamecamera();
	/// <summary>
	/// Gemeobject����p������Load�֐��B
	/// </summary>
	/// <returns>
	/// ������true�A���s��float�B
	/// </returns>
	bool Load();
	/// <summary>
	/// Gemeobject����p������Update�֐��B
	/// </summary>
	void Update();
	/// <summary>
	/// Gameobject����p������Draw�֐��B
	/// </summary>
	void Draw();
	/// <summary>
	///  �v���C���[�̃C���X�^���X�̃Z�b�g�B
	/// </summary>
	/// <param name="player">
	/// �Z�b�g�������v���C���[�̃C���X�^���X�B(Player*)
	/// </param>
	void SetPlayer(Player* plater)
	{
		m_player = plater;
	}
	/// <summary>
	/// �J�����̍������Ă�������x�N�g���B
	/// </summary>
	/// <returns>
	/// �����x�N�g���B�iCVector3�j
	/// </returns>
	CVector3 GetCameraFront()const
	{
		return camerfront;
	}
private:
	void Jiku();									//���̌v�Z�i�O�����A�E�����j
	CVector3 m_Front = CVector3::Zero();			//�O����
	CVector3 m_Up = CVector3::Zero();				//�����
	CVector3 m_right = CVector3::Zero();			//�E����
	CVector3 camerfront = CVector3::AxisZ();		//�J�����̑O�����x�N�g��
	CQuaternion	m_reg = CQuaternion::Identity();	//��]�p�x
	CMatrix mRot;									//��]�s��
	CVector3 m_angle = CVector3::Zero();			//��]���͗�
	CVector3 m_jiku;								//��
	CVector3 m_targetpos = CVector3::Zero();		//�J�����̖ڕW�n�_
	CVector3 m_position = CVector3::Zero();			//�J�����̌��ݒn
	Player* m_player = nullptr;						//�v���C���[�̃|�C���^
};

