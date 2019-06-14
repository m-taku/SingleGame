#pragma once
#include "Player_State.h"
class Player_Special :public Player_State
{
public:
	Player_Special(Player* player);
	~Player_Special();
	/// <summary>
	/// アップデート関数
	/// </summary>
	void Update();
private:
	float m_scuea = 1.0f;
	Effekseer::Effect* m_sampleEffect = nullptr;			//エフェクトの実態のポインタ（？）
	Effekseer::Handle m_playEffectHandle;					//エフェクトのさすハンドル
};

