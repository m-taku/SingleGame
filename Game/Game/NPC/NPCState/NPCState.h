#pragma once
class NPC;
class NPCState:public Noncopyable
{
public:
	NPCState(NPC* enemy_point, const CVector3* pos);
	virtual ~NPCState();
	/// <summary>
	/// アップデート。
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
	NPC * m_npc = nullptr;			//エネミーのインスタンス
	const CVector3* m_targetposition = nullptr;
};

