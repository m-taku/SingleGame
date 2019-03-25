#include "stdafx.h"
#include "Fade.h"


Fade::Fade()
{
	//フェード用のデータを読み込み
	m_texture_fade.CreateFromDDSTextureFromFile(L"Resource/sprite/White.dds");
	m_fadeSprite.Init(m_texture_fade.GetBody(), 1280.0f, 720.0f); 
	m_fadeSprite.SetclearColor(0.0f);
}


Fade::~Fade()
{
}
bool Fade::Update()
{
	m_fadeSprite.SetclearColor(m_toumei);
	m_toumei += m_faderate;
	//状態の遷移
	switch (m_fadestate)
	{
	case fadein:
		if (m_toumei >= 1.0f)
		{
			m_toumei = 1.0f;
			return true;
		}
		break;
	case fadeout:
		if (m_toumei <= 0.0f)
		{
			m_toumei = 0.0f;
			return true;
		}
		break;
	case idel:
		return false;
		break;
	default:
		break;
	}
	return false;
}
void Fade::Draw()
{
	m_fadeSprite.Draw(
		g_camera2D.GetViewMatrix(),
		g_camera2D.GetProjectionMatrix()
	);
}