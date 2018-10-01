#pragma once
#include "character/CharacterController.h"
class Gamecamera;
class Player: public Gameobject
{
public:
	Player();
	~Player();
	bool Load();
	void Update();
	void Draw();
	void postDraw();
	/*
	*@brief	2Ｄ座標系での位置
	*@return CVector3 
	*/
	CVector3 Get2Dposition() const
	{
		auto position = m_position;
		position.y = 0.0f;
		return position;
	} 	
	/*
	*@brief	3Ｄ座標系での位置
	*@return CVector3 
	*/
	CVector3 Get3Dposition() const
	{
		return m_position;
	}
	/*
	*@brief	回転行列を取得
	*@return CMatrix
	*/
	const CMatrix& GetMatrix() const
	{
		return mRot;
	}	
	/*
	*@brief	スティックの移動量
	*@return CVector3（ベクトル） 
	*/
	const CVector3& Getangle() const
	{
		return m_amount;
	}
	/*
	*@brief	スティックの移動量
	*@return CVector3（ベクトル）
	*/
	const CVector3& GetFront() const
	{
		return m_Front;
	}
	/*
	*@brief	Gamecameraのポインタを取得
	*/
	void SetCamera(Gamecamera* camera)
	{
		m_camer = camera;
	}
private:
	CharacterController m_collider;						//キャラクターコントローラー
	SkinModel m_model;									//モデルデータ
	CVector3 m_movespeed = CVector3::Zero();			//移動速度
	CQuaternion m_rotation = CQuaternion::Identity();	//回転クオータニオン
	CMatrix mRot;										//回転行列
	Gamecamera* m_camer = nullptr;						//カメラのポインタ
	CVector3 m_Up = CVector3::AxisY();					//上方向
	CVector3 m_Front = CVector3::Zero();				//前方向
	CVector3 m_position = { 0.0f,150.0f,-30.0f };		//現在位置
	CVector3 m_amount = { 0.0f,0.0f,0.0f };				//スティックの移動量
	float kaiten = 0.0f;								//回転角度（ラジアン）
	VectorDraw* vector =nullptr;
	//CVector3 m_angle = CVector3::Zero();				
	//wchar_t bonename[50];								//名前
	//int bonenum = 0;									
	//int boneNo = 0;
};

