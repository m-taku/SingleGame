#include "stdafx.h"
#include "NPCStateHit.h"
#include "NPC.h"


NPCStateHit::NPCStateHit(NPC* enemy_point, const CVector3* pos) :NPCState(enemy_point, pos)
{

}


NPCStateHit::~NPCStateHit()
{
}
void NPCStateHit::Update()
{
	if (!m_npc->GetanimationPlaying()) {
		m_npc->TransitionState(NPC::State_Move);
	}
}
