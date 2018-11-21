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
	m_fadeSprite.Init(&m_texturea, 1280.0f, 720.0f);
	m_title_haikei.Updete(CVector3::Zero(), CQuaternion::Identity(), CVector3::One());
	m_title_moji.Updete(CVector3::Zero(), CQuaternion::Identity(), CVector3::One());
	return true;
}
void title::Update()
{
	m_title_haikei.Updete(CVector3::Zero(), CQuaternion::Identity(), CVector3::One());
	m_title_moji.Updete(CVector3::Zero(), CQuaternion::Identity(), { 1.0f,1.0f,1.0f });
	if (m_toumei >= 1.0f) {
		g_objectManager->NewGO<Game>(GameObjectPriority_Game);
		g_objectManager->NewGO<Stage>(0);
		m_title_moji.SetclearColor(0.0f);
		m_title_haikei.SetclearColor(0.0f);
		m_faderate *= -1;
	}
	if (m_toumei < 0.0f)
	{
		g_objectManager->DereteGO(this);
	}
	m_fadeSprite.SetclearColor(m_toumei);
	m_toumei += m_faderate;
	if (g_pad[0].IsTrigger(enButtonA)&& m_toumei==0.0f)
	{
		m_faderate = 0.02f;
	}
	
}
void title::PostDraw()
{
	m_title_moji.Draw(
		g_camera2D.GetViewMatrix(),
		g_camera2D.GetProjectionMatrix()
	);
	m_title_haikei.Draw(
		g_camera2D.GetViewMatrix(),
		g_camera2D.GetProjectionMatrix()
	);
	m_fadeSprite.Draw(
		g_camera2D.GetViewMatrix(),
		g_camera2D.GetProjectionMatrix()
	);
}
