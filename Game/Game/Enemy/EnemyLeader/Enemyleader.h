#pragma once
#include"../../Player/Player.h"
#include "character/CharacterController.h"
#include"../../Path.h"
#include <array> 
/// <summary>
/// Enemy1グループの動作クラス。
/// </summary>
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
	/// アニメーション用のenum。
	/// </summary>
	enum animation 	{
		idle,		//停止アニメーション
		attack,
		animnum		//アニメーション状態
	};
	/// <summary>
	/// グループの状態のenum。
	/// </summary>
	enum State{
		group,		//グループ状態
		person,		//個人状態
		gathering	//集合中状態
	};
	/// <summary>
	/// ポジションのセット。
	/// </summary>
	/// <param name="Position">
	/// セットしたいポジション。(CVector3)
	/// </param>
	void SetPosition(CVector3 Position)
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
	CVector3 GetPosition()
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
private:
	static const int SOLDIER = 3;								//リーダーを含む部隊の総数（定数）
	CVector3 m_haiti[5] = {
	{ 70.0f,0.0f,0.0f },
	{-70.0f,0.0f,70.0f},
	{-70.0f,0.0f,-70.0f},
	{0.0f,0.0f,70.0f},
	{0.0f,0.0f,0.0f}
	};														    //発生位置の調整のための数値			
	CVector3 m_haiti2[5] = {
		{ 70.0f,0.0f,0.0f },
	{ -70.0f,0.0f,70.0f },
	{ -70.0f,0.0f,-70.0f },
	{ 70.0f,0.0f,-70.0f },
	{ 0.0f,0.0f,70.0f }
	};													        //中心から移動分
	SkinModel m_model;											//インスタンシング用の描画インスタンス
	//CharacterController m_collider;							//キャラクターコントローラー
	AnimationClip m_animationclip[animnum];						//アニメーションクリップ
	Animation m_animation;										//アニメーションのインスタンス
	Path* m_path=nullptr;									    //経路探査用のインスタンス
	Player* m_player = nullptr;									//プレイヤーのインスタンス
	std::array<Enemy*, SOLDIER> m_enemy;						//エネミーのインスタンス（SOLDIER）
	CVector3 m_position = { 0.0f,100.0f,0.0f };				    //架空のリーダーのポジション
	CVector3 m_nextpos = CVector3::Zero();						//パス移動用の次ポジション
	CVector3 m_oldposition = CVector3::Zero();					//1フレーム前のポジション（壁擦りなどの判定などなど）
	State m_state = { group };									//グループの今の状態
	int m_remaining = SOLDIER;									//今現在のエネミー総数		
	int m_ninzuu = 0;											//今現在のグループ状態の人数（集合時に使用）
};

