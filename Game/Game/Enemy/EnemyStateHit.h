#pragma once
#include"EnemyState.h"
class EnemyStateHit :public EnemyState
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="enemy_point">
	/// エネミーのポインタ（Enemy*）
	/// </param>
	/// <param name="pla">
	/// プレイヤーのポインタ（Player*）
	/// </param>
	EnemyStateHit(Enemy* enemy_point, const CVector3* pos);
	/// <summary>
	/// デストラクタ
	/// </summary>
	~EnemyStateHit();
	/// <summary>
	/// EnemyStateから継承したアップデート関数。
	/// </summary>
	void Update() override;
private:
	float speed = -2.0f;
};

