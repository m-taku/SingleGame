#pragma once
#include "character/CharacterController.h"
#include"EnemyState.h"
#include"../Player.h"
#include"Enemyleader.h"
#include"../Path.h"
class Enemy
{
public:
	Enemy();
	~Enemy();
	bool Load();
	void Update();
	void Draw();
	void postDraw();
	void Setposition(CVector3 position)
	{
		m_position = position;
	} 
	enum State {
		State_Tracking,		//追尾中	
		State_Move,
	};	
	/*
	*@brief	2Ｄ座標系での位置
	*@return CVector3
	*/
	CVector3 Get2Dposition()const
	{
		auto position = m_position;
		position.y = 0.0f;
		return position;
	}	
	/*
	*@brief	3Ｄ座標系での位置
	*@return CVector3
	*/
	CVector3 Get3Dposition()const
	{
		return m_position;
	}
	/*
	*@brief	移動速度
	*@return CVector3
	*/
	CVector3 Getspeed()
	{
		return m_speed;
	}
	/*
	*@brief	移動速度
	*@ CVector3
	*/
	void Setspeed(CVector3 speed)
	{
		m_speed = speed;
	}
	/*
	*@brief	回転角度
	*@return CQuaternion
	*/
	void Setangle(CQuaternion angle)
	{
		m_angle = angle;
	}
	/*
	*@brief	回転角度
	*@ CQuaternion
	*/
	CQuaternion Getangle()
	{
		return m_angle;
	}
	/*
	*@brief	ステートの遷移
	*/
	void transitionState(State state);
	/*
	*@brief Enemyleaderのセット
	*/
	void SetLeader(Enemyleader* leader)
	{
		Leader = leader;
	}
	/*
	*@brief Playerのセット
	*/
	void Setplayer(Player* pla)
	{
		player = pla;
	}
	/*
	*@brief Playerのセット
	*/
	void DDraw();
private:
	void Vectordraw();
	Path path;                                             
	EnemyState* m_enemystate=nullptr;						//エネミーのステート
	State state = State_Tracking;							//ステートの状態
	Enemyleader* Leader = nullptr;							//Leaderのポインタ
	Player* player = nullptr;								//Playerのポインタ
	CharacterController m_collider;							//キャラクターコントローラー
	CVector3 m_position = { 0.0f,150.0f,-30.0f };			//現在位置
	CVector3 m_speed = { 0.0f,-9.8f,0.0f };					//移動速度
	CQuaternion m_angle = CQuaternion::Identity();			//回転角度
	CQuaternion m_Sprite_angle = CQuaternion::Identity();	//テクスチャの回転角度
	CVector3 m_Sprite_Front = CVector3::AxisZ()*-1;	        //テクスチャの前方向
	bool DrewFragu = true;									//描画するかどうか
	sprite Sprite_hp;										//体力用の2Ｄ(中身)
	sprite Sprite_fram;										//体力用の2Ｄ(枠)
	float HP = 1.0f;										//ＨＰの割合
	ShaderResourceView texture_hp;							//体力用の2Ｄデータ(中身)
	ShaderResourceView texture_fram;						//体力用の2Ｄデータ(枠)
	VectorDraw* kasa = nullptr;								//デバック用のベクトル表示
}; 

