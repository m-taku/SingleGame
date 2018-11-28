#pragma once
#include "character/CharacterController.h"
#include"../Player/Player.h"
#include"../../Path.h"
#include"EnemyLeader/EnemyLeader.h"
class EnemyState;
/// <summary>
/// Enemy1つ1つの動作クラス。
/// </summary>
class Enemy
{
public:
	/// <summary>
	/// コンストラクタ。
	/// </summary>
	Enemy();
	/// <summary>
	/// デストラクタ。
	/// </summary>
	~Enemy();
	/// <summary>
	/// 最初に呼ばれる関数。
	/// </summary>
	/// <returns>
	/// Load成功でtrue、失敗でfalse。
	/// </returns>
	bool Load();
	/// <summary>
	/// 毎フレーム呼ばれる関数。
	/// </summary>
	void Update();
	/// <summary>
	/// 表示用関数。
	/// </summary>
	void Draw();
	/// <summary>
	/// ポストーーーーーーーーーーー
	/// </summary>
	void postDraw();
	/// <summary>
	/// エネミーのステート（状態）のenum。
	/// </summary>
	enum State {
		State_Tracking,		//追尾中	
		State_Move,			//尾行中
		State_Attack,		//攻撃中
		State_Gathering		//集合中
	};
	/// <summary>
	/// アニメーション用のenum。
	/// </summary>
	enum animation {
		idle,		//停止アニメーション
		attack, 
		walk,
		animnum		//アニメーション状態
	};
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
	/// 3D（ｘ、ｙ、ｚ）での現在のポジション。
	/// </summary>
	/// <remarks>
	/// 2D次元で返す関数ももあるので適しているか確認。
	/// </remarks>
	/// <returns>
	/// 3Dでのポジション。（CVector3）
	/// </returns>
	CVector3 Get3DPosition()const
	{
		return m_position;
	}
	/// <summary>
	/// 移動速度の遷移。（初期値は500.0f）
	/// </summary>
	/// <param name="speed">
	/// 変更したい速度。（float）
	/// </param>
	void SetSpeed(const float& speed)
	{
		m_speed = speed;
	}
	/// <summary>
	/// モデルの回転角度への加算。
	/// </summary>
	/// <remarks>
	/// 直接指定する関数もあるので適しているか確認。
	/// </remarks>
	/// <param name="angle">
	/// 足したい角度のクオータニオン。（CQuaternion）
	/// </param>
	void AddAngle(CQuaternion angle)
	{
		m_angle.Multiply(angle, m_angle);

	}
	/// <summary>
	/// モデルの回転角度を直接指定。
	/// </summary>	
	/// <remarks>
	/// 回転角度に角度を加算する関数もあるので適しているか確認。
	/// </remarks>
	/// <param name="angle">
	/// 回したい角度のクオータニオン。（CQuaternion）
	/// </param>
	void SetAngle(CQuaternion angle)
	{
		m_angle = angle;
	}
	/// <summary>
	/// 今現在のモデルの回転角度を取得。
	/// </summary>
	/// <returns>
	/// モデルの回転角度。（CQuaternion）
	/// </returns>
	CQuaternion GetAngle() const
	{
		return m_angle;
	}
	/// <summary>
	/// 2D（ｘ、ｚ）での現在の前方向。
	/// </summary>
	/// <remarks>
	/// 3D次元で返す関数もあるので適しているか確認。
	/// </remarks>
	/// <returns>
	/// 2Dでの前方向。
	/// </returns>
	CVector3 Get2DFront()const
	{
		auto front = m_Front;
		front.y = 0;
		front.Normalize();
		return front;
	}
	/// <summary>
	/// 3D（ｘ、ｙ、ｚ）での現在の前方向。
	/// </summary>
	/// <remarks>
	/// 2D次元で返す関数もあるので適しているか確認。
	/// </remarks>
	/// <returns>
	/// 3Dでの前方向。(CVector3)
	/// </returns>
	CVector3 Get3DFront()const 
	{
		//m_Front.Normalize();
		return m_Front;
	}
	/// <summary>
	/// Enemyの状態遷移。
	/// </summary>	
	/// <remarks>
	/// Delete、Newがあるため少し重い。
	/// </remarks>
	/// <param name="m_state">
	/// 遷移したいステート。（Enemy::m_state）
	/// </param>
	void TransitionState(State m_state);
	/// <summary>
	/// 所属しているリーダーのセット。
	/// </summary>
	/// <param name="m_Leader">
	/// リーダーのインスタンス。（Enemyleader*）
	/// </param>
	void SetLeader(Enemyleader* Leader)
	{
		m_Leader = Leader;
	}
	/// <summary>
	///  プレイヤーのインスタンスのセット。
	/// </summary>
	/// <param name="player">
	/// セットしたいプレイヤーのインスタンス。(Player*)
	/// </param>
	void SetPlayer(Player* player)
	{
		m_player = player;
	}
	/// <summary>
	/// 所属しているリーダーの状態遷移。
	/// </summary>
	/// <param name="m_Leader">
	/// 変更したい状態。(Enemyleader::m_state)
	/// </param>
	void ChangeLeaderState(Enemyleader::State m_state)
	{
		m_Leader->ChangeSteat(m_state);
	}
	/// <summary>
	/// 経路探査のインスタンスのゲット。
	/// （constなしのため注意！！！）
	/// </summary>
	/// <returns>
	/// 経路探査のインスタンス。（Path*）
	/// </returns>
	Path* CopyPath()
	{
		return &m_path;
	}
	/// <summary>
	/// 所属しているリーダーに対してポジションをセット。
	/// </summary>
	/// <param name="position">
	/// セットしたいポジション。（CVector3）
	/// </param>
	void SetLeaderPosition(CVector3 position)
	{
		m_Leader->SetPosition(position);
	}
	/// <summary>
	/// 集合する際の判定関数。
	/// </summary>
	void RollCall()
	{
		m_Leader->RollCall();
	}
	/// <summary>
	/// 所属しているリーダーのポジションのゲット。
	/// </summary>
	/// <returns>
	/// 所属しているリーダーのポジション。（CVector3）
	/// </returns>
	CVector3 GetLeaderPosition()const
	{
		return m_Leader->GetPosition();
	}
	/// <summary>
	/// HPバーの計算+表示。
	/// </summary>
	void HP_Draw();
	/// <summary>
	/// 今のモデルの向きに対して
	/// 進行方向は、何度角度がついているか。
	/// </summary>
	/// <param name="Vector">
	/// 進行方向を表すベクトル。（CVector3）
	/// </param>
	void FindAngle(CVector3 Vector);
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
	///　モデルのインスタンスのゲット。
	/// （constなしのため注意！！！）
	/// </summary>
	/// <returns>
	/// モデルのインスタンス（SkinModel）
	/// </returns>
	SkinModel& CopyModel()
	{
		return m_model;
	}
	/// <summary>
	/// 腕の位置のボーン番号
	/// </summary>
	/// <returns>
	/// ボーン番号（int）
	/// </returns>
	int GetNo()
	{
		return bolnNo;
	}
	/// <summary>
	/// 
	/// </summary>
	/// <param name="Animation"></param>
	void ChangeAnimation(animation Animation)
	{
		m_animation.Play(Animation,0.1);
		//m_animation.Update(0.01f);
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
		//m_collider.SetPosition(m_position);
	}
private:
	/// <summary>
	/// デバック用のベクトル表示。
	/// </summary>
	void DrawDebugVector();
	SkinModel m_model;										//インスタンシング抜きの１人１人のインスタンス
	ShaderResourceView m_texture_hp;						//体力用の2Ｄデータ(中身)
	ShaderResourceView m_texture_fram;						//体力用の2Ｄデータ(枠)
	sprite m_Sprite_hp;										//体力用の2Ｄ(中身)
	sprite m_Sprite_fram;									//体力用の2Ｄ(枠)
	//CharacterController m_collider;					        //キャラクターコントローラー
	AnimationClip m_animationclip[animnum];					//アニメーションクリップ
	Animation m_animation;									//アニメーションのインスタンス
	Enemyleader* m_Leader = nullptr;						//m_Leaderのポインタ
	Player* m_player = nullptr;								//Playerのポインタ
	VectorDraw* m_debugVecor = nullptr;						//デバック用のベクトル表示
	Path m_path;											//経路探査のインスタンス
	EnemyState* m_enemystate = nullptr;						//エネミーのステート
	State m_state = State_Tracking;							//ステートの状態
	CMatrix m_Rot;											//角度に関する行列
	CVector3 m_position = { 0.0f,150.0f,-30.0f };			//現在位置
	CVector3 m_moveVector = CVector3::Zero();				//移動させるベクトル
	CVector3 m_Front = CVector3::Zero();					//エネミーの前方向
	CVector3 m_Sprite_Front = CVector3::AxisZ()*-1;	        //テクスチャの前方向
	CVector3 m_oldposition = CVector3::Zero();				//1フレーム前のポジション（壁擦りなどの判定などなど）
	CVector3 m_nextpos = CVector3::Zero();					//経路探査で出た次のポジション
	CQuaternion m_angle = CQuaternion::Identity();			//回転角度
	CQuaternion m_Sprite_angle = CQuaternion::Identity();	//テクスチャの回転角度
	const float m_kaku = 10.0f;								//1フレームで回転させる最大角度(degree)
	const float m_margin = CMath::DegToRad(m_kaku);			//1フレームで回転させる最大角度(radian)
	int bolnNo = 0;
	float m_HP = 1.0f;										//ＨＰの割合
	float m_speed = 0.0f;             					//移動速度

};

