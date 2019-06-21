#pragma once
#include"EnemyState.h"
class EnemyStateDefens :public EnemyState
{
public:
	EnemyStateDefens(Enemy* enemy_point, const CVector3* pos);
	~EnemyStateDefens();
	/// <summary>
	/// EnemyStateから継承したアップデート関数。
	/// </summary>
	void Update() override;
private:
	enum attack
	{
		Wait,
		Chase
	};
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
	//	CQuaternion anglecalculation(CVector3 vector1, CVector3 vector2);
	int m_boneNo = 0;
	int count = 0;//手のボーンの番号
	attack m_steat = Chase;
	int m_raitspeed = 1.0f;
	int m_kakudo = 1.0f;		//名前決めなおし
	bool m_Hit = false;										//攻撃を当てたかどうか（当てたら判定を消す）
															//VectorDraw* m_debugVecor = nullptr;						//デバック用のベクトル表示
};

