#include "stdafx.h"
#include "Stage.h"
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
	//m_model.Init(L"Assets/modelData/stageGround.cmo",1);
	level.Init(L"Assets/level/stage_02.tkl",nullptr);
	Loadfrag = true;
	//Stege.CreateMeshObject(m_model, CVector3::Zero(), CQuaternion::Identity());
	navimake = objectManager->NewGO<Navimake>(0,"Navimake");
	return true;
}
void Stage::Update()
{
	//ワールド行列の更新。
	navimake->Up();
	m_model.UpdateWorldMatrix({ 0.0f,0.0f,0.0f }, CQuaternion::Identity(), CVector3::One());
}
void Stage::Draw()
{
	//m_model.Draw(
	//	g_camera3D.GetViewMatrix(),
	//	g_camera3D.GetProjectionMatrix()
	//);
	//level.Draw();
}
