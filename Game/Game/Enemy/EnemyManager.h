#pragma once
#include"Player/Player.h"
#include "Enemyleader/Enemyleader.h"
/// <summary>
/// エネミーのマネージャークラス
/// </summary>
class HitObjict;
class EnemyManager :public Gameobject
{
public:
	/// <summary>
	/// コンストラクタ。
	/// </summary>
	EnemyManager();
	/// <summary>
	/// デストラクタ。
	/// </summary>
	~EnemyManager();
	/// <summary>
	/// Gameobjectから継承した最初に呼ばれる関数。
	/// </summary>
	/// <returns>
	/// Load成功でtrue、失敗でfalse。
	/// </returns>
	bool Load() override;
	/// <summary>
	/// GemeObjectから継承したUpdate関数。
	/// </summary>
	void Update() override;
	/// <summary>
	/// プレイヤーのインスタンスのセット。
	/// </summary>
	/// <param name="player">
	/// セットしたいプレイヤーのインスタンス。(Player*)
	/// </param>
	void SetPlayer(Player* pleyer)
	{
		m_player = pleyer;
	}
	/// <summary>
	/// 
	/// </summary>
	/// <param name="Hit"></param>
	void Sethit(HitObjict* Hit)
	{
		m_hit = Hit;
	}
	void Leaderdet(Enemyleader* k)
	{
		m_enemy.erase(
			std::remove(m_enemy.begin(), m_enemy.end(),k),
			m_enemy.end());
	}
private:
	Player * m_player = nullptr;
	std::vector<Enemyleader*> m_enemy;
	Font* m_font = nullptr;											//文字表示のインスタンス
	int m_No = 0;
	Timer* m_timer = nullptr;
	HitObjict* m_hit;
};