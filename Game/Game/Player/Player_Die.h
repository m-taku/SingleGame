#pragma once
#include"Player_State.h"
class Player_Die :public Player_State
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="player">
	///プレイヤーのポインタ。（Player*）
	/// </param>
	Player_Die(Player* player);
	/// <summary>
	/// デストラクタ
	/// </summary>
	~Player_Die();
	/// <summary>
	/// アップデート
	/// </summary>
	void Update();
private:
	bool m_die = true;				//死亡診断フラグ
};

