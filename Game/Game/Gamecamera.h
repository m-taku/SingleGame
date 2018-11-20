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
	bool Load() override;
	/// <summary>
	/// Gemeobjectから継承したUpdate関数。
	/// </summary>
	void Update() override;
	/// <summary>
	/// Gameobjectから継承したDraw関数。
	/// </summary>
	void Draw() override;
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
		return m_front;
	}
private:
	/// <summary>
	///プレイヤー座標系での基底軸を更新
	/// </summary>
	/// <remarks>
	/// 現在更新されるのは、y軸と、z軸のみ。
	/// </remarks>
	void UpdateBasisInPlayerSpace();
	/// <summary>
	/// 後ろに回り込むカメラの処理を実行する。
	/// </summary>
	/// <remarks>
	/// 最近のゲームの後ろに回り込むカメラの処理。
	/// ドラクエ11とか色々。
	/// </remarks>
	void ExecuteTracking();
	CVector3 m_playerFront = CVector3::Zero();		//プレイヤーの前方向
	CVector3 m_playerUp = CVector3::Zero();			//プレイヤーの上方向
	CVector3 m_right = CVector3::Zero();			//右方向
	CVector3 m_front = CVector3::AxisZ();			//前方向ベクトル
	CQuaternion	m_reg = CQuaternion::Identity();	//回転角度
	CMatrix m_mRot = CMatrix::Identity();			//回転行列
	CVector3 m_angle = CVector3::Zero();			//回転入力量
	CVector3 m_axis = CVector3::Zero();				//軸
	CVector3 m_targetpos = CVector3::Zero();		//カメラの目標地点
	CVector3 m_position = CVector3::Zero();			//カメラの現在地
	Player* m_player = nullptr;						//プレイヤーのポインタ
};

