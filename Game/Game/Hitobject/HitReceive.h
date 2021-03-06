#pragma once
#include"Enemy/Enemy.h"
#include"Player/Player.h"
/// <summary>
/// 当たり判定用のオブジェクトデータ
/// </summary>
class HitReceive :public Noncopyable
{
public:
	/// <summary>
	/// オブジェクトの名前
	/// （タグ付の目的）
	/// </summary>
	enum objict_Name {
		enemy,
		player,
		name_num
	};
	/// <summary>
	/// コンストラクタ
	/// </summary>
	HitReceive();
	/// <summary>
	/// デストラクタ。
	/// </summary>
	~HitReceive();
	/// <summary>
	/// オブジェクトを制作する
	/// </summary>
	/// <param name="pos">
	/// ポジションのポインタ
	/// （動かす対象のポインタ）
	/// </param>
	/// <param name="radius">
	/// オブジェクトの半径
	/// </param>
	/// <param name="objict">
	/// フック関数
	/// </param>
	/// <param name="name">
	/// オブジェクトの名前
	/// </param>
	void Create(const CVector3* pos, float radius, std::function<void(float damage)>  objict, objict_Name name);
	/// <summary>
	/// オブジェクト同士の当たり判定
	/// </summary>
	/// <param name="pos">
	/// 当てる側のポジション
	/// </param>
	/// <param name="Circle">
	/// 当てるが側の球体の半径
	/// </param>
	/// <param name="damage">
	/// 当たった場合の与える変数
	/// （今回はダメージ数）
	/// </param>
	/// <returns>
	/// 当たればtrue
	/// </returns>
	bool HitTest(CVector3 pos,float Circle,float damage);
	/// <summary>
	/// オブジェクトの名前（タグ）のゲット
	/// </summary>
	/// <returns>
	/// オブジェクトの名前、タグ（objict_Name ）
	/// </returns>
	objict_Name Getobjict_Name()
	{
		return m_name;
	}
private:
	const CVector3* m_pos = nullptr;						//オブジェクトのポジション
	float m_radius = 0.0f;									//オブジェクトの半径
	objict_Name m_name = name_num;							//オブジェクトの名前（タグ）
	std::function<void(float damage)>  m_fuk;				//当たった場合に呼びたい関数
};
