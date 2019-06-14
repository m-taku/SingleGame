#pragma once
#include"EnemyState.h"
class EnemyStateDead :public EnemyState
{
public:	/// <summary>
		/// コンストラクタ
		/// </summary>
		/// <param name="enemy_point">
		/// エネミーのポインタ（Enemy*）
		/// </param>
		/// <param name="pla">
		/// プレイヤーのポインタ（Player*）
		/// </param>
	EnemyStateDead(Enemy* enemy_point, const CVector3* pos);
	/// <summary>
	///デストラクタ
	/// </summary>
	~EnemyStateDead();
	/// <summary>
	/// EnemyStateから継承したアップデート関数。
	/// </summary>
	void Update() override;
private:
	float kakudo = 0.0f;
};

