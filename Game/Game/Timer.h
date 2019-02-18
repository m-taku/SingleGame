#pragma once
/// <summary>
/// タイマークラス
/// </summary>
class Timer
{
public:
	/// <summary>
	/// コンストラクタ。
	/// </summary>
	Timer();
	/// <summary>
	/// デストラクタ。
	/// </summary>
	~Timer();
	/// <summary>
	/// タイマーのスタート
	/// （これを呼んだ瞬間から計測）
	/// </summary>
	void TimerStart();
	/// <summary>
	/// タイマーをリスタートします。
	/// （総合時間を保持したままもう一度スタートします）
	/// </summary>
	void TimerRestart();
	/// <summary>
	/// ストップ関数
	/// （ストップウォッチのラップのような関数）
	/// </summary>
	void TimerStop();
	/// <summary>
	/// ラップスタートからの秒を返す
	/// </summary>
	/// <returns>
	/// 経過秒（float）
	/// </returns>
	float GetSeconds()
	{
		return (float)m_elapsed;
	}
	/// <summary>
	/// ラップスタートからの分（時間）を返す
	/// </summary>
	/// <returns>
	/// 経過　分（時間）（float）
	/// </returns>
	float GetMinute()
	{
		return m_elapsed / 60.0f;
	}
	/// <summary>
	/// スタートからの秒を返す
	/// （ラップ関係なしのすべての合計）
	/// </summary>
	/// <returns>
	/// 合計経過秒（float）
	/// </returns>
	float GetAllSeconds()
	{
		return (float)m_Allelapsed;
	}

	/// <summary>	
	/// スタートからの分を返す
	/// （ラップ関係なしのすべての合計）
	/// </summary>
	/// <returns>
	/// 合計経過　分（時間）(float)
	/// </returns>
	float GetAllMinute()
	{
		return (float)m_Allelapsed / 60.0f;
	}
private:
	LONGLONG m_start = 0;
	LONGLONG m_stop = 0;
	LONGLONG m_fleam = 0;
	double m_elapsed = 0;				//経過時間(単位：秒)
	double m_Allelapsed = 0.0;			//すべての経過時間(単位：秒)
};
