#pragma once

class PostEffect;
class GaussianBlur:public Noncopyable
{
public:
	GaussianBlur();
	~GaussianBlur();
	/// <summary>
	/// ������
	/// </summary>
	void Init(ID3D11ShaderResourceView* tex,float blurIntensity);
	/// <summary>
	/// �K�E�X�u���[��������
	/// </summary>
	void Create(PostEffect& postEffect);
	/// <summary>
	/// �K�E�X�t�B���^�̏d�݂��X�V
	/// </summary>
	void UpdateWeights();
	ID3D11ShaderResourceView* GetResultTextureSRV()
	{
		return m_downSamplingRT[1].GetRenderTargetSRV();
	}
private:
	static const int NUM_WEIGHTS = 8;
	struct SBlurParam {
		CVector4 offset;
		float weights[NUM_WEIGHTS];
	};
	SBlurParam m_blurParam;						//
	ID3D11ShaderResourceView* m_srcTextureSRV;	//
	Shader m_vsXBlur;							//X�u���[�p�̒��_�V�F�[�_�[�B
	Shader m_vsYBlur;							//Y�u���[�p�̒��_�V�F�[�_�[�B
	Shader m_psBlur;							//�u���[�p�̃s�N�Z���V�F�[�_�[�B
	float m_srcTextureWidth;
	float m_srcTextureHeight;
	float m_blurIntensity;
	bool m_isInited;
	constantBuffer ka;
	RenderTarget m_downSamplingRT[2];			//�u���[�������邽�߂̃_�E���T���v�����O�p�̃����_�����O�^�[�Q�b�g�B
};

