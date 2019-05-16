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
	//持っているすべてのインスタンスを削除
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
	//げーむのすべてのインスタンスを発生
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
	//ここで制限時間の処理
	//制限時間のタイマーをラップでストップさせる。
	m_timer.TimerStop();
	//制限時間以内ならば
	if (m_timer.GetAllMinute() < taimup) {

		m_font.BeginDraw();	//フォントの描画開始。
							//秒の計算をする
		auto taim = (int)m_timer.GetAllSeconds() % 60;
		auto col = Color::HSVtoRGB({ 150.0f / 360.0f,10.0f,1.0f });

		swprintf_s(toubatu, L"残り時間%d分%d秒", (taimup-1 - m_timer.GetAllMinute()), (60 - taim));		//表示用にデータを加工
		m_font.Draw(
			toubatu,		//表示する文字列。
			{ -FRAME_BUFFER_W / 2.0f,FRAME_BUFFER_H / 2.0f },			//表示する座標。0.0f, 0.0が画面の中心。
			{ col.x,col.y,col.z,1.0f },
			0.0f,
			3.0f,
			{ 0.0f,1.0f }
		);
		m_font.EndDraw();
	}
	else
	{	//制限時間を超えていたら
		//ゲームおーばーが発生していなければ
		if (nullptr == g_objectManager->FindGO<Gameover>("Gameover")) {
			//ゲームおーばを発生させる
			g_objectManager->NewGO<Gameover>(GameObjectPriority_Gameover, "Gameover")->Setfra(true);
		}
	}
	//タイマーを再開させる
	m_timer.TimerRestart();
}