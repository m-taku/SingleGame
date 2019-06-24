#pragma once
#include"Player/Player.h"
#include"Enemyleader/Enemyleader.h"
#include <random>
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
	bool SpawnEnemy(CVector3 ispos)
	{
		//沸きの上限に達していなければ
		if (m_Maxsporn >= m_enemy.size()) {
			float lengthMax = FLT_MAX;
			int No;
			for (int i = 0; i < m_spawnpos.size(); i++)
			{
				auto len = (m_spawnpos[i] - ispos).Length();
				if (lengthMax >= len)
				{
					No = i;
					lengthMax = len;
				}
			}
			
			std::random_device rnd;     // 非決定的な乱数生成器を生成
			std::mt19937 mt(rnd());     //  メルセンヌ・ツイスタの32ビット版、引数は初期シード値
			std::uniform_int_distribution<> rand2(1,5);        // [0, 99] 範囲の一様乱数
			Ability* ability;
			switch (rand2(mt))
			{
			case 1:
			case 2:
			case 3:			
			case 4:
				ability = new enemy_hero;
				ability->m_Spawnnum = 3;
				break;
			case 5:
				ability = new enemy_Lance;
				break;
			default:
				break;
			}
			SpawnEnemy(m_spawnpos[No], ability);
			return true;
		}
		return false;
	}
	void SpawnEnemy(CVector3 pos,  Ability* ability, CQuaternion angle=CQuaternion::Identity(), int count=0);
private:
	Player * m_player = nullptr;
	std::vector<Enemyleader*> m_enemy;
	Font* m_font = nullptr;											//文字表示のインスタンス
	int m_No = 0;
	int m_count = 0;
	bool m_BossSpoon = false;
	int m_Maxsporn = 30;
	Score* m_Score = nullptr;
	std::vector<CVector3> m_spawnpos;
	Timer* m_timer = nullptr;
};