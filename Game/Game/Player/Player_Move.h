#pragma once
#include "Player_State.h"
class Player_Move :public Player_State
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="player">
	///プレイヤーのポインタ。（Player*）
	/// </param>
	Player_Move(Player* player);
	/// <summary>
	/// デストラクタ
	/// </summary>
	~Player_Move();
	/// <summary>
	/// アップデート関数
	/// </summary>
	void Update();
private:
};

