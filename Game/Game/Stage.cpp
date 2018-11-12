#include "stdafx.h"
#include "Stage.h"
#include"Monn.h"
#include"level/MapChip.h"


Stage::Stage()
{
}


Stage::~Stage()
{
}
bool Stage::Load()
{
	//cmo�t�@�C���̓ǂݍ��݁B
    // m_model.Init(L"Assets/modelData/wall--.cmo");
	//�X�e�[�W�̃��x��
	m_level.Init(L"Assets/level/stage_05.tkl", [&](LevelObjectData objData)
	{
		auto No = wcscmp(objData.name, (L"monn1"));
		if (No==0)
		{
			auto monn = objectManager->NewGO<Monn>(0, "Monn");
			monn->SetPosition(objData.position);
			monn->Setrotation(objData.rotation);
			monn->Setkaku();
			return true;
		}
		auto No1 = wcscmp(objData.name, (L"monn2"));
		if (No1 == 0)
		{
			auto monn = objectManager->NewGO<Monn>(0, "Monn");
			monn->SetPosition(objData.position);
			monn->Setrotation(objData.rotation);
			return true;
		}
		return false;
	});
	//Stege.CreateMeshObject(m_model, CVector3::Zero(), CQuaternion::Identity());
	//�n�ʂ݂̂̃Z���i�|���S���j�𐶐�����i�n�ʂ̃��f���͂����炩��j
	m_navimake = objectManager->NewGO<Navimake>(0,"Navimake");
	//Loadfrag = true;
	return true;
}
void Stage::Update()
{
	//���[���h�s��̍X�V�B
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
void Stage::postDraw()
{
	m_font.Begin();	//�t�H���g�̕`��J�n�B
	m_font.Draw(
		L"����ɂ��͐��E",		//�\�����镶����B
		{0.0f,100.0f},			//�\��������W�B0.0f, 0.0����ʂ̒��S�B
		CVector4::White()
	);
	m_font.end();		//�t�H���g�̕`��I���B
}
