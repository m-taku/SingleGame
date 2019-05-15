#pragma once

/// <summary>
/// GameObjectの優先順位
/// </summary>
/// <remarks>
/// 値が小さいものほど先に実行される。
/// </remarks>
enum GameObjectPriority{
	GameObjectPriority_Game,			//ゲーム制御オブジェクト。
	GameObjectPriority_Default,			//デフォルトの優先順位。
	GameObjectPriority_Player,			//プレイヤー。
	GameObjectPriority_EnemyLeader,		//エネミーのリーダー。
	GameObjectPriority_ta,		//ゲームオーバーは表示の関係で最後のほうに
	GameObjectPriority_Gameover,		//ゲームオーバーは表示の関係で最後のほうに
	GameObjectPriority_Camera = 10		//カメラは絶対に一番最後。

};
