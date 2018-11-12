#pragma once
#include"physics/PhysicsStaticObject.h"
/// <summary>
/// ステージの門制御クラス。
/// </summary>
class Monn : public Gameobject
{
public:
	/// <summary>
	/// コンストラクタ。
	/// </summary>
	Monn();
	/// <summary>
	/// デストラクタ。
	/// </summary>
	~Monn();
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
	/// ポジションのセット。
	/// </summary>
	/// <param name="position">
	/// セットしたいポジション。（CVector3）
	/// </param>
	void SetPosition(CVector3 position)
	{
		m_position = position;
	}
	/// <summary>
	/// 回転角度のセット
	/// </summary>
	/// <param name="rot">
	/// 回転角度（CQuuaternion）
	/// </param>
	void Setrotation(CQuaternion rot)
	{
		m_rotation = rot;
	}
	/// <summary>
	/// 門の開く向きの制御関数
	/// </summary>
	void Setkaku()
	{
		if (m_kaihei) {
			m_rod *= -1;
			m_kaihei = false;
		}
		else
		{
			m_kaihei = true;
		}
	}
private:
	//PhysicsStaticObject m_monn;			
	SkinModel m_model;											//スキンモデルデータ
	MeshCollider m_meshCollider;								//メッシュコライダー。
	RigidBody m_rigidBody;										//剛体。
	CVector3 m_position = CVector3::Zero();						//門のポジション
	CQuaternion m_rotation = CQuaternion::Identity();			//門の角度
	bool m_kaihei = false;										//開いているかどうか
	float m_rod = 0.0f;											//回す角度
	float m_kaku = 0.0f;										//今の角度
};

