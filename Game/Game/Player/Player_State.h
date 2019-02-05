#pragma once
class Player;
class Player_State :public Noncopyable
{
public:
	Player_State(Player* player);
	~Player_State();
	/// <summary>
	/// アップデート。
	/// </summary>
	virtual void Update() = 0;
	Player* m_player = nullptr;
};

