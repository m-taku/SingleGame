#pragma once
#include"../../Player/Player.h"
#include "character/CharacterController.h"
#include"Path.h"
#include"Score.h"
#include <array> 
#include"Status.h"
/// <summary>
/// Enemyの1グループ単位での動作クラス。
/// </summary>
class HitObjict;
class Enemy;
class Enemyleader:public Gameobject
{
public:
	/// <summary>
	/// コンストラクタ。
	/// </summary>
	Enemyleader();
	/// <summary>
	/// デストラクタ。
	/// </summary>
	~Enemyleader();	
	/// <summary>
	/// Gameobjectから継承した最初に呼ばれる関数。
	/// </summary>
	/// <returns>
	/// Load成功でtrue、失敗でfalse。
	/// </returns>
	bool Load() override;
	/// <summary>
	/// Gameobjectから継承した毎フレーム呼ばれる関数。
	/// </summary>
	void Update() override;
	/// <summary>
	/// Gameobjectから継承した表示用関数。
	/// </summary>
	void Draw() override;
	/// <summary>
	/// Gameobjectから継承したstop関数
	/// </summary>
	void Stop() override;
	/// <summary>
	/// アニメーション用のenum。
	/// </summary>
	enum animation 	{
		idle,		//停止アニメーション	
		walk,
		animnum		//アニメーション状態
	};
	/// <summary>
	/// グループの状態のenum。
	/// </summary>
	enum State{
		group_stop,		//グループ状態
		group_move,		
		person,		//個人状態
		gathering	//集合中状態
	};
	/// <summary>
	/// ポジションのセット。
	/// </summary>
	/// <param name="Position">
	/// セットしたいポジション。(CVector3)
	/// </param>
	void SetPosition(const CVector3& Position)
	{
		m_position = Position;

	}
	/// <summary>
	/// スキンモデルインスタンスの取得。
	/// （constなしのため注意！！）
	/// </summary>
	/// <remarks>
	/// インスタンシング用のデータ遷移時に使用。
	/// </remarks>
	/// <returns>
	/// スキンモデルのインスタンス。(SkinModel*)
	/// </returns>
	SkinModel& CopySkinModel()
	{
		return m_model;
	}
	/// <summary>
	/// プレイヤーのインスタンスのセット。
	/// </summary>
	/// <param name="player">
	/// セットしたいプレイヤーのインスタンス。(Player*)
	/// </param>
	void SetPlayer(Player* player)
	{
		m_player = player;
	}
	/// <summary>
	/// グループの状態遷移。
	/// </summary>
	/// <param name="steat">
	/// 変更したい状態。(Enemyleader::State)
	/// </param>
	void ChangeSteat(State steat)
	{
		m_state = steat;
	}
	/// <summary>
	/// リーダーのポジションのゲット。
	/// </summary>
	/// <returns>
	/// リーダーのポジション。(CVector3)
	/// </returns>
	const CVector3& GetPosition()
	{
		return m_position;
	}
	/// <summary>
	/// グループ化の判定。
	/// </summary>
	/// <remarks>
	/// すべての敵が集まった場合グループ状態になる。
	/// </remarks>
	void RollCall()
	{
		m_ninzuu++;
	}
	/// <summary>
	/// グループ状態での移動計算処理。
	/// </summary>
	void Move();
	/// <summary>
	/// ステートをグループでの移動に変更する
	/// </summary>
	void ChangeGroup_Move()
	{
		if (m_stopcount == 0) {
			m_group_state = group_move;
			m_path->Course(m_position, m_player->Get2DPosition());
			m_nextpos = m_path->PathPos();
		}
	}
	/// <summary>
	/// ステートをグループでの停止に変更する
	/// </summary>
	void ChangeGroup_stop(int count)
	{
		if (count != 0) {
			m_group_state = group_stop;
			m_stopcount = count;
		}
	}
	/// <summary>
	/// ステートをグループでの停止に変更する
	/// </summary>
	void Stop_count()
	{
		m_stopcount--;
		if(m_stopcount==0)
		{
			m_group_state = group_move;
			m_stopcount = 0;
		}

	}
	/// <summary>
	/// グループ全体が生きているかどうか
	/// </summary>
	/// <returns>
	/// trueで生存してます
	/// </returns>
	const bool Getlife()
	{
		return m_life;
	}
	/// <summary>
	/// ステータスのセット
	/// </summary>
	/// <param name="Status">
	/// ステータスクラス（Ability）
	/// </param>
	void SetStatus(Ability* Status)
	{
		m_Status = Status;
	}
	/// <summary>
	/// スコア集計クラスのセット
	/// </summary>
	/// <param name="score">
	/// スコア集計クラス（Score）
	/// </param>
	void SetScore(Score* score)
	{
		m_Score = score;
	}
private:
	SkinModel m_model;											//インスタンシング用の描画インスタンス
	AnimationClip m_animationclip[animnum];						//アニメーションクリップ
	Animation m_animation;										//アニメーションのインスタンス
	State m_state = { group_stop };								//グループの今の状態
	State m_group_state = { group_stop };						//グループでの今の状態
	Ability* m_Status = nullptr;								//ステータスのインスタンス
	Score* m_Score = nullptr;									//スコア集計クラスのインスタンス
	Path* m_path=nullptr;									    //経路探査用のインスタンス
	Player* m_player = nullptr;									//プレイヤーのインスタンス
	std::list<Enemy*> m_enemy;						            //エネミーのインスタンス（SOLDIER）
	CVector3 m_position = { 0.0f,100.0f,0.0f };				    //架空のリーダーのポジション
	CVector3 m_nextpos = CVector3::Zero();						//パス移動用の次ポジション
	CVector3 m_movespeed = { 0.0f,0.0f,0.0f };					//移動速度
	CVector3 m_oldposition = CVector3::Zero();					//1フレーム前のポジション（壁擦りなどの判定などなど）
	CVector3 m_Front = CVector3::Zero();						//エネミーの前方向
	CMatrix m_Rot;												//角度に関する行列
	CQuaternion m_angle = CQuaternion::Identity();				//回転角度
	int m_fream = 0;											//移動処理用のフレーム計算
	int m_remaining = 5;										//今現在のエネミー総数		
	int m_ninzuu = 0;											//今現在のグループ状態の人数（集合時に使用）
	bool m_life = true;											//生存フラグ
	int m_stopcount = 0;
	const float m_kaku = 10.0f;									//1フレームで回転させる最大角度(degree)
	const float m_margin = CMath::DegToRad(m_kaku);				//1フレームで回転させる最大角度(radian)
										
};

