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
	/// Update�֐�
	/// </summary>
	bool Update();
	/// <summary>
	/// Draw�֐�
	/// </summary>
	void Draw();
	/// <summary>
	/// �t�F�[�h�C���ɑJ��
	/// </summary>
	/// <param name="taim">
	/// �t�F�[�h�̂������i1/taim�j
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
	ShaderResourceView m_texture_fade;							//�^�C�g���̃t�F�C�h�p�̃��\�[�X
	sprite m_fadeSprite;										//�^�C�g���̃t�F�C�h�\���p�̃C���X�^���X
	float m_faderate = 0.0f;
	float m_toumei = 0.0f;									//�t�F�C�h�̓x����
	Fade_State m_fadestate = idel;
};

