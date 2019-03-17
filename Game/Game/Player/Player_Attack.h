#pragma once
#include "Player_State.h"
class Player_Attack :public Player_State
{
public:
	Player_Attack(Player* player);
	~Player_Attack();
	void Update();
	void FindSwordpos();
private:
	CVector3 m_oldhandpos = CVector3::Zero();				//移動前の手のポジション
	CVector3 m_handpos = CVector3::Zero();					//移動後の手のポジション
	CVector3 m_oldSwordcenter = CVector3::Zero();			//移動前の剣の中心ポジション
	CVector3 m_Swordcenter = CVector3::Zero();				//移動後の剣の中心ポジション
	CVector3 m_Up;											//手の上方向ベクトル
	bool m_Hit = false;										//攻撃を当てたかどうか（当てたら判定を消す）
};

