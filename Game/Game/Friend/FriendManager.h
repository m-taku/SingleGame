#pragma once
#include "Friendleader.h"
class FriendManager :public Gameobject
{
public:
	FriendManager();
	~FriendManager();	
	/// <summary>
	/// Gameobject����p�������ŏ��ɌĂ΂��֐��B
	/// </summary>
	/// <returns>
	/// Load������true�A���s��false�B
	/// </returns>
	bool Load() override;
	/// <summary>
	/// GemeObject����p������Update�֐��B
	/// </summary>
	void Update() override;	
	/// <summary>
	/// 
	/// </summary>
	/// <param name="score"></param>
	void SetScore(Score* score)
	{
		m_Score = score;
	}
	void SpawnFriend(CVector3 pos, Ability* k);
private:
	std::vector<Friendleader*> m_Friend;
	int m_No = 0;
	int m_count = 0;
	int m_Maxsporn = 10;
	Score* m_Score = nullptr;
};

