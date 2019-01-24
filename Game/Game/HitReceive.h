#pragma once
#include"Enemy/Enemy.h"
#include"Player/Player.h"
/// <summary>
/// 当たり判定用のオブジェクトデータ
/// </summary>
class HitReceive :public Noncopyable
{
public:
	enum objict_Name {
		enemy,
		player,
		name_num
	};
	HitReceive();
	~HitReceive();
	/// <summary>
	/// 
	/// </summary>
	/// <param name="pos"></param>
	/// <param name="radius"></param>
	/// <param name="objict">
	/// フック関数
	/// </param>
	/// <param name="name"></param>
	void Create(const CVector3* pos, float radius, std::function<void()>  objict, objict_Name name);
	bool HitTest(CVector3 pos);
	objict_Name Getobjict_Name()
	{
		return m_name;
	}
private:
	const CVector3* m_pos = nullptr;
	float m_radius = 0.0f;
	objict_Name m_name = name_num;
	std::function<void()>  m_fuk;
};
