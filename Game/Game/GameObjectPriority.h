#pragma once

/// <summary>
/// GameObjectの優先順位
/// </summary>
/// <remarks>
/// 値が小さいものほど先に実行される。
/// </remarks>
enum GameObjectPriority{
	GameObjectPriority_Default,			//デフォルトの優先順位。
	GameObjectPriority_Game,			//ゲーム制御オブジェクト。
	GameObjectPriority_Player,			//プレイヤー。
	GameObjectPriority_EnemyLeader,		//エネミーのリーダー。
	GameObjectPriority_Camera = 10,		//カメラは絶対に一番最後。

};
