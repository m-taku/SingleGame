#pragma once

#include "NPCState.h"
class NPCStateDesd :public  NPCState
{
public:
	NPCStateDesd(NPC* enemy_point, const CVector3* pos);
	~NPCStateDesd();
	/// <summary>
	/// EnemyState����p�������A�b�v�f�[�g�֐��B
	/// </summary>
	void Update() override;
};

