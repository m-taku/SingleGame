#pragma once
#include"EnemyState.h"
/// <summary>
/// Enemyの追尾処理ステートクラス。
/// </summary>
class EnemyStateTracking:public EnemyState
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
	EnemyStateTracking(Enemy* enemy_point, Player* pla);
	/// <summary>
	/// デストラクタ
	/// </summary>
	~EnemyStateTracking();
	/// <summary>
	/// EnemyStateから継承したアップデート関数。
	/// </summary>
	void Update() override;
private:
	VectorDraw* vector = nullptr;			//デバック用のベクトル表示インスタンス
};

