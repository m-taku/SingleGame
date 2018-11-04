#pragma once
#include "character/CharacterController.h"
#include"../../Player/Player.h"
#include"Enemyleader.h"
class EnemyState;
class Enemy
{
public:
	Enemy();
	~Enemy();
	bool Load();
	void Update();
	void Draw();
	void postDraw();

	enum State {
		State_Tracking,		//追尾中	
		State_Move,			//尾行中
		State_Attack,		//攻撃中
		State_Gathering
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
	*@brief	移動ベクトル
	*@return CVector3
	*/
	CVector3 Getmove()
	{
		return m_moveVector;
	}
	/*
	*@brief	移動量
	*@ CVector3
	*/
	void Setmove(float speed)
	{
		m_speed = speed;
	}
	/*
	*@brief	回転量足しこみ
	*@ CQuaternion
	*/
	void AddAngle(CQuaternion angle)
	{
		m_angle.Multiply(angle, m_angle);

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
	*@brief	前方向のベクトル
	*@
	*/
	CVector3 Get2DFront()
	{
		m_Front.y = 0;
		m_Front.Normalize();
		return m_Front;
	}
	CVector3 Get3DFront()
	{
		m_Front.Normalize();
		return m_Front;
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
	*@brief ステートのセット
	*/
	void SetLeaderState(Enemyleader::State ka)
	{
		Leader->SetSteat(ka);
	}
	Path* Getpath()
	{
		return &path;
	}
	void PathGO()
	{
		path.course(Get2Dposition(), GetLeaderposition());
		m_nextpos = path.Pathpos();

	}
	void SetLeaderposition(CVector3 pos)
	{
		Leader->Setposition(pos);
	}
	void Incrementninzuu()
	{
		Leader->Incrementninzuu();
	}
	CVector3 GetLeaderposition()
	{
		return Leader->Getposition();
	}
	bool syuuketu();
	void DDraw();
	void Findangle(CVector3 Front);
private:
	void Vectordraw();
	EnemyState* m_enemystate = nullptr;						//エネミーのステート
	CMatrix mRot;
	Path path;
	State state = State_Tracking;							//ステートの状態
	Enemyleader* Leader = nullptr;							//Leaderのポインタ
	Player* player = nullptr;								//Playerのポインタ
	CharacterController m_collider;					       //キャラクターコントローラー
	CVector3 m_position = { 0.0f,150.0f,-30.0f };			//現在位置
	CVector3 m_moveVector = CVector3::Zero();				//
	CQuaternion m_angle = CQuaternion::Identity();			//回転角度
	CQuaternion m_Sprite_angle = CQuaternion::Identity();	//テクスチャの回転角度
	CVector3 m_Front = CVector3::Zero();					//エネミーの前方向
	float m_speed = 500.0f;             					//移動速度
	CVector3 m_Sprite_Front = CVector3::AxisZ()*-1;	        //テクスチャの前方向
	sprite Sprite_hp;										//体力用の2Ｄ(中身)
	sprite Sprite_fram;										//体力用の2Ｄ(枠)
	float m_HP = 1.0f;										//ＨＰの割合
	ShaderResourceView texture_hp;							//体力用の2Ｄデータ(中身)
	ShaderResourceView texture_fram;						//体力用の2Ｄデータ(枠)
	VectorDraw* kasa = nullptr;								//デバック用のベクトル表示
	CVector3 m_oldposition = CVector3::Zero();					//1フレーム前のポジション（壁擦りなどの判定などなど）
	CVector3 m_nextpos = CVector3::Zero();
	const float kaku = 30.0f;
	float m_margin = CMath::DegToRad(kaku);
public:
	void Setposition(CVector3 position)
	{
		m_position = position;
		m_collider.SetPosition(m_position);
	}
};

