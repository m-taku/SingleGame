#include "stdafx.h"
#include "NPCState.h"
#include "NPC.h"


NPCState::NPCState(NPC* enemy_point, const CVector3* pos)
{
	m_npc = enemy_point;
	m_targetposition = pos;
}


NPCState::~NPCState()
{
}
