#pragma once
/*!
 *@brief	�O���t�B�b�N�X�G���W���B
 */
#include"sprite.h"
#include"PostEffect.h"
#include"ShadowMap.h"
class GraphicsEngine
{
public:
	GraphicsEngine();
	~GraphicsEngine();
	/*!
	 *@brief	�������B
	 *@param[in]	hWnd		�E�B���h�E�n���h���B
	 */
	void Init(HWND hWnd);
	/*!
	 *@brief	����B
	 */
	void Release();
	/*!
	 *@brief	D3D11�f�o�C�X���擾�B
	 */
	ID3D11Device* GetD3DDevice()
	{
		return m_pd3dDevice;
	}
	/*!
	 *@brief	D3D11�f�o�C�X�R���e�L�X�g���擾�B
	 */
	ID3D11DeviceContext* GetD3DDeviceContext()
	{
		return m_pd3dDeviceContext;
	}
	/// <summary>
	/// �Q�[���Ńf�t�H���g�̃t�H���g���擾
	/// </summary>
	/// <returns>
	/// �t�H���g�f�[�^�iDirectX::SpriteFont*�j
	/// </returns>
	DirectX::SpriteFont* GetSpriteFont()
	{
		return m_SpriteFont;
	}
	/// <summary>
	/// �t�H���g�\���ɕK�v�ȃN���X���擾
	/// </summary>
	/// <returns>
	/// �t�H���g�\���ɕK�v�ȃN���X�iDirectX::SpriteBatch*�j
	/// </returns>
	DirectX::SpriteBatch* GetSpriteBatch()
	{
		return m_SpriteBatch;
	}
	/// <summary>
	/// �V���h�[�L���X�^�[�̃Z�b�g
	/// </summary>
	/// <param name="model">
	/// �V���h�[�L���X�^�[�ɂ��������f���f�[�^
	/// </param>
	/// <returns>
	/// �m����true
	/// </returns>
	bool SetShadoCaster(SkinModel* model)
	{
		m_shadowmap->RegistShadowCaster(model);
		return true;
	}
	/*!
	 *@brief	�`��J�n�B
	 */
	void BegineRender();
	/*!
	 *@brief	�`��I���B
	 */
	void EndRender();
	/// <summary>
	/// �G�t�F�N�g�̃}�l�[�W���[�N���X�̎擾
	/// </summary>
	/// <returns>
	/// �G�t�F�N�g�̃}�l�[�W���[�N���X�iEffekseer::Manager*�j
	/// </returns>
	Effekseer::Manager* GetEffekseerManager()
	{
		return m_effekseerManager;
	}
	void EffectUpdate()
	{
		//�܂���Effeseer�̍s��^�̕ϐ��ɁA�J�����s��ƃv���W�F�N�V�����s����R�s�[�B
		Effekseer::Matrix44 efCameraMat;
		g_camera3D.GetViewMatrix().CopyTo(efCameraMat);
		Effekseer::Matrix44 efProjMat;
		g_camera3D.GetProjectionMatrix().CopyTo(efProjMat);
		//�J�����s��ƃv���W�F�N�V�����s���ݒ�B
		m_effekseerRenderer->SetCameraMatrix(efCameraMat);
		m_effekseerRenderer->SetProjectionMatrix(efProjMat);
		//Effekseer���X�V�B
		m_effekseerManager->Update(3.0f);
		EffectDraw();
	}
	void EffectDraw()
	{
		//�G�t�F�N�g�͕s�����I�u�W�F�N�g��`�悵����ŕ`�悷��B
		m_effekseerRenderer->BeginRendering();
		m_effekseerManager->Draw();
		m_effekseerRenderer->EndRendering();
	}
	/// <summary>
	/// �e�̍X�V����
	/// </summary>
	void shadoUpdate()
	{
		m_shadowmap->RenderToShadowMap();
		ChangeRenderTarget(
			m_mainTarget.GetRenderTargetView(),
			m_mainTarget.GetDepthStensilView(),
			m_mainTarget.GetViewport());
		float clearColor[] = { 0.0f, 0.0f, 0.0f, 1.0f };
		m_mainTarget.ClearRenderTarget(clearColor);
	}
	/// <summary>
	/// �|�X�g�G�t�F�N�g�̍X�V����
	/// </summary>
	void PostEffectUpdate()
	{
		m_posteffec->Update();
		m_posteffec->Draw();
		ChangeRenderTarget(
			m_frameBufferRenderTargetView,
			m_frameBufferDepthStencilView,
			&m_frameBufferViewports);
		m_mainSRV.Draw(
			g_camera2D.GetViewMatrix(),
			g_camera2D.GetProjectionMatrix()
		);
	}
	/// <summary>
	/// ���C�������_�����O�^�[�Q�b�g�̃Q�b�g
	/// </summary>
	/// <returns>
	/// ���C�������_�����O�^�[�Q�b�g�iRenderTarget*�j
	/// </returns>
	RenderTarget* GetMainRenderTarget()
	{
		return &m_mainTarget;
	}
	/// <summary>
	/// ���X�^���C�U�X�e�[�g�̃Q�b�g
	/// </summary>
	/// <returns>
	/// ���X�^���C�U�X�e�[�g�iID3D11RasterizerState* �j
	/// </returns>
	ID3D11RasterizerState* GetRasterizerState()
	{
		return m_rasterizerState;
	}
	/// <summary>
	/// �V���h�[�}�b�v�̃Q�b�g
	/// </summary>
	/// <returns>
	/// �V���h�[�}�b�v�iShadowMap*�j
	/// </returns>
	ShadowMap* GetShadowMap()
	{
		return m_shadowmap;
	}
	/// <summary>
	///�����_�����O�^�[�Q�b�g�̕ύX 
	/// </summary>
	/// <param name="m_frameBufferRenderTargetView">
	/// �����_�[�^�[�Q�b�g�r���[�iID3D11RenderTargetView*�j
	/// </param>
	/// <param name="m_frameBufferDepthStencilView">
	/// �f�v�X�X�e���V���r���[�iID3D11DepthStencilView*�j
	/// </param>
	/// <param name="m_frameBufferViewports">
	/// �r���[�|�[�g�iD3D11_VIEWPORT*�j
	/// </param>
	void ChangeRenderTarget(ID3D11RenderTargetView* m_frameBufferRenderTargetView,ID3D11DepthStencilView* m_frameBufferDepthStencilView,D3D11_VIEWPORT* m_frameBufferViewports)
	{
		auto d3dDeviceContext = GetD3DDeviceContext();
		ID3D11RenderTargetView* rtTbl[] = {
			m_frameBufferRenderTargetView
		};
		//�����_�����O�^�[�Q�b�g�̐؂�ւ��B
		d3dDeviceContext->OMSetRenderTargets(1, rtTbl, m_frameBufferDepthStencilView);
		if (&m_frameBufferViewports != nullptr) {
			//�r���[�|�[�g���w�肳��Ă�����A�r���[�|�[�g���ύX����B
			d3dDeviceContext->RSSetViewports(1,m_frameBufferViewports);
		}
	}
private:
	D3D_FEATURE_LEVEL		m_featureLevel;				//Direct3D �f�o�C�X�̃^�[�Q�b�g�ƂȂ�@�\�Z�b�g�B
	ID3D11Device*			m_pd3dDevice = NULL;		//D3D11�f�o�C�X�B
	IDXGISwapChain*			m_pSwapChain = NULL;		//�X���b�v�`�F�C���B
	ID3D11DeviceContext*	m_pd3dDeviceContext = NULL;	//D3D11�f�o�C�X�R���e�L�X�g�B
	ID3D11RenderTargetView* m_backBuffer = NULL;		//�o�b�N�o�b�t�@�B
	ID3D11RasterizerState*	m_rasterizerState = NULL;	//���X�^���C�U�X�e�[�g�B
	ID3D11RasterizerState*  m_rasterizer = NULL;		//
	ID3D11Texture2D*		m_depthStencil = NULL;		//�f�v�X�X�e���V���B
	ID3D11DepthStencilView* m_depthStencilView = NULL;	//�f�v�X�X�e���V���r���[�B
	DirectX::SpriteFont*    m_SpriteFont = NULL;		//�Q�[���̃f�t�H���g�̃t�H���g�f�[�^
	DirectX::SpriteBatch*   m_SpriteBatch = NULL;		//�Q�[���̃f�t�H���g�̃t�H���g�\���p�f�[�^
	Effekseer::Manager*	m_effekseerManager = nullptr;					//�G�t�F�N�g�}�l�[�W���[�N���X
	EffekseerRenderer::Renderer*	m_effekseerRenderer = nullptr;		//�G�t�F�N�g�����_���[�N���X
	ShadowMap* m_shadowmap = NULL;										//�V���h�[�}�b�v
	sprite m_mainSRV;													//���C�������_�����O�^�[�Q�b�g��SRV
	PostEffect* m_posteffec = NULL;										//�|�X�g�G�t�F�N�g
	RenderTarget m_mainTarget;											//���C�������_�����O�^�[�Q�b�g
	D3D11_VIEWPORT m_frameBufferViewports;								//�t���[���o�b�t�@�̃r���[�|�[�g�B
	ID3D11RenderTargetView* m_frameBufferRenderTargetView = nullptr;	//�t���[���o�b�t�@�̃����_�����O�^�[�Q�b�g�r���[�B
	ID3D11DepthStencilView* m_frameBufferDepthStencilView = nullptr;	//�t���[���o�b�t�@�̃f�v�X�X�e���V���r���[�B	
};

extern GraphicsEngine* g_graphicsEngine;			//�O���t�B�b�N�X�G���W��