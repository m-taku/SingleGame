#pragma once
#include"Fade.h"
class Gameover :public Gameobject
{
public:
	Gameover();
	~Gameover();
	/// <summary>
	/// Gemeobject����p������Loat�֐��B
	/// </summary>
	/// <returns>
	/// ������true�A���s��false�B
	/// </returns>
	bool Load() override;
	/// <summary>
	/// Gameobject����p������Update�֐�
	/// </summary>
	void Update() override;
	/// <summary>
	/// Gameobject����p������Draw�֐�
	/// </summary>
	void PostDraw() override;
private:
	ShaderResourceView m_texture_font;							//�Q�[�����[�΂̕����̃��\�[�X
	sprite m_over_font;									//�Q�[�����[�΂̕����̃C���X�^���X
	CVector3 m_pos = { 0.0f,1000.0f,0.0f };
	Fade m_fade;

};

