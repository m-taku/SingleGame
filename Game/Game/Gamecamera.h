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
	bool Load() override;
	/// <summary>
	/// Gemeobject����p������Update�֐��B
	/// </summary>
	void Update() override;
	/// <summary>
	/// Gameobject����p������Draw�֐��B
	/// </summary>
	void Draw() override;
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
		return m_front;
	}
private:
	/// <summary>
	///�v���C���[���W�n�ł̊�ꎲ���X�V
	/// </summary>
	/// <remarks>
	/// ���ݍX�V�����̂́Ay���ƁAz���̂݁B
	/// </remarks>
	void UpdateBasisInPlayerSpace();
	/// <summary>
	/// ���ɉ�荞�ރJ�����̏��������s����B
	/// </summary>
	/// <remarks>
	/// �ŋ߂̃Q�[���̌��ɉ�荞�ރJ�����̏����B
	/// �h���N�G11�Ƃ��F�X�B
	/// </remarks>
	void ExecuteTracking();
	CVector3 m_playerFront = CVector3::Zero();		//�v���C���[�̑O����
	CVector3 m_playerUp = CVector3::Zero();			//�v���C���[�̏����
	CVector3 m_right = CVector3::Zero();			//�E����
	CVector3 m_front = CVector3::AxisZ();			//�O�����x�N�g��
	CQuaternion	m_reg = CQuaternion::Identity();	//��]�p�x
	CMatrix m_mRot = CMatrix::Identity();			//��]�s��
	CVector3 m_angle = CVector3::Zero();			//��]���͗�
	CVector3 m_axis = CVector3::Zero();				//��
	CVector3 m_targetpos = CVector3::Zero();		//�J�����̖ڕW�n�_
	CVector3 m_position = CVector3::Zero();			//�J�����̌��ݒn
	Player* m_player = nullptr;						//�v���C���[�̃|�C���^
};

