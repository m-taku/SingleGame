#pragma once
#include"Fade.h"
/// <summary>
/// タイトル表示クラス。
/// </summary>
class title : public Gameobject
{
public:	
	enum mode
{
	test,
	sturt
};
	/// <summary>
	/// コンストラクタ。
	/// </summary>
	title();
	/// <summary>
	/// デストラクタ。
	/// </summary>
	~title();
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
	/// Gameobjectから継承したpostDraw関数。
	/// </summary>
	void PostDraw() override;
	mode Getmode()
	{
		return moudo;
	}
private:
	ShaderResourceView m_texture_haikei;							//タイトルの背景のリソース
	sprite m_title_haikei;									//タイトルの背景表示用のインスタンス
	ShaderResourceView m_texture_moji;							//タイトルの文字部分のリソース
	sprite m_title_moji;									//タイトルの文字部分表示用のインスタンス
	ShaderResourceView m_texture_fade;							//タイトルのフェイド用のリソース
	sprite m_fadeSprite;									//タイトルのフェイド表示用のインスタンス
	ShaderResourceView m_texture_yaji;							//タイトルの矢印用のリソース
	sprite m_yajiSprite;									//タイトルの矢印用のインスタンス
	CVector3 m_pos = { -300.0f,-250.0f,0.0f };
	mode moudo = test;
	Fade m_fade;
	float m_toumei = 0.0f;									//フェイドの度合い
	float m_faderate = 0.0f;
};

