#include "stdafx.h"
#include "UI.h"
#include"Gameover.h"

namespace {
	//HPBarのサイズ
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
	//プレイヤーのHP用のデータをロード
	m_Texture_bar_waku.CreateFromDDSTextureFromFile(L"Resource/sprite/HP_Player_waku.dds");
	m_HP_bar_waku.Init(m_Texture_bar_waku.GetBody(), Hpbarsize.x, Hpbarsize.y);
	m_Texture_bar.CreateFromDDSTextureFromFile(L"Resource/sprite/HP_Player.dds");
	m_HP_bar.Init(m_Texture_bar.GetBody(), Hpbarsize.x, Hpbarsize.y);
	m_HP_bar_waku.Updete(m_HP_waku_position, CQuaternion::Identity(), CVector3::One(), {0.0f,1.0f});
	m_HP_bar.Updete(m_HP_position, CQuaternion::Identity(), CVector3::One(), { 0.0f,1.0f });
	//制限時間のタイマーのスタート
	m_timer.TimerStart();
	return true;
}
void UI::Update()
{
	//HPの遷移用にテクスチャを更新
	m_HP_bar_waku.Updete(m_HP_waku_position, CQuaternion::Identity(), CVector3::One(), { 0.0f,1.0f });
	m_HP_bar.Updete(m_HP_position, CQuaternion::Identity(),{m_HP- m_Damage,1.0f,1.0f}, { 0.0f,1.0f });
}
void UI::PostDraw()
{	
	//プレイヤーのHP用のスプライトをDraw
	m_HP_bar_waku.Draw(
		g_camera2D.GetViewMatrix(),
		g_camera2D.GetProjectionMatrix()
	);
	m_HP_bar.Draw(
		g_camera2D.GetViewMatrix(),
		g_camera2D.GetProjectionMatrix()
	);
	m_font.BeginDraw();	//フォントの描画開始。
	static Color color;
	wchar_t toubatu[256];
	swprintf_s(toubatu, L"%d討伐！！",m_Score->GetNum());	//スコアのクラスからデータを抽出し表示する。
	auto Col = color.HSVtoRGB();
	m_font.Draw(
		toubatu,		//表示する文字列。
		{ FRAME_BUFFER_W / 2.0f,-FRAME_BUFFER_H / 2.0f },			//表示する座標。0.0f, 0.0が画面の中心。
		Col,//{ 0.0f,0.0f,0.0f,1.0f },
		0.0f,
		3.0f,
		{1.0f,0.0f}
	);
	//制限時間のタイマーをラップでストップさせる。
	m_timer.TimerStop();
	//制限時間以内ならば
	if (m_timer.GetAllMinute() < GAMETAIM) {
		//秒の計算をする
		auto taim = (int)m_timer.GetAllSeconds() % 60;
		auto col = Color::HSVtoRGB({ 150.0f / 360.0f,10.0f,1.0f });

		swprintf_s(toubatu, L"残り時間%d分%d秒", (GAMETAIM -m_timer.GetAllMinute()), (60- taim));		//表示用にデータを加工
		m_font.Draw(
			toubatu,		//表示する文字列。
			{ -FRAME_BUFFER_W / 2.0f,FRAME_BUFFER_H / 2.0f },			//表示する座標。0.0f, 0.0が画面の中心。
			{ col.x,col.y,col.z,1.0f },
			0.0f,
			3.0f,
			{ 0.0f,1.0f }
		);
	}	
	else
	{	//制限時間を超えていたら
		//ゲームおーばーが発生していなければ
		if (nullptr == g_objectManager->FindGO<Gameover>("Gameover")) {
			//ゲームおーばを発生させる
			g_objectManager->NewGO<Gameover>(GameObjectPriority_Gameover, "Gameover");
			//すべての関数をストップさせ、Drawのみにする
			g_objectManager->AllStoporComeback();
		}
	}
	//タイマーを再開させる
	m_timer.TimerRestart();
	m_font.EndDraw();		//フォントの描画終了。
}
void UI::Draw()
{

}