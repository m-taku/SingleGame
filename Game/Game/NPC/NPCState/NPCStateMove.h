#pragma once
#include "NPCState.h"
class NPCStateMove :public NPCState
{
public:
	NPCStateMove(NPC* enemy_point, const CVector3* pos);
	~NPCStateMove();
	/// <summary>
	/// EnemyStateから継承したアップデート関数。
	/// </summary>
	void Update();
private:
	Path * m_path = nullptr;										//経路探査のインスタンス
	CVector3 m_oldposition = CVector3::Zero();					//1フレーム前のポジション（壁擦りなどの判定などなど）
	CVector3 m_nextpos = CVector3::Zero();						//経路探査で出た次のポジション
	int m_fream = 0;
};



