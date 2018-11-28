#include "stdafx.h"
#include "Stage.h"
#include"Monn.h"
#include"level/MapChip.h"
#include "title.h"

Stage::Stage()
{
}


Stage::~Stage()
{
}
bool Stage::Load()
{
	//cmoファイルの読み込み。
    // m_model.Init(L"Assets/modelData/wall--.cmo");
	//ステージのレベル
	auto mode=g_objectManager->FindGO<title>("title");
	wchar_t moveFilePath[256];
	swprintf_s(moveFilePath, L"Assets/level/stage_0%d.tkl",mode->Getmode()+4);
	m_level.Init(moveFilePath, [&](LevelObjectData objData)
	{
		auto No = wcscmp(objData.name, (L"monn1"));
		if (No==0)
		{
			auto monn = g_objectManager->NewGO<Monn>(0, GameObjectName_Monn);
			monn->SetPosition(objData.position);
			monn->Setrotation(objData.rotation);
			monn->Setkaku();
			return true;
		}
		auto No1 = wcscmp(objData.name, (L"monn2"));
		if (No1 == 0)
		{
			auto monn = g_objectManager->NewGO<Monn>(0, GameObjectName_Monn);
			monn->SetPosition(objData.position);
			monn->Setrotation(objData.rotation);
			return true;
		}
		return false;
	});
	//Stege.CreateMeshObject(m_model, CVector3::Zero(), CQuaternion::Identity());
	//地面のみのセル（ポリゴン）を生成する（地面のモデルはこちらから）
	m_navimake = g_objectManager->NewGO<Navimake>(0,"Navimake");
	//Loadfrag = true;
	return true;
}
void Stage::Update()
{
	//ワールド行列の更新。
	//m_model.UpdateWorldMatrix({ 0.0f,10.0f,0.0f }, CQuaternion::Identity(), CVector3::One());
}
void Stage::Draw()
{
	//m_model.Draw(
	//	g_camera3D.GetViewMatrix(),
	//	g_camera3D.GetProjectionMatrix()
	//);
	//

	m_navimake->Update();
	m_level.Draw();
}
void Stage::PostDraw()
{

}
