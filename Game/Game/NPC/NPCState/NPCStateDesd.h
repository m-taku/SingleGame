#pragma once

#include "NPCState.h"
class NPCStateDesd :public  NPCState
{
public:
	NPCStateDesd(NPC* enemy_point, const CVector3* pos);
	~NPCStateDesd();
	/// <summary>
	/// EnemyStateから継承したアップデート関数。
	/// </summary>
	void Update() override;
};

