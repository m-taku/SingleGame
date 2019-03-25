#pragma once
#include"Score.h"
/// <summary>
/// ユーザーインターフェースクラス。
/// </summary>
class UI :public Gameobject
{
public:
	/// <summary>
	/// コンストラクタ。
	/// </summary>
	UI();
	/// <summary>
	/// デストラクタ。
	/// </summary>
	~UI();
	/// <summary>
	/// Gemeobjectから継承したLoat関数。
	/// </summary>
	/// <returns>
	/// 成功でtrue、失敗でfalse。
	/// </returns>
	bool Load() override;
	/// <summary>
	/// Gameobjectから継承したUpdate関数。
	/// </summary>
	void Update() override;
	/// <summary>
	/// Gameobjectから継承したDraw関数。
	/// </summary>
	void Draw() override;
	/// <summary>
	/// Gameobjectから継承したpostDraw関数。
	/// </summary>
	void PostDraw() override;
	/// <summary>
	/// プレイヤーに対するダメージによるゲージの減少処理
	/// </summary>
	/// <param name="damage">
	/// ダメージ量（1.0ｆで死亡）（float）
	/// </param>
	void SetDamage(float damage)
	{
		m_Damage = damage;
	}
	/// <summary>
	/// 残りの体力を取得（0.0ｆ～1.0ｆ）
	/// </summary>
	/// <returns>
	/// 残りの体力（float）
	/// </returns>
	const float GetHP() const
	{
		return m_HP- m_Damage;
	}
	/// <summary>
	/// スコア計算クラスのインスタンスセット
	/// </summary>
	/// <param name="score">
	/// セットしたいインスタンス（Score*）
	/// </param>
	void SetScore(Score* score)
	{
		m_Score = score;
	}
private:
	ShaderResourceView m_Texture_bar_waku;					//HPバーの枠のリソース
	sprite m_HP_bar_waku;									//HPバーの枠の表示用インスタンス
	CVector3 m_HP_waku_position = {-660.0f,-240.0f,0.0f};	//HPバーの枠の画面上の位置
	ShaderResourceView m_Texture_bar;						//HPバーの中身のリソース
	sprite m_HP_bar;										//HPバーの中身の表示用インスタンス
	CVector3 m_HP_position = { -657.0f,-242.0f,0.0f };		//HPバーの中身の画面上の位置
	Score* m_Score = nullptr;								//スコア計算のクラスのインスタンス
	Timer m_timer;											//タイマークラスのインスタンス
	float m_Damage = 0.0f;									//ダメージ量
	Font m_font;											//文字表示のインスタンス
	float m_HP=1.0f;										//残りHP（1で最大）			
};

