#include "stdafx.h"
#include "NPCStateDesd.h"
#include "NPC.h"


NPCStateDesd::NPCStateDesd(NPC* enemy_point, const CVector3* pos) :NPCState(enemy_point, pos)
{
}


NPCStateDesd::~NPCStateDesd()
{
}
void NPCStateDesd::Update()
{
	if (!m_npc->GetanimationPlaying())
	{
		m_npc->DeleteEnemy();
		m_npc->DeleteHitobj();
	}
}