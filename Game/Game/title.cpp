#include "stdafx.h"
#include "title.h"
#include"Game.h"

title::title()
{
}


title::~title()
{
}
bool title::Load()
{
	texture.CreateFromDDSTextureFromFile(L"Resource/sprite/taitoru.dds");
	HP_bar_waku.Init(&texture, 1280.0f, 720.0f);
	Texture.CreateFromDDSTextureFromFile(L"Resource/sprite/yellow.dds");
	HP_bar.Init(&Texture, 1280.0f, 720.0f);
	HP_bar_waku.Updete(CVector3::Zero(), CQuaternion::Identity(), CVector3::One(), { 0.0f,1.0f });
	HP_bar.Updete(CVector3::Zero(), CQuaternion::Identity(), CVector3::One(), { 0.0f,1.0f });
	return true;
}
void title::Update()
{
	HP_bar_waku.Updete(CVector3::Zero(), CQuaternion::Identity(), CVector3::One());

	HP_bar.Updete(CVector3::Zero(), CQuaternion::Identity(), { 1.0f,1.0f,1.0f });
	if (g_pad[0].IsTrigger(enButtonA) )
	{
		objectManager->NewGO<Game>(1);
		objectManager->DereteGO(this);
	}
}
void title::postDraw()
{

	HP_bar.Draw(
		g_camera2D.GetViewMatrix(),
		g_camera2D.GetProjectionMatrix()
	);	
	HP_bar_waku.Draw(
		g_camera2D.GetViewMatrix(),
		g_camera2D.GetProjectionMatrix()
	);
}
