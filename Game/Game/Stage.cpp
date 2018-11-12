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
	//cmoファイルの読み込み。
    // m_model.Init(L"Assets/modelData/wall--.cmo");
	//ステージのレベル
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
	//地面のみのセル（ポリゴン）を生成する（地面のモデルはこちらから）
	m_navimake = objectManager->NewGO<Navimake>(0,"Navimake");
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
void Stage::postDraw()
{
	m_font.Begin();	//フォントの描画開始。
	m_font.Draw(
		L"こんにちは世界",		//表示する文字列。
		{0.0f,100.0f},			//表示する座標。0.0f, 0.0が画面の中心。
		CVector4::White()
	);
	m_font.end();		//フォントの描画終了。
}
