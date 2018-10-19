#include "stdafx.h"
#include "UI.h"


UI::UI()
{
}


UI::~UI()
{

}
bool UI::Load()
{
	texture.CreateFromDDSTextureFromFile(L"Resource/sprite/HP_Player_waku.dds");
	HP_bar_waku.Init(&texture,1000.0f, 250.0f);
	Texture.CreateFromDDSTextureFromFile(L"Resource/sprite/HP_Player.dds");
	HP_bar.Init(&Texture, 1000.0f, 250.0f);
	HP_bar_waku.Updete(m_HP_waku_position, CQuaternion::Identity(), CVector3::One(), {0.0f,1.0f});
	HP_bar.Updete(m_HP_position, CQuaternion::Identity(), CVector3::One(), { 0.0f,1.0f });
	return true;
}
void UI::Update()
{
	//if (HP > 0.0f) {
	//	HP -= 0.01f;
	//}
	//else {
	//	HP = 0.0f;
	//}
	HP_bar_waku.Updete(m_HP_waku_position, CQuaternion::Identity(), CVector3::One(), { 0.0f,1.0f });

	HP_bar.Updete(m_HP_position, CQuaternion::Identity(),{m_HP- m_Damage,1.0f,1.0f}, { 0.0f,1.0f });
}
void UI::postDraw()
{	
	HP_bar_waku.Draw(
		g_camera2D.GetViewMatrix(),
		g_camera2D.GetProjectionMatrix()
	);
	HP_bar.Draw(
		g_camera2D.GetViewMatrix(),
		g_camera2D.GetProjectionMatrix()
	);

}
void UI::Draw()
{

}