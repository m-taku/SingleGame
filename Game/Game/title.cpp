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
	title_haikei.Init(&texture, 1280.0f, 720.0f);
	Texture.CreateFromDDSTextureFromFile(L"Resource/sprite/yellow.dds");
	title_moji.Init(&Texture, 1280.0f, 720.0f);
	texturea.CreateFromDDSTextureFromFile(L"Resource/sprite/White.dds");
	feid.Init(&texturea, 1280.0f, 720.0f);

	title_haikei.Updete(CVector3::Zero(), CQuaternion::Identity(), CVector3::One());
	title_moji.Updete(CVector3::Zero(), CQuaternion::Identity(), CVector3::One());
	return true;
}
void title::Update()
{
	title_haikei.Updete(CVector3::Zero(), CQuaternion::Identity(), CVector3::One());
	static float la = 0.0f;
	title_moji.Updete(CVector3::Zero(), CQuaternion::Identity(), { 1.0f,1.0f,1.0f });
	if (toumei >= 1.0f) {
		objectManager->NewGO<Game>(1);
		objectManager->DereteGO(this);
	}
	feid.SetclearColor(toumei);
	toumei += la;
	if (g_pad[0].IsTrigger(enButtonA) )
	{
		la = 0.02f;
	}
	
}
void title::postDraw()
{

	title_moji.Draw(
		g_camera2D.GetViewMatrix(),
		g_camera2D.GetProjectionMatrix()
	);
	title_haikei.Draw(
		g_camera2D.GetViewMatrix(),
		g_camera2D.GetProjectionMatrix()
	);
	feid.Draw(
		g_camera2D.GetViewMatrix(),
		g_camera2D.GetProjectionMatrix()
	);
}
