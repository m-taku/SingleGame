#include "stdafx.h"
#include "Stage.h"
#include"Monn.h"
#include"level/MapChip.h"


Stage::Stage()
{
	int ka = 0;
	ka++;
}


Stage::~Stage()
{
}
bool Stage::Load()
{
	//cmoファイルの読み込み。
  //  m_model.Init(L"Assets/modelData/wall--.cmo");
	level.Init(L"Assets/level/stage_05.tkl", [&](LevelObjectData objData)
	{
		auto No = wcscmp(objData.name, (L"monn1"));
		if (No==0)
		{
			auto monn = objectManager->NewGO<Monn>(0, "Monn");
			monn->Setposition(objData.position);
			monn->Setrotation(objData.rotation);
			monn->Setkaku();
			return true;
		}
		auto No1 = wcscmp(objData.name, (L"monn2"));
		if (No1 == 0)
		{
			auto monn = objectManager->NewGO<Monn>(0, "Monn");
			monn->Setposition(objData.position);
			monn->Setrotation(objData.rotation);
			return true;
		}
		return false;
	});
	//Stege.CreateMeshObject(m_model, CVector3::Zero(), CQuaternion::Identity());
	navimake = objectManager->NewGO<Navimake>(0,"Navimake");
	Loadfrag = true;
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
	navimake->Up();
	level.Draw();
}
