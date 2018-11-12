#pragma once
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
	bool Load();
	/// <summary>
	/// Gameobjectから継承したUpdate関数。
	/// </summary>
	void Update();
	/// <summary>
	/// Gameobjectから継承したDraw関数。
	/// </summary>
	void Draw();
	/// <summary>
	/// Gameobjectから継承したpostDraw関数。
	/// </summary>
	void postDraw();
	/// <summary>
	/// プレイヤーに対するダメージによるゲージの減少処理
	/// </summary>
	/// <param name="damage">
	/// ダメージ量（1.0ｆで死亡）（float）
	/// </param>
	void SetDamage(float damage)
	{
		m_Damage += damage;
	}
	/// <summary>
	/// 残りの体力を取得（0.0ｆ～1.0ｆ）
	/// </summary>
	/// <returns>
	/// 残りの体力（float）
	/// </returns>
	float GetHP()
	{
		return m_HP;
	}
private:
	ShaderResourceView texture;												//HPバーの枠のリソース
	sprite HP_bar_waku;														//HPバーの枠の表示用インスタンス
	CVector3 m_HP_waku_position = {-640.0f,-240.0f,0.0f};					//HPバーの枠の画面上の位置
	ShaderResourceView Texture;												//HPバーの中身のリソース
	sprite HP_bar;															//HPバーの中身の表示用インスタンス
	CVector3 m_HP_position = { -637.0f,-242.0f,0.0f };						//HPバーの中身の画面上の位置
	float m_Damage = 0.0f;													//ダメージ量
	float m_HP=1.0f;														//残りHP			

};

