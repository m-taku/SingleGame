#pragma once
#include"GameobjectList.h"
class GameobjectManager
{
public:
	GameobjectManager();
	~GameobjectManager();
	void DeleteExecution();
	void Execute();
	template<class T>
	T* NewGO(int No , char* name)
	{
		return List.at(No).NewGo<T>(No,name);
	}
	template<class T>
	T* NewGO(int No)
	{
		return List.at(No).NewGo<T>(No);
	}
	
	// list.DereteGo(pointa)
	bool DereteGO(Gameobject* pointa);
	//{
	//	No = 0;
	//	for (auto kaa : List[pointa->Getpriority()].GetList())
	//	{
	//		if (kaa == pointa)
	//		{
	//			DeleteList[DeleteNo].insert(std::make_pair(pointa, No));
	//			return true;
	//		}
	//		No++;
	//	}
	//	return false;
	//}
	bool DereteGO(char* Name);
	//{
	//	for (auto ka : List) {
	//		No = 0;
	//		for (auto kaa : ka.GetName()) {
	//			if (Name == kaa) {
	//				auto map=ka.GetList();
	//				DeleteList[DeleteNo].insert(std::make_pair(map[No],No));
	//				return true;
	//			}
	//			No++;
	//		}
	//	}
	//	return false;
	//}
private:
	int No = 0;
	int DeleteNo = 0;

	//std::list<Gameobject*> List2;
	//std::vector<std::list<Gameobject*>> List2;

	std::vector<GameobjectList> List;
	std::map<Gameobject*, int> DeleteList[2];
};

