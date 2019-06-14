#pragma once
class NPC;
class NPCState:public Noncopyable
{
public:
	NPCState(NPC* enemy_point, const CVector3* pos);
	virtual ~NPCState();
	/// <summary>
	/// �A�b�v�f�[�g�B
	/// </summary>
	virtual void Update() = 0;
	CVector3 GetTarget3DPosition()
	{
		return *m_targetposition;
	}
	CVector3 GetTarget2DPosition()
	{
		auto pos = *m_targetposition;
		pos.y = 0;
		return pos;
	}
protected:
	NPC * m_npc = nullptr;			//�G�l�~�[�̃C���X�^���X
	const CVector3* m_targetposition = nullptr;
};

