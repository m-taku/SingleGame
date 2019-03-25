#pragma once
#include"Fade.h"
class Gameover :public Gameobject
{
public:
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
	/// Gameobjectから継承したDraw関数
	/// </summary>
	void PostDraw() override;
private:
	ShaderResourceView m_texture_font;							//ゲームおーばの文字のリソース
	sprite m_over_font;											//ゲームおーばの文字のインスタンス
	CVector3 m_pos = { 0.0f,1000.0f,0.0f };						//ゲームおーばの文字の位置
	Fade m_fade;												//フェードクラスのインスタンス

};

