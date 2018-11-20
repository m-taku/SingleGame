#pragma once
class Enemy;
class Player;
/// <summary>
/// ステートの基底クラス。
/// </summary>
class EnemyState
{
public:
	/// <summary>
	/// コンストラクタ。
	/// </summary>
	/// <param name="enemy_point">
	/// エネミーのポインタ。（Enemy*）
	/// </param>
	/// <param name="pla">
	/// プレイヤーのポインタ。（Player*）
	/// </param>
	EnemyState(Enemy* enemy_point, Player* pla);
	/// <summary>
	/// デストラクタ。
	/// </summary>
	virtual ~EnemyState();
	/// <summary>
	/// アップデート。
	/// </summary>
	virtual void Update() = 0;
protected:
	Enemy* m_enemy=nullptr;			//エネミーのインスタンス
	Player* m_player=nullptr;			//プレイヤーのインスタンス
};

