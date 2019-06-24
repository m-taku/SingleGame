#pragma once
#include"UI.h"
/// <summary>
/// スコア集計クラス
/// </summary>
class Score : public Gameobject
{
public:
	/// <summary>
	/// コンストラクタ。
	/// </summary>
	Score();
	/// <summary>
	/// デストラクタ。
	/// </summary>
	~Score();
	/// <summary>
	/// Gemeobjectから継承したLoat関数。
	/// </summary>
	/// <returns>
	/// 成功でtrue、失敗でfalse。
	/// </returns>
	bool Load() override;
	/// <summary>
	/// スコアの加算
	/// </summary>
	void AddScore()
	{
		m_Allscore++;
	}
	/// <summary>
	/// 現在のスコアの合計
	/// </summary>
	/// <returns>
	/// スコア（int）
	/// </returns>
	const int GetNum()
	{
		return m_Allscore;
	}

	void Gettime(int& minit, int& second)
	{
		minit = m_minute;
		second = m_seconds;
	}
	/// <summary>
	/// Gameobjectから継承したDraw関数
	/// </summary>
	void PostDraw() override;
private:
	int m_Allscore = 0;
	int m_minute = 0;
	int m_seconds = 0;
	Font m_font;											//文字表示のインスタンス
	Timer m_timer;											//タイマークラスのインスタンス
};
