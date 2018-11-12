#pragma once
#include "character/CharacterController.h"
#include"UI.h"
class Gamecamera;
class Navimake;
/// <summary>
/// プレイヤークラス
/// </summary>
class Player: public Gameobject
{
public:
	/// <summary>
	/// コンストラクタ。
	/// </summary>
	Player();
	/// <summary>
	/// デストラクタ。
	/// </summary>
	~Player();
	/// <summary>
	/// Gemeobjectから継承したLoat関数。
	/// </summary>
	/// <returns>
	/// 成功でtrue、失敗でfalse。
	/// </returns>
	bool Load();
	/// <summary>
	/// Gameobjectから継承したUpdate関数
	/// </summary>
	void Update();
	/// <summary>
	/// Gameobjectから継承したDraw関数
	/// </summary>
	void Draw();
	/// <summary>
	/// 2D（ｘ、ｚ）での現在のポジション。
	/// </summary>
	/// <remarks>
	/// 3D次元で返す関数もあるので適しているか確認。
	/// </remarks>
	/// <returns>
	/// 2Dでのポジション。（CVector3）
	/// </returns>
	CVector3 Get2Dposition() const
	{
		auto position = m_position;
		position.y = 0.0f;
		return position;
	} 
	/// <summary>
	/// 3D（ｘ、ｙ、ｚ）での現在のポジション。
	/// </summary>
	/// <remarks>
	/// 2D次元で返す関数ももあるので適しているか確認。
	/// </remarks>
	/// <returns>
	/// 3Dでのポジション。（CVector3）
	/// </returns>
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
	UI* Ui = nullptr;
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
	float m_kaiten = 0.0f;								//回転角度（ラジアン）
	VectorDraw* vector =nullptr; 
	//CVector3 m_angle = CVector3::Zero();				
	//wchar_t bonename[50];								//名前
	//int bonenum = 0;									
	//int boneNo = 0;
};

