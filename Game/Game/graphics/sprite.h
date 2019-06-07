#pragma once
#include "Shader.h"
#include"SpriteData.h"
#include"Buffer/constantBuffer.h"
class sprite:Noncopyable
{
public:
	struct SpriteCB
	{
		CMatrix S_WVP;
		CVector4 S_mulColor;
	};
	sprite();
	~sprite();
	/// <summary>
	/// ������
	/// </summary>
	/// <param name="texture">
	/// �c�c�r�t�@�C���̃p�X
	/// </param>
	/// <param name="w">
	/// �������̒����i1280�j
	/// </param>
	/// <param name="h">
	/// �c�����̒����i720�j
	/// </param>
	void Init(ID3D11ShaderResourceView* texture, float w, float h);
	/*!
	*@brief	�e�N�X�`���̃n�[�t�T�C�Y�iX�j
	*@return�@float
	*/
	/// <summary>
	/// �e�N�X�`���̃n�[�t�T�C�Y�iX�j
	/// </summary>
	/// <returns>
	/// float
	/// </returns>
	float Gethalf_sizeX()
	{
		return half_size.x;
	}
	/*!
	*@brief	�e�N�X�`���̃n�[�t�T�C�Y�iY�j
	*@return�@float 
	*/
	float Gethalf_sizeY()
	{
		return half_size.y;
	}
	/*
	*@brief	    �A�b�v�f�[�g
	*@param[in]	position		�|�W�V����		    
	*@param[in]	rot				��]
	*@param[in]	scale			�g�嗦
	*@param[in] pivot			�s�{�b�g�u�o0.5��,0.5��}(�����j�v�ς�������Ώ���
										�u{1.0f,0.0f}(�E��)�v
										�u{0.0f,0.0f}(����)�v
										�u{1.0f,1.0f}(�E��)�v		
										�u{0.0f,1.0f}(����)�v
	*/
	void Updete(const CVector3& position, const CQuaternion& rot, const CVector3& scale, const CVector2& pivot = {0.5f,0.5f});
	/*
	*@brief	    �A�b�v�f�[�g
	*@param[in]	position		�|�W�V����
	*@param[in]	rot				��]
	*@param[in]	scale			�g�嗦
	*@param[in] pivot			�s�{�b�g�u�o0.5��,0.5��}(�����j�v�ς�������Ώ���
	�u{1.0f,0.0f}(�E��)�v
	�u{0.0f,0.0f}(����)�v
	�u{1.0f,1.0f}(�E��)�v
	�u{0.0f,1.0f}(����)�v
	*@param[in] scalepivot		�g��Ńs�{�b�g��ς�������Ώ����i��{�s�{�b�g�͂P�j
	*/
	void Updete(const CVector3& position, const CMatrix& rot, const CVector3& scale, const CVector2& pivot = { 0.5f,0.5f });
	/*
	*@brief	    �A�b�v�f�[�g(�g��Ńs�{�b�g��ς������ꍇ�̂݌Ă�ł�������)
	*@param[in]	position		�|�W�V����
	*@param[in]	rot				��]
	*@param[in]	scale			�g�嗦
	*@param[in] scalepivot		�g��ł̃s�{�b�g
	*@param[in] pivot			�s�{�b�g�u�o0.5��,0.5��}(�����j�v�ς�������Ώ���
	�u{1.0f,0.0f}(�E��)�v
	�u{0.0f,0.0f}(����)�v
	�u{1.0f,1.0f}(�E��)�v
	�u{0.0f,1.0f}(����)�v
	*/
	void Updete_2pivots(const CVector3& position, const CMatrix& rot, const CVector3& scale, const CVector2& scalepivot = { 0.5f,0.5f }, const CVector2& pivot = { 0.5f,0.5f });
	/*!
	*@brief	�`��
	*@param[in]	viewMatrix		�r���[�s��B
	*@param[in]	projMatrix		�v���W�F�N�V�����s��B
	*/
	void Draw( const CMatrix& viewMatrix, const CMatrix& projMatrix);
	/*!
	*@brief	�F������ύX
	*@param[in]	clear		�@�F(�q,�f,�a,�����x)
	*/
	void SetMulColor(CVector4 color)
	{
		m_mulColor = color;
	}
	/*!
	*@brief	�����x����������
	*@param[in]	clear		�@�����x�i0.0���`1.0���j
	*/
	void SetclearColor(float clear)
	{
		m_mulColor.w = clear;
	}	
	/*!
	*@brief	�����x����������121312
	*@param[in]	clear		�@�����x�i0.0���`1.0���j
	*/
	void setworld(CMatrix pos)
	{
		m_world.Mul(m_world,pos);
	}
private:
	ID3D11ShaderResourceView*	    m_textureSRV = nullptr;							//!<�e�N�X�`���B
	SpriteData				m_date;
	Shader					m_ps;											//!<�s�N�Z���V�F�[�_�[�B
	Shader					m_vs;											//!<���_�V�F�[�_�[�B
	constantBuffer			m_cb;
	CVector2			    sprite_size;									//!�X�v���C�g�̃T�C�Y�i���A���j
	CVector2				half_size;										//!�X�v���C�g�̃n�[�t�T�C�Y�i��*0.5�A��*0.5�j
	CVector2				m_size = CVector2::Zero();						//!<�T�C�Y�B
	CVector3				m_position = CVector3::Zero();					//!<���W�B
	CVector3				m_scale = CVector3::One();			
	CVector4				m_mulColor = CVector4::White();					//!<��Z�J���[�B
	CQuaternion				m_rotation = CQuaternion::Identity();			//!<��]
	CMatrix					m_world = CMatrix::Identity();					//!<���[���h�s��B		
};

