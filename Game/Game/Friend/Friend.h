#pragma once

#include "NPC/NPC.h"
#include"Friendleader.h"
class Friend :public NPC
{
public:
	Friend();
	~Friend();
	bool FriendLoad();
	void FriendUpdete(); 
	void TransitionState(State m_state);
	/// <summary>
	/// 所属しているリーダーのセット。
	/// </summary>
	/// <param name="m_Leader">
	/// リーダーのインスタンス。（Enemyleader*）
	/// </param>
	void SetLeader(Friendleader* Leader)
	{
		m_Leader = Leader;
	}
private:
	Friendleader* m_Leader = nullptr;						//m_Leaderのポインタ

};

