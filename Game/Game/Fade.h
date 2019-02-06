#pragma once
class Fade :public Noncopyable
{
public:
	Fade();
	~Fade();
	enum Fade_State
	{
		fadein,
		fadeout,
		idel
	};
	/// <summary>
	/// Update関数
	/// </summary>
	bool Update();
	/// <summary>
	/// Draw関数
	/// </summary>
	void Draw();
	/// <summary>
	/// フェードインに遷移
	/// </summary>
	/// <param name="taim">
	/// フェードのかかり具合（1/taim）
	/// </param>
	void Fadein(float taim=20.0f)
	{
		m_faderate = 1 / taim;
		m_fadestate = fadein;
	}
	void Fadeout(float taim = 20.0f)
	{
		m_faderate = 1 / taim;
		m_faderate *= -1;
		m_fadestate = fadeout;
	}
	void Fadeidel()
	{
		m_faderate = 0.0f;
		m_fadestate = idel;
	}
	Fade_State GetState()
	{
		return m_fadestate;
	}
private:
	ShaderResourceView m_texture_fade;							//タイトルのフェイド用のリソース
	sprite m_fadeSprite;										//タイトルのフェイド表示用のインスタンス
	float m_faderate = 0.0f;
	float m_toumei = 0.0f;									//フェイドの度合い
	Fade_State m_fadestate = idel;
};

