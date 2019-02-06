#pragma once
#include "character/CharacterController.h"
#include"UI.h"
class Player_State;
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
	struct PlyerStatus
	{
		float Max_HP = 100.0f;				//マックスのHP
		float Attack = 10.0f;				//基本の攻撃力
		float defense = 10.0f;				//基本の守備力
		float speed = 500.0f;				//
	};
	/// <summary>
	/// アニメーション用のenum。
	/// </summary>
	enum animation {
		ded,
		idle,		//停止アニメーション
		run,
		hit,
		attack,
		defens,
		walk,
		animnum		//アニメーション状態
	};
	enum State {
		State_Attack,		//攻撃中
		State_Move,			//
		State_Guard,		//
		State_Hit,
		State_did
	};
	/// <summary>
	/// Gameobjectから継承したOnDestroy関数
	/// </summary>
	void OnDestroy() override;
	/// <summary>
	/// Gemeobjectから継承したLoat関数。
	/// </summary>
	/// <returns>
	/// 成功でtrue、失敗でfalse。
	/// </returns>
	bool Load() override;
	/// <summary>
	/// Gameobjectから継承したUpdate関数
	/// </summary>
	void Update() override;
	/// <summary>
	/// Gameobjectから継承したDraw関数
	/// </summary>
	void Draw() override;
	/// <summary>
	/// 
	/// </summary>
	void Hit();
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
	/// 
	/// </summary>
	/// <param name="Animation">
	/// 
	/// </param>
	void ChangeAnimation(animation Animation,float taim=0.2f)
	{
		m_animation.Play(Animation, taim);
	}
	void UpdateFront()
	{
		m_mRot.MakeRotationFromQuaternion(m_rotation);
		m_Front.x = m_mRot.m[2][0];
		m_Front.y = m_mRot.m[2][1];
		m_Front.z = m_mRot.m[2][2];
		m_Front.Normalize();
	}
	bool GetanimationPlaying()
	{
		return m_animation.IsPlaying();
	}
	/// <summary>
	/// 
	/// </summary>
	/// <param name="Animation">
	/// 
	/// </param>
	//bool AnimationPlaying()
	//{
	//	return m_animation.IsPlaying();
	//}
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
	void Setspeed(float speed)
	{
		m_speed = speed;
	}
	/// <summary>
	/// 回転行列を取得。
	/// </summary>
	/// <returns>
	/// 回転行列。(CMatrix)
	/// </returns>
	const CMatrix& GetMatrix() const
	{
		return m_mRot;
	}	
	/// <summary>
	/// スティックの移動量の取得。
	/// </summary>
	/// <returns>
	/// 移動量のベクトル。(CVector3)
	/// </returns>
	CVector3 Getangle() const
	{
		return m_amount;
	}
	/// <summary>
	/// モデルの前方向。
	/// </summary>
	/// <returns>
	/// 方向ベクトル。（CVector3）
	/// </returns>
	CVector3 GetFront() const
	{
		return m_Front;
	}
	/// <summary>
	/// Gamecameraのポインタを取得。
	/// </summary>
	/// <param name="camera">
	/// セットしたいカメラのインスタンス。(Gamecamera*)
	/// </param>
	void SetCamera(Gamecamera* camera)
	{
		m_camera = camera;
	}
	/// <summary>
	/// 
	/// </summary>
	/// <returns></returns>
	Gamecamera* Getcamera()
	{
		return m_camera;
	}
	//カメラのポインタ
	/// <summary>
	/// ポジションのセット
	/// </summary>
	/// <param name="position">
	/// セットしたいポジション（CVector3）
	/// </param>
	void SetPosition(CVector3 position)
	{
		m_position = position;
		ChangeColliderPosition(m_position);
	}
	/// <summary>
	/// ダメージ処理
	/// </summary>
	/// <param name="damage">
	/// プレイヤーに与えるダメージ（ダメージ量そのまま）（float）
	/// </param>
	void Damage(float damage)
	{
		
		auto wariai = (damage - m_plyerStatus.defense) / m_plyerStatus.Max_HP;
		/*HPの最大値*/

		//ここで０～1の形に変換
		m_ui->SetDamage(wariai);
	}
	/// <summary>
	/// キャラクターコントローラーの交代の更新
	/// </summary>
	/// <remarks>
	/// 当たり判定は取っていません。動かすだけです。
	/// </remarks>
	/// <param name="position">
	/// 更新後のポジション。（CVector3）
	/// </param>
	void ChangeColliderPosition(CVector3 position)
	{
		m_collider.SetPosition(position);
	}
	/// <summary>
	/// 
	/// </summary>
	void InitAnimation();
	/// <summary>
	/// 
	/// </summary>
	/// <param name="rotation"></param>
	void Setrotation(CQuaternion rotation)
	{
		m_rotation = rotation;
	}
	/// <summary>
	/// 
	/// </summary>
	/// <param name="m_state"></param>
	void TransitionState(State m_state);
private:
	UI* m_ui = nullptr;
	CharacterController m_collider;						//キャラクターコントローラー
	SkinModel m_model;									//モデルデータ
	AnimationClip m_animationclip[animnum];						//アニメーションクリップ
	Animation m_animation;										//アニメーションのインスタンス
	CVector3 m_movespeed = CVector3::Zero();			//移動速度
	CQuaternion m_rotation = CQuaternion::Identity();	//回転クオータニオン
	CMatrix m_mRot=CMatrix::Identity();					//回転行列
	Gamecamera* m_camera = nullptr;						//カメラのポインタ
	CVector3 m_playerUp = CVector3::AxisY();					//上方向
	CVector3 m_Front = CVector3::Zero();				//前方向
	CVector3 m_position = { 0.0f,150.0f,-30.0f };		//現在位置
	CVector3 m_amount = { 0.0f,0.0f,0.0f };				//スティックの移動量
	float m_angle = 0.0f;								//回転角度（ラジアン）
	VectorDraw* m_debugVector =nullptr;					//デバック用のベクトル表示
	PlyerStatus m_plyerStatus;
	Player_State* m_State = nullptr;
	bool m_ded=false;
	float m_speed = 0.0f;

	//CVector3 m_angle = CVector3::Zero();				
	//wchar_t bonename[50];								//名前
	//int bonenum = 0;									
	//int boneNo = 0;
};

