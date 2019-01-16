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
			if (objedct->GetLodefrag()) {
				objedct->Update();
			}
			else {
				if (objedct->Load())
					objedct->SetLoadfrag(true);
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
			if (objedct->GetLodefrag()) {
				objedct->Draw();
			}
		}
	}
	//デバック用の剛体表示
	g_graphicsEngine->PostEffectUpdate();
#ifdef _DEBUG
	//g_physics.DebubDrawWorld();
#endif

	for (auto& list : m_List) {
		for (auto objedct : list.GetList()) {
			if (objedct->GetLodefrag()) {
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
		int no = Deleteobject.first->GetPriority();
		Deleteobject.first->OnDestroy();
		if (!m_List[no].DereteGo(Deleteobject.first, Deleteobject.second))
		{
			//クラッシュさせたい
			throw;
		}
	}
	m_DeleteList[m_DeleteNo].clear();
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
	int No = 0;
	for (auto objedct : m_List[pointa->GetPriority()].GetList())
	{
		if (objedct == pointa)
		{
			m_DeleteList[m_DeleteNo].insert(std::make_pair(pointa, No));
			return true;
		}
		No++;
	}
	return false;
}
bool GameobjectManager::DereteGO(char* Name)
{
	int No = 0;
	for (auto& list : m_List) {
		for (auto objedct : list.GetList()) {
			No = 0;
			if (Name == objedct->GetName()) {
				auto map = list.GetList();
				m_DeleteList[m_DeleteNo].insert(std::make_pair(map[No], No));
				return true;
			}
			No++;
		}
	}
	return false;
}