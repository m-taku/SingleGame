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
	void Setposition(CVector3 pos)
	{
		m_position = pos;
	}
	void Setrotation(CQuaternion rot)
	{
		m_rotation = rot;
	}
	void Setkaku()
	{
		m_rod *= -1;
	}
private:
	//PhysicsStaticObject m_monn;			
	SkinModel m_model;
	MeshCollider m_meshCollider;		//!<���b�V���R���C�_�[�B
	RigidBody m_rigidBody;				//!<���́B
	CVector3 m_position = CVector3::Zero();						//��̃|�W�V����
	CQuaternion m_rotation = CQuaternion::Identity();			//��̊p�x
	float m_rod = 2.0f;											//���p�x
	float m_kaku = 0.0f;										//���̊p�x
};

