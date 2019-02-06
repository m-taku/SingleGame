#include "stdafx.h"
#include "UI.h"

namespace {
	//HPBar�̃T�C�Y
	const CVector2 Hpbarsize = { 1000.0f, 250.0f };
}

UI::UI()
{

}


UI::~UI()
{

}
bool UI::Load()
{
	m_Texture_bar_waku.CreateFromDDSTextureFromFile(L"Resource/sprite/HP_Player_waku.dds");
	m_HP_bar_waku.Init(m_Texture_bar_waku.GetBody(), Hpbarsize.x, Hpbarsize.y);
	m_Texture_bar.CreateFromDDSTextureFromFile(L"Resource/sprite/HP_Player.dds");
	m_HP_bar.Init(m_Texture_bar.GetBody(), Hpbarsize.x, Hpbarsize.y);
	m_HP_bar_waku.Updete(m_HP_waku_position, CQuaternion::Identity(), CVector3::One(), {0.0f,1.0f});
	m_HP_bar.Updete(m_HP_position, CQuaternion::Identity(), CVector3::One(), { 0.0f,1.0f });
	return true;
}
void UI::Update()
{
	m_HP_bar_waku.Updete(m_HP_waku_position, CQuaternion::Identity(), CVector3::One(), { 0.0f,1.0f });
	m_HP_bar.Updete(m_HP_position, CQuaternion::Identity(),{m_HP- m_Damage,1.0f,1.0f}, { 0.0f,1.0f });
}
void UI::PostDraw()
{	
	m_HP_bar_waku.Draw(
		g_camera2D.GetViewMatrix(),
		g_camera2D.GetProjectionMatrix()
	);
	m_HP_bar.Draw(
		g_camera2D.GetViewMatrix(),
		g_camera2D.GetProjectionMatrix()
	);
	m_font.BeginDraw();	//�t�H���g�̕`��J�n�B
	static Color color;
	static int fream = 0;
	wchar_t toubatu[256];
	swprintf_s(toubatu, L"%d�����I�I", fream);//�X�e�[�W�B
	if (g_pad[0].IsPress(enButtonY)) {
		fream++;
	}
	auto Col = color.HSVtoRGB();
	m_font.Draw(
		toubatu,		//�\�����镶����B
		{ 500.0f,-300.0f },			//�\��������W�B0.0f, 0.0����ʂ̒��S�B
		Col,//{ 0.0f,0.0f,0.0f,1.0f },
		0.0f,
		3.0f
	);
	m_font.EndDraw();		//�t�H���g�̕`��I���B
}
void UI::Draw()
{

}