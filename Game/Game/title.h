#pragma once
#include"Fade.h"
/// <summary>
/// �^�C�g���\���N���X�B
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
	/// �R���X�g���N�^�B
	/// </summary>
	title();
	/// <summary>
	/// �f�X�g���N�^�B
	/// </summary>
	~title();
	/// <summary>
	/// Gemeobject����p������Loat�֐��B
	/// </summary>
	/// <returns>
	/// ������true�A���s��false�B
	/// </returns>
	bool Load() override;
	/// <summary>
	/// Gameobject����p������Update�֐��B
	/// </summary>
	void Update() override;
	/// <summary>
	/// Gameobject����p������postDraw�֐��B
	/// </summary>
	void PostDraw() override;
	mode Getmode()
	{
		return moudo;
	}
private:
	ShaderResourceView m_texture_haikei;							//�^�C�g���̔w�i�̃��\�[�X
	sprite m_title_haikei;									//�^�C�g���̔w�i�\���p�̃C���X�^���X
	ShaderResourceView m_texture_moji;							//�^�C�g���̕��������̃��\�[�X
	sprite m_title_moji;									//�^�C�g���̕��������\���p�̃C���X�^���X
	ShaderResourceView m_texture_fade;							//�^�C�g���̃t�F�C�h�p�̃��\�[�X
	sprite m_fadeSprite;									//�^�C�g���̃t�F�C�h�\���p�̃C���X�^���X
	ShaderResourceView m_texture_yaji;							//�^�C�g���̖��p�̃��\�[�X
	sprite m_yajiSprite;									//�^�C�g���̖��p�̃C���X�^���X
	CVector3 m_pos = { -300.0f,-250.0f,0.0f };
	mode moudo = test;
	Fade m_fade;
	float m_toumei = 0.0f;									//�t�F�C�h�̓x����
	float m_faderate = 0.0f;
};

