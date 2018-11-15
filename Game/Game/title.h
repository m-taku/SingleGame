#pragma once
/// <summary>
/// タイトル表示クラス。
/// </summary>
class title : public Gameobject
{
public:
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
	bool Load();
	/// <summary>
	/// Gameobjectから継承したUpdate関数。
	/// </summary>
	void Update();
	/// <summary>
	/// Gameobjectから継承したpostDraw関数。
	/// </summary>
	void postDraw();
private:
	ShaderResourceView m_texture;							//タイトルの背景のリソース
	sprite m_title_haikei;									//タイトルの背景表示用のインスタンス
	ShaderResourceView m_Texture;							//タイトルの文字部分のリソース
	sprite m_title_moji;									//タイトルの文字部分表示用のインスタンス
	ShaderResourceView m_texturea;							//タイトルのフェイド用のリソース
	sprite m_feid;											//タイトルのフェイド表示用のインスタンス
	float toumei = 0.0f;									//フェイドの度合い
	float la = 0.0f;
};

