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
	MeshCollider m_meshCollider;		//!<メッシュコライダー。
	RigidBody m_rigidBody;				//!<剛体。
	CVector3 m_position = CVector3::Zero();						//門のポジション
	CQuaternion m_rotation = CQuaternion::Identity();			//門の角度
	float m_rod = 2.0f;											//回る角度
	float m_kaku = 0.0f;										//今の角度
};

