#pragma once
#include "Friendleader.h"
class FriendManager :public Gameobject
{
public:
	FriendManager();
	~FriendManager();	
	/// <summary>
	/// Gameobjectから継承した最初に呼ばれる関数。
	/// </summary>
	/// <returns>
	/// Load成功でtrue、失敗でfalse。
	/// </returns>
	bool Load() override;
	/// <summary>
	/// GemeObjectから継承したUpdate関数。
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
	void SpawnFriend(CVector3 pos, Ability* ability);
private:
	std::vector<Friendleader*> m_Friend;
	int m_No = 0;
	int m_count = 0;
	int m_Maxsporn = 10;
	Score* m_Score = nullptr;
};

