#pragma once
#include"../../Player/Player.h"
#include "character/CharacterController.h"
#include"../../Path.h"
#include <array> 
class Enemy;
class Enemyleader:public Gameobject
{
public:
	Enemyleader();
	~Enemyleader();
	//グループの状態
	enum State{
		group,
		person,
		gathering
	};
	/*
	*@brief	ポジションセット
	*@ CVector3
	*/
	void Setposition(CVector3 Position)
	{
		position = Position;
	}
	/*
	*@brief	インスタンシングのインスタンス
	*return SkinModel
	*/
	SkinModel& GetSkinmdel()
	{
		return m_model;
	}
	/*
	*@brief	プレイヤーのインスタンスセット
	*@ Player
	*/
	void Setplayer(Player* pa)
	{
		player = pa;
	}
	/*
	*@brief	グループの状態セット
	*@ Enemyleader::State
	*/
	void SetSteat(State s)
	{
		state = s;
	}
	/*
	*@brief	リーダーのポジションゲット
	*@return CVector3
	*/
	CVector3 Getposition()
	{
		return position;
	}
	bool Load();
	void Update();
	void Draw();

	void move();
private:
	CVector3 haiti[5] = {
	{ 70.0f,0.0f,0.0f },
	{-70.0f,0.0f,0.0f},
	{0.0f,0.0f,-70.0f},
	{0.0f,0.0f,70.0f},
	{0.0f,0.0f,0.0f}
	};
	CVector3 haiti2[5] = {
		{ 70.0f,0.0f,0.0f },
	{ -70.0f,0.0f,70.0f },
	{ -70.0f,0.0f,-70.0f },
	{ 70.0f,0.0f,-70.0f },
	{ 0.0f,0.0f,70.0f }
	};													        //中心から移動分
	CVector3 position = { 0.0f,100.0f,0.0f };				    //架空のリーダーのポジション
	Path* path=nullptr;										    //経路探査用のインスタンス
	CVector3 m_nextpos = CVector3::Zero();						//パス移動用の次ポジション
	CVector3 m_oldposition = CVector3::Zero();					//1フレーム前のポジション（壁擦りなどの判定などなど）
	CharacterController m_collider;								//キャラクターコントローラー
	SkinModel m_model;											//インスタンシング用の描画インスタンス
	static const int SOLDIER = 5;								//リーダーを含む部隊の総数
	State state = { group };									//グループの今の状態
	Player* player;												//プレイヤーのインスタンス
	std::array<Enemy*, SOLDIER> enemy;							//エネミーのインスタンス（SOLDIER）
	//std::vector<Enemy*> enemy;									
	int No = 0;
	int remaining = SOLDIER;									//今現在のエネミー総数
	int m_time = 0;		//仮？？
};

