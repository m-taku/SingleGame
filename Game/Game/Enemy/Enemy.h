#pragma once
#include "character/CharacterController.h"
#include"../Player/Player.h"
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
	/// Gameobjectから継承した最初に呼ばれる関数。
	/// </summary>
	/// <returns>
	/// Load成功でtrue、失敗でfalse。
	/// </returns>
	bool Load();
	/// <summary>
	/// Gameobjectから継承した毎フレーム呼ばれる関数。
	/// </summary>
	void Update();
	/// <summary>
	/// Gameobjectから継承した表示用関数。
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
	/// <param name="state">
	/// 遷移したいステート。（Enemy::State）
	/// </param>
	void TransitionState(State state);
	/// <summary>
	/// 所属しているリーダーのセット。
	/// </summary>
	/// <param name="leader">
	/// リーダーのインスタンス。（Enemyleader*）
	/// </param>
	void SetLeader(Enemyleader* leader)
	{
		Leader = leader;
	}
	/// <summary>
	///  プレイヤーのインスタンスのセット。
	/// </summary>
	/// <param name="player">
	/// セットしたいプレイヤーのインスタンス。(Player*)
	/// </param>
	void Setplayer(Player* player)
	{
		m_player = player;
	}
	/// <summary>
	/// 所属しているリーダーの状態遷移。
	/// </summary>
	/// <param name="leader">
	/// 変更したい状態。(Enemyleader::State)
	/// </param>
	void ChangeLeaderState(Enemyleader::State ka)
	{
		Leader->ChangeSteat(ka);
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
	void SetLeaderposition(CVector3 position)
	{
		Leader->SetPosition(position);
	}
	/// <summary>
	/// 集合する際の判定関数。
	/// </summary>
	void Rollcall()
	{
		Leader->Rollcall();
	}
	/// <summary>
	/// 所属しているリーダーのポジションのゲット。
	/// </summary>
	/// <returns>
	/// 所属しているリーダーのポジション。（CVector3）
	/// </returns>
	CVector3 GetLeaderPosition()const
	{
		return Leader->GetPosition();
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
	/// キャラクターコントローラーの交代の更新
	/// </summary>
	/// <remarks>
	/// 当たり判定は取っていません。動かすだけです。
	/// </remarks>
	/// <param name="position">
	/// 更新後のポジション。（CVector3）
	/// </param>
	void SetCollider(CVector3 position)
	{
		m_collider.SetPosition(m_position);
	}
private:
	/// <summary>
	/// デバック用のベクトル表示。
	/// </summary>
	void Vectordraw();
	SkinModel m_model;										//インスタンシング抜きの１人１人のインスタンス
	ShaderResourceView texture_hp;							//体力用の2Ｄデータ(中身)
	ShaderResourceView texture_fram;						//体力用の2Ｄデータ(枠)
	sprite Sprite_hp;										//体力用の2Ｄ(中身)
	sprite Sprite_fram;										//体力用の2Ｄ(枠)
	CharacterController m_collider;					        //キャラクターコントローラー
	Enemyleader* Leader = nullptr;							//Leaderのポインタ
	Player* m_player = nullptr;								//Playerのポインタ
	VectorDraw* kasa = nullptr;								//デバック用のベクトル表示
	Path m_path;											//経路探査のインスタンス
	EnemyState* m_enemystate = nullptr;						//エネミーのステート
	State state = State_Tracking;							//ステートの状態
	CMatrix mRot;											//角度に関する行列
	CVector3 m_position = { 0.0f,150.0f,-30.0f };			//現在位置
	CVector3 m_moveVector = CVector3::Zero();				//移動させるベクトル
	CVector3 m_Front = CVector3::Zero();					//エネミーの前方向
	CVector3 m_Sprite_Front = CVector3::AxisZ()*-1;	        //テクスチャの前方向
	CVector3 m_oldposition = CVector3::Zero();				//1フレーム前のポジション（壁擦りなどの判定などなど）
	CVector3 m_nextpos = CVector3::Zero();					//経路探査で出た次のポジション
	CQuaternion m_angle = CQuaternion::Identity();			//回転角度
	CQuaternion m_Sprite_angle = CQuaternion::Identity();	//テクスチャの回転角度
	const float m_kaku = 30.0f;								//1フレームで回転させる最大角度(degree)
	const float m_margin = CMath::DegToRad(m_kaku);			//1フレームで回転させる最大角度(radian)
	float m_HP = 1.0f;										//ＨＰの割合
	float m_speed = 500.0f;             					//移動速度

};

