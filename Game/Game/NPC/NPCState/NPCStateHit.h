#pragma once

#include "NPCState.h"
class NPCStateHit :public  NPCState
{
public:
	NPCStateHit(NPC* enemy_point, const CVector3* pos);
	~NPCStateHit();
	void Update() override;
};

