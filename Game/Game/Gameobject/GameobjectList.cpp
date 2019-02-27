#include "stdafx.h"
#include "GameobjectList.h"
GameobjectList::GameobjectList()
{
}


GameobjectList::~GameobjectList()
{
}
bool GameobjectList::DereteGo(Gameobject* obj)
{
	//for (int i = 0; i < m_ObjectList.size(); i++) {
	//	if (m_ObjectList[no] == obj) {

	//		//delete obj;

	//		delete obj;
	//		m_ObjectList.erase(
	//			std::remove(m_ObjectList.begin(), m_ObjectList.end(), obj),
	//			m_ObjectList.end()
	//		);
	//		//m_Name.erase(
	//		//	m_Name.begin() + no
	//		//);
	//		return true;
	//	}
	//}
	for(int i = 0; i < m_ObjectList.size(); i++)
	{
		if (m_ObjectList[i] == obj)
		{
			delete obj;

			m_ObjectList.erase(
				std::remove(m_ObjectList.begin(), m_ObjectList.end(), obj),
				m_ObjectList.end()
			);
			return true;
		}
	}
	return false;
}
