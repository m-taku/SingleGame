#pragma once
/// <summary>
/// �^�C�g���\���N���X�B
/// </summary>
class title : public Gameobject
{
public:
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
	bool Load();
	/// <summary>
	/// Gameobject����p������Update�֐��B
	/// </summary>
	void Update();
	/// <summary>
	/// Gameobject����p������postDraw�֐��B
	/// </summary>
	void postDraw();
private:
	ShaderResourceView m_texture;							//�^�C�g���̔w�i�̃��\�[�X
	sprite m_title_haikei;									//�^�C�g���̔w�i�\���p�̃C���X�^���X
	ShaderResourceView m_Texture;							//�^�C�g���̕��������̃��\�[�X
	sprite m_title_moji;									//�^�C�g���̕��������\���p�̃C���X�^���X
	ShaderResourceView m_texturea;							//�^�C�g���̃t�F�C�h�p�̃��\�[�X
	sprite m_feid;											//�^�C�g���̃t�F�C�h�\���p�̃C���X�^���X
	float toumei = 0.0f;									//�t�F�C�h�̓x����
	float la = 0.0f;
};

