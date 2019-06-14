#pragma once
#include"EnemyState.h"
#include"Path.h"
/// <summary>
/// Enemyのグループに集合するときの処理ステートクラス。
/// </summary>
class EnemyStategathering :public EnemyState
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
	EnemyStategathering(Enemy* enemy_point, const CVector3* pos);
	/// <summary>
	/// デストラクタ。
	/// </summary>
	~EnemyStategathering();
	/// <summary>
	/// EnemyStateから継承したアップデート関数。
	/// </summary>
	void Update() override;
private:
	Path* m_path = nullptr;										//経路探査のインスタンス
	CVector3 m_oldposition = CVector3::Zero();					//1フレーム前のポジション（壁擦りなどの判定などなど）
	CVector3 m_nextpos = CVector3::Zero();						//経路探査で出た次のポジション
};

