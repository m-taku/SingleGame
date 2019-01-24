#include "stdafx.h"
#include "HitReceive.h"


HitReceive::HitReceive()
{
}


HitReceive::~HitReceive()
{
}

void HitReceive::Create(const CVector3* pos, float radius, std::function<void()>  objict, objict_Name name)
{
	m_pos = pos;
	m_radius = radius;
	m_fuk = objict;
	m_name = name;
}
bool HitReceive::HitTest(CVector3 pos)
{
	auto rengs=*m_pos - pos;
	//円形で判定（aabb等に変更する可能性あり）
	if (rengs.Length() <= m_radius)
	{

		m_fuk();
		//switch (m_name)
		//{
		//case HitReceive::enemy:
		//	m_objict;
		//	break;
		//case HitReceive::player:
		//	((Player*)m_objict)->Hit();
		//	break;
		//default:
		//	break;
		//}
		//return true;
	}
	return false;
}