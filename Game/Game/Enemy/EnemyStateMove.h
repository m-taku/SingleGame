#pragma once
#include"EnemyState.h"
#include"../../Path.h"
/// <summary>
/// Enemyの移動ステートクラス。
/// </summary>
class EnemyStateMove :public EnemyState
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
	EnemyStateMove(Enemy* enemy_point, Player* pla);
	/// <summary>
	/// デストラクタ
	/// </summary>
	~EnemyStateMove();
	/// <summary>
	/// EnemyStateから継承したアップデート関数。
	/// </summary>
	void Update() override;
private:
	Path * path = nullptr;										//経路探査のインスタンス
	CVector3 m_oldposition = CVector3::Zero();					//1フレーム前のポジション（壁擦りなどの判定などなど）
	CVector3 m_nextpos = CVector3::Zero();						//経路探査で出た次のポジション
};

