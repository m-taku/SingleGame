#pragma once
#include"Fade.h"
/// <summary>
/// �^�C�g���\���N���X�B
/// </summary>
class title : public Gameobject
{
public:	
	/// <summary>
	/// ���[�h�I��p��enum
	/// </summary>
	enum mode
	{
		sturt,
		test
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
	/// <summary>
	/// 
	/// </summary>
	void Stop()override;
	/// <summary>
	/// ���݂̃��[�h���擾
	/// </summary>
	/// <returns>
	/// ���[�h�ienum�j
	/// </returns>
	const mode GetMode()const
	{
		return moudo;
	}
private:
	ShaderResourceView m_texture_haikei;					//�^�C�g���̔w�i�̃��\�[�X
	sprite m_title_haikei;									//�^�C�g���̔w�i�\���p�̃C���X�^���X
	ShaderResourceView m_texture_moji;						//�^�C�g���̕��������̃��\�[�X
	sprite m_title_moji;									//�^�C�g���̕��������\���p�̃C���X�^���X
	ShaderResourceView m_texture_fade;						//�^�C�g���̃t�F�C�h�p�̃��\�[�X
	sprite m_fadeSprite;									//�^�C�g���̃t�F�C�h�\���p�̃C���X�^���X
	ShaderResourceView m_texture_yaji;						//�^�C�g���̖��p�̃��\�[�X
	sprite m_yajiSprite;									//�^�C�g���̖��p�̃C���X�^���X
	Fade m_fade;											//�t�F�[�h�p�̃N���X 
	CSoundSource m_bgmA;									//BGM�p�̃N���X
	CVector3 m_pos = { -300.0f,-250.0f,0.0f };				//���̃|�W�V����
	mode moudo = sturt;										//���[�h�̕ϐ�
};

