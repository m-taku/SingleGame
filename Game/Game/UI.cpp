#include "stdafx.h"
#include "UI.h"
#include"Gameover.h"

namespace {
	//HPBar�̃T�C�Y
	const CVector2 Hpbarsize = { 1000.0f, 250.0f };
	const CVector2 Statussize = { 100.0f,100.0f };
	const int GAMETAIM = 3;			//��������

}

UI::UI()
{
}


UI::~UI()
{

}
bool UI::Load()
{
	m_bgmA.Init(L"Assets/sound/shakin1.wav");
	//�v���C���[��HP�p�̃f�[�^�����[�h
	m_Texture_bar_waku.CreateFromDDSTextureFromFile(L"Resource/sprite/HP_Player_waku.dds");
	m_HP_bar_waku.Init(m_Texture_bar_waku.GetBody(), Hpbarsize.x, Hpbarsize.y);
	m_HP_bar_waku.Updete(m_HP_waku_position, CQuaternion::Identity(), CVector3::One(), {0.0f,1.0f});
	//�v���C���[��HP�g�p�̃f�[�^�����[�h
	m_Texture_bar.CreateFromDDSTextureFromFile(L"Resource/sprite/HP_Player.dds");
	m_HP_bar.Init(
		m_Texture_bar.GetBody(), 
		Hpbarsize.x,
		Hpbarsize.y
	);
	m_HP_bar.Updete(m_HP_position, CQuaternion::Identity(), CVector3::One(), { 0.0f,1.0f });
	//�v���C���[��MP�p�̃f�[�^�����[�h
	m_Texture_bar_waku_MP.CreateFromDDSTextureFromFile(L"Resource/sprite/MP_Player_waku.dds");
	m_MP_bar_waku.Init(m_Texture_bar_waku_MP.GetBody(), Hpbarsize.x*0.8f, Hpbarsize.y/6.0f);
	m_MP_bar_waku.Updete(m_MP_waku_position, CQuaternion::Identity(), { 1.0f,1.0f,1.0f }, { 0.0f,1.0f });
	//�v���C���[��MP�g�p�̃f�[�^�����[�h
	m_Texture_bar_MP.CreateFromDDSTextureFromFile(L"Resource/sprite/MP_Player.dds");
	m_MP_bar.Init(
		m_Texture_bar_MP.GetBody(),
		Hpbarsize.x*0.79,
		Hpbarsize.y/6.0f
	);
	m_MP_bar.Updete(m_MP_position, CQuaternion::Identity(), { 1.0,0.9f,1.0f }, { 0.0f,1.0f });
	m_MP_bar.SetMulColor({ 0.0,0.0,1.0,1.0 });
	//
	m_texture_status_bar.CreateFromDDSTextureFromFile(L"Resource/sprite/status_waku.dds");
	m_status_bar.Init(m_texture_status_bar.GetBody(), Statussize.x*3, Statussize.y);
	m_status_bar.Updete(m_status_bar_position, CQuaternion::Identity(), CVector3::One() ,{0.0f,0.5f});

	//
	m_texture_status[attakc1].CreateFromDDSTextureFromFile(L"Resource/sprite/attakc_icon.dds");
	m_status[attakc1].Init(m_texture_status[attakc1].GetBody(), Statussize.x, Statussize.y);
	m_status[attakc1].Updete(m_status_position[attakc1], CQuaternion::Identity(), CVector3::One());
	m_status[attakc1].SetclearColor(0.5f);
	//
	m_texture_status[defense1].CreateFromDDSTextureFromFile(L"Resource/sprite/defensu_icon.dds");
	m_status[defense1].Init(m_texture_status[defense1].GetBody(), Statussize.x, Statussize.y);
	m_status[defense1].Updete(m_status_position[defense1], CQuaternion::Identity(), CVector3::One());
	m_status[defense1].SetclearColor(0.5f);
	//
	m_texture_status[speed1].CreateFromDDSTextureFromFile(L"Resource/sprite/speed_icon.dds");
	m_status[speed1].Init(m_texture_status[speed1].GetBody(), Statussize.x, Statussize.y);
	m_status[speed1].Updete(m_status_position[speed1], CQuaternion::Identity(), CVector3::One());
	m_status[speed1].SetclearColor(0.5f);
	//�������Ԃ̃^�C�}�[�̃X�^�[�g
	//m_timer.TimerStart();
	return true;
}
void UI::Update()
{
	//HP�̑J�ڗp�Ƀe�N�X�`�����X�V
	m_HP_bar_waku.Updete(m_HP_waku_position, CQuaternion::Identity(), CVector3::One(), { 0.0f,1.0f });
	m_HP_bar.Updete(m_HP_position, CQuaternion::Identity(),{m_HP- m_Damage,1.0f,1.0f}, { 0.0f,1.0f });
	m_MP_bar.Updete(m_MP_position, CQuaternion::Identity(), { m_MP,0.9f,1.0f }, { 0.0f,1.0f });
	m_status_bar.Updete(m_status_bar_position, CQuaternion::Identity(), CVector3::One());
	for (int i = 0; i < num; i++) {
		m_status[i].Updete(m_status_position[i], CQuaternion::Identity(), CVector3::One());
	}

}
void UI::PostDraw()
{
	//�v���C���[��HP�p�̃X�v���C�g��Draw
	m_HP_bar_waku.Draw(
		g_camera2D.GetViewMatrix(),
		g_camera2D.GetProjectionMatrix()
	);
	m_HP_bar.Draw(
		g_camera2D.GetViewMatrix(),
		g_camera2D.GetProjectionMatrix()
	);
	m_MP_bar_waku.Draw(
		g_camera2D.GetViewMatrix(),
		g_camera2D.GetProjectionMatrix()
	);
	CVector4 Col;
	if (m_MP >= 1.0f) {
		Col = m_Color_Mp.HSVtoRGB();
		if (m_bool) {
			m_bgmA.Play(false);
			m_bool = false;
		}
	}
	else
	{
		m_Color_Mp.SetHSV(230.0f / 360.0f);
		Col = m_Color_Mp.HSVtoRGB();
		m_bool = true;
	}
	m_MP_bar.SetMulColor(Col);
	m_MP_bar.Draw(
		g_camera2D.GetViewMatrix(),
		g_camera2D.GetProjectionMatrix()
	);
	m_status_bar.Draw(
		g_camera2D.GetViewMatrix(),
		g_camera2D.GetProjectionMatrix()
	);

	for (int i = 0; i < num; i++) {
		m_status[i].Draw(
			g_camera2D.GetViewMatrix(),
			g_camera2D.GetProjectionMatrix()
		);
	}
	m_font.BeginDraw();	//�t�H���g�̕`��J�n�B

	wchar_t toubatu[256];
	swprintf_s(toubatu, L"%d�����I�I",m_Score->GetNum());	//�X�R�A�̃N���X����f�[�^�𒊏o���\������B

	m_font.Draw(
		toubatu,		//�\�����镶����B
		{ FRAME_BUFFER_W / 2.0f,-FRAME_BUFFER_H / 2.0f },			//�\��������W�B0.0f, 0.0����ʂ̒��S�B
		{0.0f,0.0f,0.0f,1.0f},
		0.0f,
		3.0f,
		{1.0f,0.0f});
	m_font.EndDraw();		//�t�H���g�̕`��I���B
}
void UI::Draw()
{

}