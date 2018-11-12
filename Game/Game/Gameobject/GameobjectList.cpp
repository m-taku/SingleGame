#include "stdafx.h"
#include "GameobjectList.h"
GameobjectList::GameobjectList()
{
}


GameobjectList::~GameobjectList()
{
}
bool GameobjectList::DereteGo(Gameobject* obj, int no)
{
	if (m_ObjectList[no] == obj) {

		//delete obj;
		m_ObjectList.erase(
			std::remove(m_ObjectList.begin(), m_ObjectList.end(), obj),
			m_ObjectList.end()
		);
		delete obj;
		m_Name.erase(
			m_Name.begin() + no
		);
		return true;
	}
	return false;
}
//////////ｃｐｐに書いてみた。。。。動かない
//template<typedef T>
//T* GameobjectList::NewGo(/*char* name*/)
//{
//	T* object = new T;
//	ObjectList.push_back(object);
//	//Name.push_back(name);
//	return object;
//}