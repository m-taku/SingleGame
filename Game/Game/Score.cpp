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
	//ここで制限時間の処理
	//制限時間のタイマーをラップでストップさせる。
	m_timer.TimerStop();
	//制限時間以内ならば
	if (m_timer.GetAllMinute() < taimup) {

		m_font.BeginDraw();	//フォントの描画開始。
					//秒の計算をする
		m_minute = taimup-(int)m_timer.GetAllMinute()-1;
		m_seconds = 59-(int)m_timer.GetAllSeconds() % 60;
		auto col = Color::HSVtoRGB({ 150.0f / 360.0f,10.0f,1.0f });

		swprintf_s(toubatu, L"残り時間%d分%02d秒", (m_minute), (m_seconds));		//表示用にデータを加工
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
