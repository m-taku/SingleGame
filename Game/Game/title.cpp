#include "stdafx.h"
#include "title.h"
#include"Game.h"
#include"Stage.h"

title::title()
{
}


title::~title()
{
}
bool title::Load()
{
	m_texture.CreateFromDDSTextureFromFile(L"Resource/sprite/taitoru.dds");
	m_title_haikei.Init(&m_texture, 1280.0f, 720.0f);
	m_Texture.CreateFromDDSTextureFromFile(L"Resource/sprite/yellow.dds");
	m_title_moji.Init(&m_Texture, 1280.0f, 720.0f);
	m_texturea.CreateFromDDSTextureFromFile(L"Resource/sprite/White.dds");
	m_feid.Init(&m_texturea, 1280.0f, 720.0f);

	m_title_haikei.Updete(CVector3::Zero(), CQuaternion::Identity(), CVector3::One());
	m_title_moji.Updete(CVector3::Zero(), CQuaternion::Identity(), CVector3::One());
	return true;
}
void title::Update()
{
	m_title_haikei.Updete(CVector3::Zero(), CQuaternion::Identity(), CVector3::One());
	static float la = 0.0f;
	m_title_moji.Updete(CVector3::Zero(), CQuaternion::Identity(), { 1.0f,1.0f,1.0f });
	if (toumei >= 1.0f) {
		objectManager->NewGO<Game>(GameObjectPriority_Game);
		objectManager->NewGO<Stage>(0);
		objectManager->DereteGO(this);
	}
	m_feid.SetclearColor(toumei);
	toumei += la;
	if (g_pad[0].IsTrigger(enButtonA) )
	{
		la = 0.02f;
	}
	
}
void title::postDraw()
{

	m_title_moji.Draw(
		g_camera2D.GetViewMatrix(),
		g_camera2D.GetProjectionMatrix()
	);
	m_title_haikei.Draw(
		g_camera2D.GetViewMatrix(),
		g_camera2D.GetProjectionMatrix()
	);
	m_feid.Draw(
		g_camera2D.GetViewMatrix(),
		g_camera2D.GetProjectionMatrix()
	);
}
