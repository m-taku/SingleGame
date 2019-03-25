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
	Score()
	{

	}
	/// <summary>
	/// デストラクタ。
	/// </summary>
	~Score()
	{

	}
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
private:
	int m_Allscore = 0;
};

