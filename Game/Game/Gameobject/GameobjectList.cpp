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
	if (ObjectList[no] == obj) {
		ObjectList.erase(
			std::remove(ObjectList.begin(), ObjectList.end(), ObjectList[no]),
			ObjectList.end()
		);
		delete obj;
		Name.erase(
			Name.begin() + no
		);
		return true;
	}
	return false;
}
//////////�������ɏ����Ă݂��B�B�B�B�����Ȃ�
//template<typedef T>
//T* GameobjectList::NewGo(/*char* name*/)
//{
//	T* object = new T;
//	ObjectList.push_back(object);
//	//Name.push_back(name);
//	return object;
//}