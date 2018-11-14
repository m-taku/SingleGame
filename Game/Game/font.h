#pragma once
/// <summary>
/// フォントクラス
/// </summary>
class Font
{
public:
	/// <summary>
	/// コンストラクタ。
	/// </summary>
	Font();
	/// <summary>
	/// デストラクタ。
	/// </summary>
	~Font();
	/// <summary>
	/// フォントを設定。
	/// </summary>
	/// <param name="font">
	/// DirectX::SpriteFontを使用して変更。（DirectX::SpriteFont*）
	/// </param>
	void SetFont(DirectX::SpriteFont* font)
	{
		m_spriteFont = font;
	}
	/// <summary>
	/// 描画開始。
	/// </summary>
	void Begin();
	/// <summary>
	/// 描画終了
	/// </summary>
	/// <remarks>
	/// そのままだと透過などの設定が変更されてままなので忘れずに呼び出してください。
	/// </remarks>
	void end();
	/*!
	* @brief	描画。
	*@param[in]	text		表示したいテキスト。
	*@param[in]	trans		平行移動。
	*@param[in]	color		カラー。
	*@param[in]	rot			回転。
	*@param[in]	scale		拡大。
	*@param[in]	pivot		基点。
	*						0.5, 0.5で画像の中心が基点。
	*						0.0, 0.0で画像の左下。
	*						1.0, 1.0で画像の右上。
	*						UnityのuGUIに準拠。
	*/
	/// <summary>
	/// 描画。
	/// </summary>
	/// <param name="text">
	/// 表示したいテキスト。
	/// </param>
	/// <param name="position">
	/// どこに出したいか
	/// </param>
	/// <param name="color">
	/// 文字の色
	/// </param>
	/// <param name="rotation">
	/// 文字の回転
	/// </param>
	/// <param name="scale">
	/// 大きさ
	/// </param>
	/// <param name="pivot">
	/// 2D上でどこを起点にするか
	/// </param>
	void Draw(
		wchar_t const* text,
		const CVector2& position,
		const CVector4& color = CVector4::White(),
		float rotation = 0.0f,
		float scale = 1.0f,
		CVector2 pivot = { 0.5f, 0.5f }
	);
private:
	DirectX::SpriteBatch*	m_spriteBatch = nullptr;	//!<スプライトバッチ。
	DirectX::SpriteFont*	m_spriteFont = nullptr;		//!<スプライトフォント。
	CMatrix m_scaleMat;									//拡大行列
};

