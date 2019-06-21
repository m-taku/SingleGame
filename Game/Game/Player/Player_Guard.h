#pragma once
#include "Player_State.h"
class Player_Guard :public Player_State
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="player">
	///プレイヤーのポインタ。（Player*）
	/// </param>
	Player_Guard(Player* player);
	/// <summary>
	/// デストラクタ
	/// </summary>
	~Player_Guard();
	/// <summary>
	/// アップデート関数
	/// </summary>
	void Update();
private:
	Effekseer::Effect* m_sampleEffect = nullptr;			//エフェクトの実態のポインタ（？）
	Effekseer::Handle m_playEffectHandle;					//エフェクトのさすハンドル
};

