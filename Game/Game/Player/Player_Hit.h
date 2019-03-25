#pragma once
#include"Player_State.h"
class Player_Hit :public Player_State
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="player">
	///プレイヤーのポインタ。（Player*）
	/// </param>
	Player_Hit(Player* player);
	/// <summary>
	/// デストラクタ
	/// </summary>
	~Player_Hit();
	/// <summary>
	/// アップデート関数
	/// </summary>
	void Update();
	
};

