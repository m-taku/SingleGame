#include "stdafx.h"
#include "Friend.h"
#include"Enenystate.h"
#include"NPCStateFile.h"
//�����ōl���鏈��

Friend::Friend()
{
}


Friend::~Friend()
{
}
bool Friend::FriendLoad()
{
	Load();
	CopyModel();
	return true;
}
void Friend::FriendUpdete()
{
	Update();
}
void Friend::TransitionState(State m_state)
{
	delete m_enemystate;
	//�����ŖڕW�v�Z�i�D��x������悤�j
	switch (m_state)
	{
	case State_Move:
		m_enemystate = new NPCStateMove(this, &CVector3::Zero());
		break;
	case State_Attack:
		m_enemystate = new NPCStateAttack(this, &CVector3::Zero());
		break;
	//	//case State_Gathering:
	//	//	m_enemystate = new EnemyStategathering(this, &m_player->Get3DPosition());
	//	//	break;
	case State_Hit:
		m_enemystate = new NPCStateHit(this, &CVector3::Zero());
		break;
	case State_Dead:
		m_enemystate = new NPCStateDesd(this, &CVector3::Zero());
		break;
	default:
		break;
	}
}