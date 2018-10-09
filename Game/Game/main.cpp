#include"stdafx.h"
#include"system/system.h"
#include"level/Level.h"
#include"UI.h"
#include"Stage.h"
#include"Enemy/Enemy.h"
#include"Enemy/Enemyleader.h"
#include"Player.h"
#include"Gamecamera.h"

///////////////////////////////////////////////////////////////////
// ウィンドウプログラムのメイン関数。
///////////////////////////////////////////////////////////////////
GameobjectManager* objectManager;
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
	//ゲームの初期化。
	InitGame(hInstance, hPrevInstance, lpCmdLine, nCmdShow, "Game");

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
	//g_camera3D.SetTarget({ 0.0f, 0.0f, 0.0f });
	//g_camera3D.SetPosition({ 0.0f, 100.0f, 0.0f });
	//g_camera3D.SetUp({ 1.0f, 0.0f, 0.0f });
	//g_camera3D.SetFar(10000.0f);


	//プレイヤー
	//Player player;
	GameobjectManager objectManage;
	objectManager = &objectManage;
	objectManager->NewGO<Stage>(0);
	//Navimake* navimake = nullptr;
	//ゲームループ。
	UI* Ui = objectManager->NewGO<UI>(0);
	Player* player = objectManager->NewGO<Player>(0);
	Gamecamera* Camera = objectManager->NewGO<Gamecamera>(10);
	Camera->SetPlayer(player);
	player->SetCamera(Camera);
	Level level;

	g_physics.SetDebugDrawMode(btIDebugDraw::DBG_DrawWireframe);

	static int kuku = 0;
	//Player* ks = objectManager->NewGO<Player>(1);
	level.Init(L"Assets/level/Enemy_lever.tkl", [&](LevelObjectData objData)
	{
		kuku++;
		if (kuku != 2) {
			return true;
		}
		Enemyleader* enemy = objectManager->NewGO<Enemyleader>(1, "Enemyleader");
		enemy->Setposition(objData.position);
		enemy->Setplayer(player);
		return true;
	});
	while (DispatchWindowMessage() == true)
	{
		//描画開始。
		g_graphicsEngine->BegineRender();
		int debak = 1;
		//ゲームパッドの更新。	
		for (auto& pad : g_pad) {
			pad.Update();
		}

     //   auto ks = objectManager->NewGO<Player>(0);
		//物理エンジンの更新。
		objectManager->Execute();
		g_physics.Update();
		if (debak==1)
		{
			g_physics.DebubDrawWorld();
		}
		//プレイヤーの更新。
		//player.Update();
		//プレイヤーの描画。
		//player.Draw();

	//    objectManager->DereteGO(ks);
		//カメラの更新。
		//描画終了。
		g_graphicsEngine->EndRender();
	}
}