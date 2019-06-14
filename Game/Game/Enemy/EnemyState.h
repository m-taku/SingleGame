#pragma once
class Enemy;
class Player;
/// <summary>
/// ステートの基底クラス。
/// </summary>
class EnemyState:public Noncopyable
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
	EnemyState(Enemy* enemy_point,const CVector3* pos);
	/// <summary>
	/// デストラクタ。
	/// </summary>
	virtual ~EnemyState();
	/// <summary>
	/// アップデート。
	/// </summary>
	virtual void Update() = 0;
	CVector3 GetTarget3DPosition()
	{
		return *m_targetposition;
	}
	CVector3 GetTarget2DPosition()
	{
		auto pos = *m_targetposition;
		pos.y = 0;
		return pos;
	}
protected:
	Enemy* m_enemy=nullptr;			//エネミーのインスタンス
	const CVector3* m_targetposition = nullptr;
	//Player* m_player=nullptr;			//プレイヤーのインスタンス
};

