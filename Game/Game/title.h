#pragma once
#include"Fade.h"
/// <summary>
/// タイトル表示クラス。
/// </summary>
class title : public Gameobject
{
public:	
	/// <summary>
	/// モード選択用のenum
	/// </summary>
	enum mode
	{
		sturt,
		test
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
	/// <summary>
	/// 
	/// </summary>
	void Stop()override;
	/// <summary>
	/// 現在のモードを取得
	/// </summary>
	/// <returns>
	/// モード（enum）
	/// </returns>
	const mode GetMode()const
	{
		return moudo;
	}
private:
	ShaderResourceView m_texture_haikei;					//タイトルの背景のリソース
	sprite m_title_haikei;									//タイトルの背景表示用のインスタンス
	ShaderResourceView m_texture_moji;						//タイトルの文字部分のリソース
	sprite m_title_moji;									//タイトルの文字部分表示用のインスタンス
	ShaderResourceView m_texture_fade;						//タイトルのフェイド用のリソース
	sprite m_fadeSprite;									//タイトルのフェイド表示用のインスタンス
	ShaderResourceView m_texture_yaji;						//タイトルの矢印用のリソース
	sprite m_yajiSprite;									//タイトルの矢印用のインスタンス
	Fade m_fade;											//フェード用のクラス 
	CSoundSource m_bgmA;									//BGM用のクラス
	CVector3 m_pos = { -300.0f,-250.0f,0.0f };				//矢印のポジション
	mode moudo = sturt;										//モードの変数
};

