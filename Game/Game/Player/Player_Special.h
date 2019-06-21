#pragma once
#include "Player_State.h"
class Player_Special :public Player_State
{
public:
	Player_Special(Player* player);
	~Player_Special();
	enum special
	{
		chrji,
		Attackc
	};
	/// <summary>
	/// アップデート関数
	/// </summary>
	void Update();
private:
	void Attack();
	float m_scuea = 1.0f;
	bool m_sound = false;
	CSoundSource m_bgmA;									//BGM用のクラス
	special ka;
	Effekseer::Effect* m_sampleEffect = nullptr;			//エフェクトの実態のポインタ（？）
	Effekseer::Handle m_playEffectHandle;					//エフェクトのさすハンドル
};

