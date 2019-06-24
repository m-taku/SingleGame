#pragma once
#include"Fade.h"
class Score;
class Gameover :public Gameobject
{
public:
	enum ScoreDoaw
	{
		start,
		toubatu,
		nokorijikann,
		stop
	};
	/// <summary>
	/// コンストラクタ
	/// </summary>
	Gameover();
	/// <summary>
	/// デストラクタ
	/// </summary>
	~Gameover();
	/// <summary>
	/// Gemeobjectから継承したLoat関数。
	/// </summary>
	/// <returns>
	/// 成功でtrue、失敗でfalse。
	/// </returns>
	bool Load() override;
	/// <summary>
	/// Gameobjectから継承したUpdate関数
	/// </summary>
	void Update() override;
	/// <summary>
	/// 
	/// </summary>
	void Stop()override;
	/// <summary>
	/// クリア判定のセット
	/// </summary>
	/// <param name="flag">
	/// クリアでfalse
	/// </param>
	void Setfra(bool flag)
	{
		m_flag = flag;
	}
	/// <summary>
	/// Gameobjectから継承したDraw関数
	/// </summary>
	void PostDraw() override;
	void clear();
private:
	ShaderResourceView m_texture_font;							//ゲームおーばの文字のリソース
	sprite m_over_font;											//ゲームおーばの文字のインスタンス
	CVector3 m_pos = { 0.0f,1000.0f,0.0f };						//ゲームおーばの文字の位置
	Fade m_fade;												//フェードクラスのインスタンス
	bool m_flag;													//クリア判定
	//ここからクリア時のみ使用
	Font* m_font=nullptr;											//文字表示のインスタンス
	Score* m_score = nullptr;
	std::list<wchar_t*> m_scoa;
	ScoreDoaw m_scorenum = start;
	float m_count = 0;
};

