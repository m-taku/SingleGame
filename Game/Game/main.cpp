#include"stdafx.h"
#include"system/system.h"
#include"title.h"
#include"level/Level.h"
#include"UI.h"
#include"Stage.h"
#include"Enemy/EnemyLeader/Enemyleader.h"
#include"Enemy/Enemy.h"
#include"Player/Player.h"
#include"Gamecamera.h"

//#if _DEBUG
//#include <crtdbg.h>
//#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)
//#endif


///////////////////////////////////////////////////////////////////
// ウィンドウプログラムのメイン関数。
///////////////////////////////////////////////////////////////////
GameobjectManager* g_objectManager;
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
	//ゲームの初期化。
	InitGame(hInstance, hPrevInstance, lpCmdLine, nCmdShow, "Game");

#ifdef _DEBUG
	//::_CrtSetDbgFlag(_CRTDBG_LEAK_CHECK_DF | _CRTDBG_ALLOC_MEM_DF);
	::_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif
	//カメラを初期化。
	g_camera3D.SetPosition({ 0.0f, 150.0f, -1000.0f });
	g_camera3D.SetTarget({ 0.0f, 100.0f, 0.0f });
	g_camera3D.SetFar(10000.0f);	
	g_camera2D.SetTarget(CVector3::Zero());
	g_camera2D.SetPosition({ 0.0f, 0.0f, -10.0f });
	//g_camera2D.SetUpdateProjMatrixFunc(CCamera::enUpdateProjMatrixFunc_Ortho);
	g_camera2D.SetNear(0.1f);
	g_camera2D.SetFar(1000.0f);
	g_camera2D.Setcamera2D(true);
	g_camera2D.Update();
	
	//プレイヤー
	//Player player;
	GameobjectManager objectManage;
	g_objectManager = &objectManage;
	g_physics.SetDebugDrawMode(btIDebugDraw::DBG_DrawWireframe);
	
	auto tittle = g_objectManager->NewGO<title>(0,"title");
	int debak = 0;
	while (DispatchWindowMessage() == true)
	{
		//描画開始。
		g_graphicsEngine->BegineRender();
		//ゲームパッドの更新。	
		for (auto& pad : g_pad) {
			pad.Update();
		}
        //auto ks = objectManager->NewGO<Player>(0);
		//物理エンジンの更新。
		g_objectManager->Execute();
		if (debak==0)
		{
			g_physics.DebubDrawWorld();
		}
		g_physics.Update();
		//プレイヤーの更新。
		//player.Update();
		//プレイヤーの描画。
		//player.Draw();

	    //objectManager->DereteGO(ks);
		//カメラの更新。
		//描画終了。
		g_graphicsEngine->EndRender();
	}
    delete g_graphicsEngine;
}