#pragma once
#include"EnemyState.h"
#include "Physics/CapsuleCollider.h"
#include "Physics/RigidBody.h"
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
	/// <summary>
	/// 剣に対してプレイヤーが当たったかどうか
	/// </summary>
	void CollisionTest();
private:
	/// <summary>
	/// 剣の当たり判定用の回転角度取得
	/// </summary>
	/// <param name="vector1">
	/// １つ目のベクトル（Normalize）
	/// </param>
	/// <param name="vector2">
	/// 2つ目のベクトル（Normalize）
	/// </param>
	/// <returns>
	/// 回転クオータニオン
	/// </returns>
	CQuaternion anglecalculation(CVector3 vector1, CVector3 vector2);
	/// <summary>
	/// 剣の中心と手の位置を検索する
	/// </summary>
	void FindSwordpos();
	int m_boneNo = 0;										//手のボーンの番号
	CVector3 m_oldhandpos = CVector3::Zero();				//移動前の手のポジション
	CVector3 m_handpos= CVector3::Zero();					//移動後の手のポジション
	CVector3 m_oldSwordcenter = CVector3::Zero();			//移動前の剣の中心ポジション
	CVector3 m_Swordcenter = CVector3::Zero();				//移動後の剣の中心ポジション
	CVector3 m_Up;											//手の上方向ベクトル
	VectorDraw* m_debugVecor = nullptr;						//デバック用のベクトル表示
}; 

