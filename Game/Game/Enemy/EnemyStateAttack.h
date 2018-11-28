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
	/// 
	/// </summary>
	bool CollisionTest();
private:
	int m_boneNo = 0;
	CVector3 center = CVector3::Zero();
	CVector3 m_center = CVector3::Zero();
	CVector3 swodaabb2 = CVector3::Zero();
	CVector3 swodaabb20 = CVector3::Zero();
	CQuaternion m_Rot = CQuaternion::Identity();
	//CapsuleCollider m_collide;
	RigidBody*	m_rigidBody=nullptr;					//剛体。デバック
	VectorDraw* m_debugVecor = nullptr;						//デバック用のベクトル表示
}; 

