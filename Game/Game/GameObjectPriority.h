#pragma once


/*
*GameObjectの優先順位。
*値が小さいものほど先に実行される。
*/
enum GameObjectPriority{
	GameObjectPriority_Default,				//デフォルトの優先順位。
	GameObjectPriority_Game = 1,			//ゲーム制御オブジェクト。
	GameObjectPriority_Player = 1,			//プレイヤー。
	GameObjectPriority_EnemyLeader = 1,		//エネミーのリーダー。
	GameObjectPriority_Camera = 10,			//カメラは絶対に一番最後。

};
