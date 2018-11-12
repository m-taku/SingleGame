#pragma once
#include"Player/Player.h"
/// <summary>
/// ゲームカメラクラス。
/// </summary>
class Gamecamera:public Gameobject
{
public:
	/// <summary>
	/// コンストラクタ。
	/// </summary>
	Gamecamera();
	/// <summary>
	/// デストラクタ。
	/// </summary>
	~Gamecamera();
	/// <summary>
	/// Gemeobjectから継承したLoad関数。
	/// </summary>
	/// <returns>
	/// 成功でtrue、失敗でfloat。
	/// </returns>
	bool Load();
	/// <summary>
	/// Gemeobjectから継承したUpdate関数。
	/// </summary>
	void Update();
	/// <summary>
	/// Gameobjectから継承したDraw関数。
	/// </summary>
	void Draw();
	/// <summary>
	///  プレイヤーのインスタンスのセット。
	/// </summary>
	/// <param name="player">
	/// セットしたいプレイヤーのインスタンス。(Player*)
	/// </param>
	void SetPlayer(Player* plater)
	{
		m_player = plater;
	}
	/// <summary>
	/// カメラの今向いている方向ベクトル。
	/// </summary>
	/// <returns>
	/// 方向ベクトル。（CVector3）
	/// </returns>
	CVector3 GetCameraFront()const
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
	CVector3 m_jiku;								//軸
	CVector3 m_targetpos = CVector3::Zero();		//カメラの目標地点
	CVector3 m_position = CVector3::Zero();			//カメラの現在地
	Player* m_player = nullptr;						//プレイヤーのポインタ
};

