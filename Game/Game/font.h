#pragma once
/// <summary>
/// �t�H���g�N���X
/// </summary>
class Font
{
public:
	/// <summary>
	/// �R���X�g���N�^�B
	/// </summary>
	Font();
	/// <summary>
	/// �f�X�g���N�^�B
	/// </summary>
	~Font();
	/// <summary>
	/// �t�H���g��ݒ�B
	/// </summary>
	/// <param name="font">
	/// DirectX::SpriteFont���g�p���ĕύX�B�iDirectX::SpriteFont*�j
	/// </param>
	void SetFont(DirectX::SpriteFont* font)
	{
		m_spriteFont = font;
	}
	/// <summary>
	/// �`��J�n�B
	/// </summary>
	void Begin();
	/// <summary>
	/// �`��I��
	/// </summary>
	/// <remarks>
	/// ���̂܂܂��Ɠ��߂Ȃǂ̐ݒ肪�ύX����Ă܂܂Ȃ̂ŖY�ꂸ�ɌĂяo���Ă��������B
	/// </remarks>
	void end();
	/*!
	* @brief	�`��B
	*@param[in]	text		�\���������e�L�X�g�B
	*@param[in]	trans		���s�ړ��B
	*@param[in]	color		�J���[�B
	*@param[in]	rot			��]�B
	*@param[in]	scale		�g��B
	*@param[in]	pivot		��_�B
	*						0.5, 0.5�ŉ摜�̒��S����_�B
	*						0.0, 0.0�ŉ摜�̍����B
	*						1.0, 1.0�ŉ摜�̉E��B
	*						Unity��uGUI�ɏ����B
	*/
	/// <summary>
	/// �`��B
	/// </summary>
	/// <param name="text">
	/// �\���������e�L�X�g�B
	/// </param>
	/// <param name="position">
	/// �ǂ��ɏo��������
	/// </param>
	/// <param name="color">
	/// �����̐F
	/// </param>
	/// <param name="rotation">
	/// �����̉�]
	/// </param>
	/// <param name="scale">
	/// �傫��
	/// </param>
	/// <param name="pivot">
	/// 2D��łǂ����N�_�ɂ��邩
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
	DirectX::SpriteBatch*	m_spriteBatch = nullptr;	//!<�X�v���C�g�o�b�`�B
	DirectX::SpriteFont*	m_spriteFont = nullptr;		//!<�X�v���C�g�t�H���g�B
	CMatrix m_scaleMat;									//�g��s��
};

