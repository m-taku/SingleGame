#include "stdafx.h"
#include "GameobjectManager.h"
#include"GameobjectList.h"
#include "ShadowMap.h"


GameobjectManager::GameobjectManager()
{
}
GameobjectManager::~GameobjectManager()
{
	Release();
}
void GameobjectManager::Release()
{
	for (auto& list : m_List) {
		auto List = list.GetList();
		for (auto& objedct : List) {
			delete objedct;
		}
	}
}
void GameobjectManager::Execute()
{

	for (auto& list : m_List) {
		for (auto& objedct : list.GetList())
		{
			if (objedct->Getislife()) {
				if (objedct->GetLodefrag()) {
					objedct->Update();
				}
				else {
					if (objedct->Load())
						objedct->SetLoadfrag(true);
				}
			}
		}
	}

	//ここからレンダー系の処理を書く
	//g_graphicsEngine->GetShadowMap()->UpdateFromLightTarget(
	//	{ -0.707f,0.707f,0.0f },
	//	{ 0.0f, 0.0f, 0.0f }
	//);
	g_graphicsEngine->shadoUpdate();

	for (auto& list : m_List) {
		for (auto objedct : list.GetList()) {
			if (objedct->GetLodefrag()&& objedct->Getislife()) {
				objedct->Draw();
			}
		}
	}
	//デバック用の剛体表示
	g_graphicsEngine->PostEffectUpdate();
#ifdef _DEBUG
//
	//g_physics.DebubDrawWorld();
#endif

	for (auto& list : m_List) {
		for (auto objedct : list.GetList()) {
			if (objedct->GetLodefrag() && objedct->Getislife()) {
				objedct->PostDraw();
			}
		}
	}
	DeleteExecution();
	NewExecution();

}
void GameobjectManager::DeleteExecution()
{
	auto nowNo = m_DeleteNo;
	m_DeleteNo = ++m_DeleteNo % 2;
	for (auto Deleteobject : m_DeleteList[nowNo]) {
		int no = Deleteobject->GetPriority();
		if (!m_List[no].DereteGo(Deleteobject))
		{
			//クラッシュさせたい
			throw;
		}
	}
	m_DeleteList[nowNo].clear(); //erase(m_DeleteList[m_DeleteNo].begin(), m_DeleteList[m_DeleteNo].end());
}
void GameobjectManager::NewExecution()
{
	for (auto Newobject : m_newLest)
	{
		m_List[Newobject.second].PushObject(Newobject.first);
	}
	m_newLest.clear();
}
bool GameobjectManager::DereteGO(Gameobject* pointa)
{
	for (auto objedct : m_List[pointa->GetPriority()].GetList())
	{
		if (objedct == pointa)
		{
			m_DeleteList[m_DeleteNo].push_back(pointa);
			pointa->deleteobjiect();
			return true;
		}
	}
	return false;
}
bool GameobjectManager::DereteGO(char* Name)
{
	int No = 0;
	for (auto& list : m_List) {
		for (auto objedct : list.GetList()){
			if (Name == objedct->GetName()){
				auto map = list.GetList();
				m_DeleteList[m_DeleteNo].push_back(map[No]);
				map[No]->deleteobjiect();
				return true;
			}
		}
	}
	return false;
}