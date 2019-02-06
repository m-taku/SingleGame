#include "stdafx.h"
#include "Gameover.h"
#include"title.h"


Gameover::Gameover()
{
}


Gameover::~Gameover()
{
}
bool Gameover::Load()
{
	m_texture_font.CreateFromDDSTextureFromFile(L"Resource/sprite/taitoru.dds");
	m_over_font.Init(m_texture_font.GetBody(), 1280.0f, 720.0f);
	m_over_font.Updete(m_pos, CQuaternion::Identity(), CVector3::One());

	return true;
}
void Gameover::Update()
{
	m_over_font.Updete(m_pos, CQuaternion::Identity(), CVector3::One());
	if (m_fade.GetState() == Fade::idel) {
		if (m_pos.y <= 0.0f)
		{
			m_fade.Fadein();
		}
		else
		{
			m_pos.y -= 20.0f;
		}
	}
	if (m_fade.Update())
	{
		switch (m_fade.GetState())
		{
		case Fade::fadein:	
			g_objectManager->DereteGO("Game");
			g_objectManager->NewGO<title>(0, "title");
			m_over_font.SetclearColor(0.0f);
			m_fade.Fadeout(50.0f);
			break;
		case Fade::fadeout:
			g_objectManager->DereteGO(this);
			break;
		default:
			break;
		}
	}

}
void Gameover::PostDraw()
{
	m_over_font.Draw(
		g_camera2D.GetViewMatrix(),
		g_camera2D.GetProjectionMatrix()
	);
	m_fade.Draw();

}
