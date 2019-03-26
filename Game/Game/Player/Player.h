#pragma once
#include "character/CharacterController.h"
#include"UI.h"
#include"Status.h"
class Player_State;
class Gamecamera;
class Navimake;
/// <summary>
/// プレイヤークラス
/// </summary>
class Player : public Gameobject
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
	const Ability* p_status = new PlyerStatus;
	/// <summary>
	/// アニメーション用のenum。
	/// </summary>
	enum animation {
		walk,		//歩きアニメーション
		idle,		//停止アニメーション
		run,		//走りアニメーション
		hit,		//ヒットアニメーション
		ded,		//死亡アニメーション
		attack,		//攻撃アニメーション
		defens,		//防御アニメーション
		animnum		//アニメーション状態
	};
	/// <summary>
	/// 状態のEnum
	/// </summary>
	enum State {
		State_Attack,		//攻撃中
		State_Move,			//移動中
		State_Guard,		//防御中
		State_Hit,			//ヒット中
		State_did			//死亡中
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
	/// Gameobjectから継承したStop関数
	/// </summary>
	void Stop()override;
	/// <summary>
	/// Hit時にHitObjictから呼ばれる関数
	/// </summary>
	void Hit(float damage);
	/// <summary>
	/// 2D（ｘ、ｚ）での現在のポジション。
	/// </summary>
	/// <remarks>
	/// 3D次元で返す関数もあるので適しているか確認。
	/// </remarks>
	/// <returns>
	/// 2Dでのポジション。（CVector3）
	/// </returns>
	CVector3 Get2DPosition() const
	{
		auto position = m_position;
		position.y = 0.0f;
		return position;
	}
	/// <summary>
	/// アニメーションの変更
	/// </summary>
	/// <param name="Animation">
	/// 変えたいアニメーション
	/// </param>
	/// <param name="taim">
	/// 保管時間（指定なしで0.2）
	/// </param>
	void ChangeAnimation(animation Animation, float taim = 0.2f)
	{
		m_animation.Play(Animation, taim);
	}
	/// <summary>
	/// アニメーションイベントの取得
	/// </summary>
	/// <returns>
	/// teueでイベント期間
	/// </returns>
	const bool IsEvent()
	{
		return m_animation.IsEvent();
	}
	/// <summary>
	/// 前方向の更新（角度変更後に呼んでください）
	/// </summary>
	void UpdateFront()
	{
		m_mRot.MakeRotationFromQuaternion(m_rotation);
		m_Front.x = m_mRot.m[2][0];
		m_Front.y = m_mRot.m[2][1];
		m_Front.z = m_mRot.m[2][2];
		m_Front.Normalize();
	}
	/// <summary>
	/// アニメーションが再生中かどうか
	/// </summary>
	/// <returns>
	/// trueで再生中
	/// </returns>
	const bool GetAnimationPlaying()
	{
		return m_animation.IsPlaying();
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
	const CVector3& Get3DPosition() const
	{
		return m_position;
	}
	/// <summary>
	/// スピードのセット
	/// </summary>
	/// <param name="speed">
	/// 割合で制御します（1で最大）
	/// </param>
	void SetSpeed(float speed)
	{
		m_speed = speed;
	}
	/// <summary>
	/// スピードのゲット
	/// </summary>
	/// <returns>
	/// 割合で返ります（1で最大）
	/// </returns>
	const float GetSpeed()const
	{
		return m_speed;
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
	const CVector3& GetMoveStick() const
	{
		return m_amount;
	}
	/// <summary>
	/// モデルの前方向。
	/// </summary>
	/// <returns>
	/// 方向ベクトル。（CVector3）
	/// </returns>
	const CVector3& GetFront() const
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
	/// ステータスのゲット
	/// </summary>
	/// <returns>
	/// ステータスのインスタンス（Ability）
	/// </returns>
	const Ability& GetStatu()
	{
		return *m_plyerStatus;
	}
	/// <summary>
	/// カメラのインスタンスのゲット
	/// </summary>
	/// <returns>
	/// カメラのインスタンス（Gamecamera*）
	/// </returns>
	Gamecamera* GetCamera()
	{
		return m_camera;
	}
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
		float hidame = damage - m_plyerStatus->m_Defense;
		if (hidame > 0.0f) {
			m_plyerStatus->m_HP -= hidame;
			auto wariai = m_plyerStatus->m_HP / p_status->m_HP;
			m_ui->SetDamage(1.0f - wariai);
		}
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
	/// アニメーションの初期化
	/// </summary>
	void InitAnimation();
	/// <summary>
	/// 角度のセット
	/// </summary>
	/// <param name="rotation">
	/// 変更後の角度（CQuaternion）
	/// </param>
	void SetRotation(const CQuaternion& rotation)
	{
		m_rotation = rotation;
	}
	/// <summary>
	/// デバック用の点表示
	/// </summary>
	/// <param name="pos">
	/// 表示したい点（CVector3）
	/// </param>
	void SetDebegVector(const CVector3& pos)
	{
		m_debugVector->Update(pos);
	}
	/// <summary>
	/// ステートの遷移
	/// </summary>
	/// <param name="m_state">
	/// 遷移後のステート（Player::State）
	/// </param>
	void TransitionState(State m_state);
	/// <summary>
	/// 攻撃用に手のボーンを検索
	/// </summary>
	void FindArm();
	/// <summary>
	/// 
	/// </summary>
	/// <returns></returns>
	const CMatrix& GetArmMatrix()
	{
		return m_model.GetSkeleton().GetBone(m_armboneNo)->GetWorldMatrix();
	}
	/// <summary>
	/// 当たり判定を反転させる
	/// </summary>
	void ReverseHit()
	{
		m_Hit = !m_Hit;
	}
	//ここからアイテムによるステータス変更
	//不完全なのでオミット
	//void SetStatu_Speed(float speed)
	//{
	//	m_plyerStatus->m_Speed = max(m_plyerStatus->m_Speed, speed);
	//}
	//void SetStatu_Attack(float attack)
	//{
	//	m_plyerStatus->m_Attack = max(m_plyerStatus->m_Attack, attack);
	//}
	//void SetStatu_Defense(float defense)
	//{
	//	m_plyerStatus->m_Defense = max(m_plyerStatus->m_Defense, defense);
	//}
	//void AddStatu_NowHP(float now_HP)
	//{
	//	m_plyerStatus->m_HP = max(p_status->m_HP, m_plyerStatus->m_HP + now_HP);
	//	auto wariai = m_plyerStatus->m_HP / p_status->m_HP;
	//	m_ui->SetDamage(1.0f - wariai);
	//}
private:
	CharacterController m_collider;						//キャラクターコントローラー
	SkinModel m_model;									//モデルデータ
	AnimationClip m_animationclip[animnum];				//アニメーションクリップ
	Animation m_animation;								//アニメーション
	UI* m_ui = nullptr;									//アニメーションのインスタンス
	Gamecamera* m_camera = nullptr;						//カメラのポインタ
	VectorDraw* m_debugVector = nullptr;				//デバック用のベクトル表示
	Player_State* m_State = nullptr;					//ステートのインスタンス
	Ability* m_plyerStatus = new PlyerStatus;			//ステータス
	CVector3 m_movespeed = CVector3::Zero();			//移動速度
	CVector3 m_playerUp = CVector3::AxisY();			//上方向
	CVector3 m_Front = CVector3::Zero();				//前方向
	CVector3 m_position = { 0.0f,150.0f,-30.0f };		//現在位置
	CVector3 m_amount = { 0.0f,0.0f,0.0f };				//スティックの移動量
	CQuaternion m_rotation = CQuaternion::Identity();	//回転クオータニオン
	CMatrix m_mRot = CMatrix::Identity();				//回転行列
	int m_armboneNo = -1;								//手のボーン番号
	float m_speed = 0.0f;								//移動速度
	float m_angle = 0.0f;								//回転角度（ラジアン）
	bool m_Hit = false;									//当てる状態かどうか
	//アイテム用のタイマーインスタンス
	Timer m_Attacktimer;
	Timer m_Defensetimer;
	Timer m_Speedtimer;
};