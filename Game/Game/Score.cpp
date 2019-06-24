#include "stdafx.h"
#include"Score.h"
#include"Gameover.h"
#include"EnemyManager.h"
namespace {
	int taimup = 5;
};
Score::Score()
{

}
Score::~Score()
{


}
bool Score::Load()
{
	if (g_objectManager->FindGO<EnemyManager>("EnemyManager")->GetLodefrag()) {
		m_timer.TimerStart();
		m_minute = taimup;
		m_seconds = 0.0f;
		return true;
	}
	return false;
}
void Score::PostDraw()
{
	wchar_t toubatu[256];
	//�����Ő������Ԃ̏���
	//�������Ԃ̃^�C�}�[�����b�v�ŃX�g�b�v������B
	m_timer.TimerStop();
	//�������Ԉȓ��Ȃ��
	if (m_timer.GetAllMinute() < taimup) {

		m_font.BeginDraw();	//�t�H���g�̕`��J�n�B
					//�b�̌v�Z������
		m_minute = taimup-(int)m_timer.GetAllMinute()-1;
		m_seconds = 59-(int)m_timer.GetAllSeconds() % 60;
		auto col = Color::HSVtoRGB({ 150.0f / 360.0f,10.0f,1.0f });

		swprintf_s(toubatu, L"�c�莞��%d��%02d�b", (m_minute), (m_seconds));		//�\���p�Ƀf�[�^�����H
		m_font.Draw(
			toubatu,		//�\�����镶����B
			{ -FRAME_BUFFER_W / 2.0f,FRAME_BUFFER_H / 2.0f },			//�\��������W�B0.0f, 0.0����ʂ̒��S�B
			{ col.x,col.y,col.z,1.0f },
			0.0f,
			3.0f,
			{ 0.0f,1.0f }
		);
		m_font.EndDraw();
	}
	else
	{	//�������Ԃ𒴂��Ă�����
		//�Q�[�����[�΁[���������Ă��Ȃ����
		if (nullptr == g_objectManager->FindGO<Gameover>("Gameover")) {
			//�Q�[�����[�΂𔭐�������
			g_objectManager->NewGO<Gameover>(GameObjectPriority_Gameover, "Gameover")->Setfra(true);
		}
	}
	//�^�C�}�[���ĊJ������
	m_timer.TimerRestart();
}
