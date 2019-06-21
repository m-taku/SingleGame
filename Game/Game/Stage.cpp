#include "stdafx.h"
#include "Stage.h"
#include"level/MapChip.h"
#include "title.h"

Stage::Stage()
{

}


Stage::~Stage()
{

}
void Stage::OnDestroy()
{
	g_objectManager->DereteGO(m_navimake);
}
bool Stage::Load()
{
	auto mode=g_objectManager->FindGO<title>("title");
	wchar_t moveFilePath[256];
	//タイトルからモードを取得
	switch (mode->GetMode())
	{
	case title::sturt:
		//sturtモード用のデータを読み込み
		swprintf_s(moveFilePath, L"Assets/level/stage_0%d.tkl", 8);
		//m_bgmA.Init(L"Assets/sound/bgm.wav");
		//m_bgmA.Play(true);
		break;
	case title::test:
		//testモード用のデータを読み込み
		swprintf_s(moveFilePath, L"Assets/level/stage_0%d.tkl", 5);

		break;
	default:
		break;
	}		
	m_bgmA.Init(L"Assets/sound/bgm.wav");
	//m_bgmA.Play(true);
	//ステージのレベル
	m_level.Init(moveFilePath, nullptr);
	//地面のみのセル（ポリゴン）を生成する
	//（地面のモデルはこちらでやってください）
	m_navimake = g_objectManager->NewGO<Navimake>(0, "Navimake");
	return true;
}
void Stage::Update()
{
	m_level.Update();
}
void Stage::Draw()
{
	m_level.Draw();
}
void Stage::PostDraw()
{

}
