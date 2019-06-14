#pragma once
#include"Player/Player.h"
#include"Enemyleader/Enemyleader.h"
/// <summary>
/// エネミーのマネージャークラス
/// </summary>
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
	/// Gameobjectから継承したcomeback関数
	/// </summary>
	void Comeback() override;
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
	/// <param name="score"></param>
	void SetScore(Score* score)
	{
		m_Score = score;
	}
	void SpawnEnemy(CVector3 pos,Ability* k,int count=0);
private:
	Player * m_player = nullptr;
	std::vector<Enemyleader*> m_enemy;
	Font* m_font = nullptr;											//文字表示のインスタンス
	int m_No = 0;
	int m_count = 0;
	bool m_BossSpoon = false;
	int m_Maxsporn = 10;
	Score* m_Score = nullptr;
	std::vector<CVector3> m_spawnpos;
	Timer* m_timer = nullptr;
};