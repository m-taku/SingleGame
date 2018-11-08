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
	*@brief ポジションのセット
	*@param[in]　CVector3 pos
	*/
	void Setposition(CVector3 pos)
	{
		m_position = pos;
	}
	/*
	*@brief 回転角度のセット
	*@param[in]　CQuaternion rot
	*/
	void Setrotation(CQuaternion rot)
	{
		m_rotation = rot;
	}
	/*
	*@brief 開く方向の遷移
	*@　kaihei
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
	MeshCollider m_meshCollider;		//!<メッシュコライダー。
	RigidBody m_rigidBody;				//!<剛体。
	CVector3 m_position = CVector3::Zero();						//門のポジション
	CQuaternion m_rotation = CQuaternion::Identity();			//門の角度
	bool kaihei = false;											//開いているかどうか
	float m_rod = 0.0f;											//回る角度
	float m_kaku = 0.0f;										//今の角度
};

