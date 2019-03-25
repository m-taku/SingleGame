#include "stdafx.h"
#include "UI.h"
#include"Gameover.h"

namespace {
	//HPBar�̃T�C�Y
	const CVector2 Hpbarsize = { 1000.0f, 250.0f };
	const int GAMETAIM = 2;
}

UI::UI()
{
}


UI::~UI()
{

}
bool UI::Load()
{
	//�v���C���[��HP�p�̃f�[�^�����[�h
	m_Texture_bar_waku.CreateFromDDSTextureFromFile(L"Resource/sprite/HP_Player_waku.dds");
	m_HP_bar_waku.Init(m_Texture_bar_waku.GetBody(), Hpbarsize.x, Hpbarsize.y);
	m_Texture_bar.CreateFromDDSTextureFromFile(L"Resource/sprite/HP_Player.dds");
	m_HP_bar.Init(m_Texture_bar.GetBody(), Hpbarsize.x, Hpbarsize.y);
	m_HP_bar_waku.Updete(m_HP_waku_position, CQuaternion::Identity(), CVector3::One(), {0.0f,1.0f});
	m_HP_bar.Updete(m_HP_position, CQuaternion::Identity(), CVector3::One(), { 0.0f,1.0f });
	//�������Ԃ̃^�C�}�[�̃X�^�[�g
	m_timer.TimerStart();
	return true;
}
void UI::Update()
{
	//HP�̑J�ڗp�Ƀe�N�X�`�����X�V
	m_HP_bar_waku.Updete(m_HP_waku_position, CQuaternion::Identity(), CVector3::One(), { 0.0f,1.0f });
	m_HP_bar.Updete(m_HP_position, CQuaternion::Identity(),{m_HP- m_Damage,1.0f,1.0f}, { 0.0f,1.0f });
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
	m_font.BeginDraw();	//�t�H���g�̕`��J�n�B
	static Color color;
	wchar_t toubatu[256];
	swprintf_s(toubatu, L"%d�����I�I",m_Score->GetNum());	//�X�R�A�̃N���X����f�[�^�𒊏o���\������B
	auto Col = color.HSVtoRGB();
	m_font.Draw(
		toubatu,		//�\�����镶����B
		{ FRAME_BUFFER_W / 2.0f,-FRAME_BUFFER_H / 2.0f },			//�\��������W�B0.0f, 0.0����ʂ̒��S�B
		Col,//{ 0.0f,0.0f,0.0f,1.0f },
		0.0f,
		3.0f,
		{1.0f,0.0f}
	);
	//�������Ԃ̃^�C�}�[�����b�v�ŃX�g�b�v������B
	m_timer.TimerStop();
	//�������Ԉȓ��Ȃ��
	if (m_timer.GetAllMinute() < GAMETAIM) {
		//�b�̌v�Z������
		auto taim = (int)m_timer.GetAllSeconds() % 60;
		auto col = Color::HSVtoRGB({ 150.0f / 360.0f,10.0f,1.0f });

		swprintf_s(toubatu, L"�c�莞��%d��%d�b", (GAMETAIM -m_timer.GetAllMinute()), (60- taim));		//�\���p�Ƀf�[�^�����H
		m_font.Draw(
			toubatu,		//�\�����镶����B
			{ -FRAME_BUFFER_W / 2.0f,FRAME_BUFFER_H / 2.0f },			//�\��������W�B0.0f, 0.0����ʂ̒��S�B
			{ col.x,col.y,col.z,1.0f },
			0.0f,
			3.0f,
			{ 0.0f,1.0f }
		);
	}	
	else
	{	//�������Ԃ𒴂��Ă�����
		//�Q�[�����[�΁[���������Ă��Ȃ����
		if (nullptr == g_objectManager->FindGO<Gameover>("Gameover")) {
			//�Q�[�����[�΂𔭐�������
			g_objectManager->NewGO<Gameover>(GameObjectPriority_Gameover, "Gameover");
			//���ׂĂ̊֐����X�g�b�v�����ADraw�݂̂ɂ���
			g_objectManager->AllStoporComeback();
		}
	}
	//�^�C�}�[���ĊJ������
	m_timer.TimerRestart();
	m_font.EndDraw();		//�t�H���g�̕`��I���B
}
void UI::Draw()
{

}