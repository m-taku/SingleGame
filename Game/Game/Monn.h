#pragma once
#include"physics/PhysicsStaticObject.h"
class Monn : public Gameobject
{
public:
	Monn();
	~Monn();
	bool Load();
	void Draw();
	void Update();
	/*
	*@brief �|�W�V�����̃Z�b�g
	*@param[in]�@CVector3 pos
	*/
	void Setposition(CVector3 pos)
	{
		m_position = pos;
	}
	/*
	*@brief ��]�p�x�̃Z�b�g
	*@param[in]�@CQuaternion rot
	*/
	void Setrotation(CQuaternion rot)
	{
		m_rotation = rot;
	}
	/*
	*@brief �J�������̑J��
	*@�@kaihei
	*/
	void Setkaku()
	{
		if (kaihei) {
			m_rod *= -1;
			kaihei = false;
		}
		else
		{
			kaihei = true;
		}
	}
private:
	//PhysicsStaticObject m_monn;			
	SkinModel m_model;
	MeshCollider m_meshCollider;		//!<���b�V���R���C�_�[�B
	RigidBody m_rigidBody;				//!<���́B
	CVector3 m_position = CVector3::Zero();						//��̃|�W�V����
	CQuaternion m_rotation = CQuaternion::Identity();			//��̊p�x
	bool kaihei = false;											//�J���Ă��邩�ǂ���
	float m_rod = 0.0f;											//���p�x
	float m_kaku = 0.0f;										//���̊p�x
};

