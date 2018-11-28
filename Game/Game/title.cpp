#include "stdafx.h"
#include "title.h"
#include"Game.h"

title::title()
{
}


title::~title()
{
}
bool title::Load()
{
	m_texture_moji.CreateFromDDSTextureFromFile(L"Resource/sprite/taitoru.dds");
	m_title_haikei.Init(&m_texture_moji, 1280.0f, 720.0f);
	m_texture_haikei.CreateFromDDSTextureFromFile(L"Resource/sprite/yellow.dds");
	m_title_moji.Init(&m_texture_haikei, 1280.0f, 720.0f);
	m_texture_fade.CreateFromDDSTextureFromFile(L"Resource/sprite/White.dds");
	m_fadeSprite.Init(&m_texture_fade, 1280.0f, 720.0f);
	m_texture_yaji.CreateFromDDSTextureFromFile(L"Resource/sprite/yaji.dds");							//タイトルの矢印用のリソース
	m_yajiSprite.Init(&m_texture_yaji, 100.0f, 72.0f);									//タイトルの矢印用のインスタンス
	m_title_haikei.Updete(CVector3::Zero(), CQuaternion::Identity(), CVector3::One());
	m_title_moji.Updete(CVector3::Zero(), CQuaternion::Identity(), CVector3::One());
	m_yajiSprite.Updete(m_pos, CQuaternion::Identity(), CVector3::One());
	return true;
}
void title::Update()
{
	m_title_haikei.Updete(CVector3::Zero(), CQuaternion::Identity(), CVector3::One());
	m_title_moji.Updete(CVector3::Zero(), CQuaternion::Identity(), { 1.0f,1.0f,1.0f });
	if (m_toumei >= 1.0f) {
		g_objectManager->NewGO<Game>(GameObjectPriority_Game);
		m_title_moji.SetclearColor(0.0f);
		m_title_haikei.SetclearColor(0.0f);
		m_yajiSprite.SetclearColor(0.0f);
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
		m_toumei += m_faderate;
	}
	if (g_pad[0].IsPress(enButtonRight)&& moudo== test && m_toumei == 0.0f)
	{
		m_pos.x +=600.0f;
		moudo = sturt;
	}
	else
	{
		if (g_pad[0].IsPress(enButtonLeft) && moudo == sturt && m_toumei == 0.0f)
		{
			m_pos.x -= 600.0f; 
			moudo = test;
		}
	}
	m_yajiSprite.Updete(m_pos, CQuaternion::Identity(), CVector3::One());
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
	m_yajiSprite.Draw(
		g_camera2D.GetViewMatrix(),
		g_camera2D.GetProjectionMatrix()
	);
	m_fadeSprite.Draw(
		g_camera2D.GetViewMatrix(),
		g_camera2D.GetProjectionMatrix()
	);
}
