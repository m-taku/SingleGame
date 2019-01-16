#include "stdafx.h"
#include "GaussianBlur.h"
#include "PostEffect.h"


GaussianBlur::GaussianBlur()
{
}


GaussianBlur::~GaussianBlur()
{
}
void GaussianBlur::Init(ID3D11ShaderResourceView* tex,float  blurIntensity)
{
	//�\�[�X�e�N�X�`����SRV���R�s�[�B
	m_srcTextureSRV = tex;
	//UpdateWeight�֐��Ŏg�p����̂ŁA�u���[�̋����������o�ϐ��ɋL�����Ă����B
	m_blurIntensity = blurIntensity;
	//�\�[�X�e�N�X�`���̏����擾�B
	ID3D11Texture2D* Tex;
	tex->GetResource((ID3D11Resource**)&Tex);
	//�擾�����e�N�X�`������A�e�N�X�`�������擾����B
	D3D11_TEXTURE2D_DESC texDesc;
	Tex->GetDesc(&texDesc);
	//�e�N�X�`�������擾�ł����̂ŁA�e�N�X�`���̎Q�ƃJ�E���^�����낷�B
	Tex->Release();
	//�\�[�X�e�N�X�`���̕��ƍ������L�����Ă����B
	m_srcTextureWidth = texDesc.Width;
	m_srcTextureHeight = texDesc.Height;
	//�u���[�������邽�߂̃_�E���T���v�����O�p�̃����_�����O�^�[�Q�b�g���쐬�B
	//���u���[�p�B
	m_downSamplingRT[0].Create(
		texDesc.Width * 0.5f,	//���̉𑜓x���t���[���o�b�t�@�̔����ɂ���B
		texDesc.Height,
		DXGI_FORMAT_R16G16B16A16_FLOAT
	);
	//�c�u���[�p�B
	m_downSamplingRT[1].Create(
		texDesc.Width * 0.5f,	//���̉𑜓x���t���[���o�b�t�@�̔����ɂ���B
		texDesc.Height * 0.5f,	//�c�̉𑜓x���t���[���o�b�t�@�̔����ɂ���B
		DXGI_FORMAT_R16G16B16A16_FLOAT
	);
	m_vsXBlur.Load("Assets/shader/bloom.fx", "VSXBlur", Shader::EnType::VS);
	m_vsYBlur.Load("Assets/shader/bloom.fx", "VSYBlur", Shader::EnType::VS);
	m_psBlur.Load("Assets/shader/bloom.fx", "PSBlur", Shader::EnType::PS);
	ka.Create(nullptr,sizeof(SBlurParam));
	m_isInited = true;
}
void GaussianBlur::UpdateWeights()
{
	//�K�E�X�t�B���^�̏d�݂��X�V����B
	float total = 0;
	for (int i = 0; i < NUM_WEIGHTS; i++) {
		m_blurParam.weights[i] = expf(-0.5f*(float)(i*i) / m_blurIntensity);
		total += 2.0f*m_blurParam.weights[i];
	}
	// �K�i���B�d�݂̃g�[�^����1.0�ɂȂ�悤�ɁA�S�̂̏d�݂ŏ��Z���Ă���B
	for (int i = 0; i < NUM_WEIGHTS; i++) {
		m_blurParam.weights[i] /= total;
	}
}
void GaussianBlur::Create(PostEffect& postEffect)
{

	if (m_isInited == false) {
		//�������ł��ĂȂ����B
		return;
	}
	//�K�E�V�A���t�B���^�[�̏d�݃e�[�u�����X�V����B
	UpdateWeights();
	auto deviceContext = g_graphicsEngine->GetD3DDeviceContext();
	//�d�݃e�[�u�����X�V�����̂ŁAVRAM��̒萔�o�b�t�@���X�V����B
	//���C���������̓��e��VRAM�ɃR�s�[�B
	auto d3d11CbGpu = ka.GetBody();
	deviceContext->UpdateSubresource(
		d3d11CbGpu, 0, nullptr, &m_blurParam, 0, 0);
	//���W�X�^b0��m_blurCbGpu�̃A�h���X��ݒ肷��B
	deviceContext->PSSetConstantBuffers(
		0, 1, &d3d11CbGpu);

	//�P�x�𒊏o�����e�N�X�`����X�u���[��������B
	{
		//X�u���[�p�̃����_�����O�^�[�Q�b�g�ɕύX����B
		g_graphicsEngine->ChangeRenderTarget(m_downSamplingRT[0].GetRenderTargetView(), m_downSamplingRT[0].GetDepthStensilView(), m_downSamplingRT[0].GetViewport());

		//�P�x�e�N�X�`����t0���W�X�^�ɐݒ肷��B
		auto luminanceTexSRV = m_srcTextureSRV;
		deviceContext->VSSetShaderResources(0, 1, &luminanceTexSRV);
		deviceContext->PSSetShaderResources(0, 1, &luminanceTexSRV);
		// �萔�o�b�t�@���X�V�B
		m_blurParam.offset.x = 16.0f / m_srcTextureWidth;
		m_blurParam.offset.y = 0.0f;
		deviceContext->UpdateSubresource(d3d11CbGpu, 0, nullptr, &m_blurParam, 0, 0);
		//�u���[�p�̒萔�o�b�t�@��ݒ肷��B
		deviceContext->PSSetConstantBuffers(0, 1, &d3d11CbGpu);

		//�t���X�N���[���`��B
		postEffect.DrawFullScreenQuadPrimitive(deviceContext, m_vsXBlur, m_psBlur);
	}
	//X�u���[���������e�N�X�`����Y�u���[��������B
	{
		//Y�u���[�p�̃����_�����O�^�[�Q�b�g�ɕύX����B
		g_graphicsEngine->ChangeRenderTarget(m_downSamplingRT[1].GetRenderTargetView(), m_downSamplingRT[1].GetDepthStensilView(), m_downSamplingRT[1].GetViewport());
		//X�u���[���������e�N�X�`����t0���W�X�^�ɐݒ肷��B
		auto xBlurSRV = m_downSamplingRT[0].GetRenderTargetSRV();
		deviceContext->VSSetShaderResources(0, 1, &xBlurSRV);
		deviceContext->PSSetShaderResources(0, 1, &xBlurSRV);

		// �萔�o�b�t�@���X�V�B
		m_blurParam.offset.x = 0.0f;
		m_blurParam.offset.y = 16.0f / m_srcTextureHeight;
		deviceContext->UpdateSubresource(d3d11CbGpu, 0, nullptr, &m_blurParam, 0, 0);
		//�u���[�p�̒萔�o�b�t�@��ݒ肷��B
		deviceContext->PSSetConstantBuffers(0, 1, &d3d11CbGpu);

		//�t���X�N���[���`��B
		postEffect.DrawFullScreenQuadPrimitive(deviceContext, m_vsYBlur, m_psBlur);
	}
}