#pragma once

#include "NPC/NPC.h"
#include"Friendleader.h"
class Friend :public NPC
{
public:
	Friend();
	~Friend();
	bool FriendLoad();
	void FriendUpdete(); 
	void TransitionState(State m_state);
	/// <summary>
	/// �������Ă��郊�[�_�[�̃Z�b�g�B
	/// </summary>
	/// <param name="m_Leader">
	/// ���[�_�[�̃C���X�^���X�B�iEnemyleader*�j
	/// </param>
	void SetLeader(Friendleader* Leader)
	{
		m_Leader = Leader;
	}
private:
	Friendleader* m_Leader = nullptr;						//m_Leader�̃|�C���^

};

