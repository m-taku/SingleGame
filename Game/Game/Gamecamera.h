#pragma once
#include"Player.h"
class Gamecamera:public Gameobject
{
public:
	Gamecamera();
	~Gamecamera();
	bool Load();
	void Update();
	void Draw();
	/*
	�v���C���[�̃|�C���^�����
	*/
	void SetPlayer(Player* pLater)
	{
		player = pLater;
	}
	/*
	�J�����̑O�����x�N�g�����擾�iCVector3�j
	*/
	CVector3 Getcamerafront()
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
	CVector3 ka;
	float kakudo = 0.0f;
	CVector3 m_targetpos = CVector3::Zero();		//�J�����̖ڕW�n�_
	CVector3 m_position = CVector3::Zero();			//�J�����̌��ݒn
	Player* player = nullptr;						//�v���C���[�̃|�C���^
};

