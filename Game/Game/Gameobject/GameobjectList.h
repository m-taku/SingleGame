#pragma once
#include"Gameobject.h"
class GameobjectList
{
public:
	GameobjectList();
	~GameobjectList();
	template<class T>
	T* NewGo(int No,char* name)
	{
		T* object = new T;
		object->setpriority(No);
		ObjectList.push_back(object);
		Name.push_back(name);
		return object;
	}
	template<class T>
	T* NewGo(int No)
	{
		T* object = new T;
		object->setpriority(No);
		ObjectList.push_back(object);
		Name.push_back("NULL");
		return object;
	}	

	bool DereteGo(Gameobject* ka,int no);
	std::vector<Gameobject*> GetList()
	{
		return ObjectList;

	}
	std::vector<char*> GetName()
	{
		return Name;
	}
	/*char* Getname()
	{
		return *Name.begin();
	}*/
	private:
	int No = 0;
	std::vector<char*>  Name;
	std::vector<Gameobject*> ObjectList;
};

