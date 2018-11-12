#pragma once
#include"EnemyState.h"
/// <summary>
/// Enemyのアタックステートクラス。
/// </summary>
class EnemyStateAttack :public EnemyState
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
	EnemyStateAttack(Enemy* enemy_point, Player* pla);
	/// <summary>
	/// デストラクタ。
	/// </summary>
	~EnemyStateAttack();	
	/// <summary>
	/// EnemyStateから継承したアップデート関数。
	/// </summary>
	void Update() override;
private:
}; 

