#include "stdafx.h"
#include "Game.h"
#include"UI.h"
#include"Enemy/EnemyManager.h"
#include"HitObjict.h"
#include"Gameover.h"
#include"Enemy.h"
#include"Player.h"
#include"Gamecamera.h"
#include"Stage.h"
#include"ItemManager.h"
namespace {
	int taimup = 3;
};
Game::Game()
{
}
Game::~Game()
{

}
void Game::OnDestroy()
{
	//�����Ă��邷�ׂẴC���X�^���X���폜
	g_objectManager->DereteGO(m_camera);
	g_objectManager->DereteGO(m_stage);
	g_objectManager->DereteGO(m_player);
	g_objectManager->DereteGO(m_ui);
	g_objectManager->DereteGO(m_enemyManager);
	g_objectManager->DereteGO(m_score); 
	g_objectManager->DereteGO(m_item);
	GetHitObjict().Release();
}
bool Game::Load()
{
	//���[�ނ̂��ׂẴC���X�^���X�𔭐�
	m_player = g_objectManager->NewGO<Player>(GameObjectPriority_Player,"player");	
	m_camera = g_objectManager->NewGO<Gamecamera>(GameObjectPriority_Camera);
	m_ui = g_objectManager->NewGO<UI>(GameObjectPriority_Default,"UI");
	m_score = g_objectManager->NewGO<Score>(GameObjectPriority_Default);
	m_stage = g_objectManager->NewGO<Stage>(GameObjectPriority_Default);
	m_enemyManager = g_objectManager->NewGO<EnemyManager>(GameObjectPriority_EnemyLeader);
	m_camera->SetPlayer(m_player);
	m_player->SetCamera(m_camera);
	m_ui->SetScore(m_score);
	m_item = g_objectManager->NewGO<ItemManager>(GameObjectPriority_Default,"item");
	//m_score->SetUI(m_ui);
	m_enemyManager->SetPlayer(m_player);
	m_enemyManager->SetScore(m_score);
	m_timer.TimerStart();
	return true;
}
void Game::Update()
{
}
void Game::PostDraw()
{

	wchar_t toubatu[256];
	//�����Ő������Ԃ̏���
	//�������Ԃ̃^�C�}�[�����b�v�ŃX�g�b�v������B
	m_timer.TimerStop();
	//�������Ԉȓ��Ȃ��
	if (m_timer.GetAllMinute() < taimup) {

		m_font.BeginDraw();	//�t�H���g�̕`��J�n�B
							//�b�̌v�Z������
		auto taim = (int)m_timer.GetAllSeconds() % 60;
		auto col = Color::HSVtoRGB({ 150.0f / 360.0f,10.0f,1.0f });

		swprintf_s(toubatu, L"�c�莞��%d��%d�b", (taimup-1 - m_timer.GetAllMinute()), (60 - taim));		//�\���p�Ƀf�[�^�����H
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