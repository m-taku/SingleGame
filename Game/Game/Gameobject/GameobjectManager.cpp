#include "stdafx.h"
#include "GameobjectManager.h"
#include"GameobjectList.h"
GameobjectManager::GameobjectManager()
{
	List.resize(20);
}
GameobjectManager::~GameobjectManager()
{
	for (auto& list : List) {
		for (auto objedct : list.GetList()) {
			delete objedct;
		}
	}
	List.clear();
}
void GameobjectManager::Execute()
{
	DeleteExecution();
	for (auto& list : List) {
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
	for (auto& list : List) {
		for (auto objedct : list.GetList()) {
			if (objedct->GetLodefrag()) {
				objedct->Draw();
			}
		}
	}
	for (auto& list : List) {
		for (auto objedct : list.GetList()) {
			if (objedct->GetLodefrag()) {
				objedct->postDraw();

			}
		}
	}
	NewExecution();
	/*static int count = 0;
	m_timeTotal += (float)m_sw.GetElapsed();
	count++;
	if (count == 30) {
		m_fps = 1.0f / (m_timeTotal / count);
		m_timeTotal = 0.0f;
		count = 0;

	}

	m_font->Begin(GraphicsEngine().GetRenderContext());
	wchar_t fps[256];
	swprintf_s(fps, L"FPS = %f", m_fps);
	float w = (float)GraphicsEngine().Get2DSpaceScreenWidth();
	float h = (float)GraphicsEngine().Get2DSpaceScreenHeight();
	m_font->Draw(
		fps,
		{
			w * -0.5f,
			h * 0.5f
		},
		CVector4::White,
		0.0f,															//ＦＰＳ表示、、、まだ（２Ｄからユウセン）
		1.0f,
		{ 0.0f, 1.0f }
	);
	m_font->End(GraphicsEngine().GetRenderContext());
#endif
	m_graphicsEngine.EndRender();

	m_sw.Stop();

	GameTime().PushFrameDeltaTime((float)m_sw.GetElapsed());
}*/
	int u = 0;
}
void GameobjectManager::DeleteExecution()
{
	auto nowNo = DeleteNo;
	DeleteNo = ++DeleteNo % 2;
	for (auto Deleteobject : DeleteList[nowNo]) {
		int no = Deleteobject.first->GetPriority();
		if (!List[no].DereteGo(Deleteobject.first, Deleteobject.second))
		{
			//クラッシュさせたい
			throw;
		}
	}
	DeleteList[DeleteNo].clear();
}
void GameobjectManager::NewExecution()
{
	for (auto Newobject : newLest)
	{
		List[Newobject.second].PushObject(Newobject.first);
	}
	newLest.clear();
}
bool GameobjectManager::DereteGO(Gameobject* pointa)
{
	int No = 0;
	for (auto kaa : List[pointa->GetPriority()].GetList())
	{
		if (kaa == pointa)
		{
			DeleteList[DeleteNo].insert(std::make_pair(pointa, No));
			return true;
		}
		No++;
	}
	return false;
}
bool GameobjectManager::DereteGO(char* Name)
{
	int No = 0;
	for (auto& ka : List) {
		for (auto kaa : ka.GetList()) {
			No = 0;
			if (Name == kaa->GetName()) {
				auto map = ka.GetList();
				DeleteList[DeleteNo].insert(std::make_pair(map[No], No));
				return true;
			}
			No++;
		}
	}
	return false;
}