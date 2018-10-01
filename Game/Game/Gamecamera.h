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
	プレイヤーのポインタ入れる
	*/
	void SetPlayer(Player* pLater)
	{
		player = pLater;
	}
	/*
	カメラの前方向ベクトルを取得（CVector3）
	*/
	CVector3 Getcamerafront()
	{
		return camerfront;
	}
private:
	void Jiku();									//軸の計算（前方向、右方向）
	CVector3 m_Front = CVector3::Zero();			//前方向
	CVector3 m_Up = CVector3::Zero();				//上方向
	CVector3 m_right = CVector3::Zero();			//右方向
	CVector3 camerfront = CVector3::AxisZ();		//カメラの前方向ベクトル
	CQuaternion	m_reg = CQuaternion::Identity();	//回転角度
	CMatrix mRot;									//回転行列
	CVector3 m_angle = CVector3::Zero();			//回転入力量
	CVector3 ka;
	float kakudo = 0.0f;
	CVector3 m_targetpos = CVector3::Zero();		//カメラの目標地点
	CVector3 m_position = CVector3::Zero();			//カメラの現在地
	Player* player = nullptr;						//プレイヤーのポインタ
};

