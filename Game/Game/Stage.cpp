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
	//cmo�t�@�C���̓ǂݍ��݁B
    m_model.Init(L"Assets/modelData/jimennabi2.cmo");
	level.Init(L"Assets/level/stage_01.tkl",nullptr);
	navimake = objectManager->NewGO<Navimake>(0,"Navimake");
	Loadfrag = true;
	Stege.CreateMeshObject(m_model, CVector3::Zero(), CQuaternion::Identity());
	return true;
}
void Stage::Update()
{
	//���[���h�s��̍X�V�B
	//navimake->Up();
	m_model.UpdateWorldMatrix({ 0.0f,-10.0f,0.0f }, CQuaternion::Identity(), CVector3::One());
}
void Stage::Draw()
{
	m_model.Draw(
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix()
	);
	//navimake->Up();
	level.Draw();
}
