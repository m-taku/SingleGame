#pragma once
/*!
 *@brief	�O���t�B�b�N�X�G���W���B
 */
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
	DirectX::SpriteFont* GetSpriteFont()
	{
		return m_SpriteFont;
	}
	DirectX::SpriteBatch* GetSpriteBatch()
	{
		return m_SpriteBatch;
	}
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
	//�m�F���������ߐ�Β���
	ID3D11RasterizerState* mrasterizerState()
	{
		return m_rasterizerState;
	}
	//ID3D11RasterizerState* terizerState()
	//{
	//	return m_rasterizer;
	//}
	void shadoUpdate()
	{
		m_shadowmap->RenderToShadowMap();
		ka();
	}
	ShadowMap* GetShadowMap()
	{
		return m_shadowmap;
	}
	void ka()
	{
		auto d3dDeviceContext = GetD3DDeviceContext();
		ID3D11RenderTargetView* rtTbl[] = {
			m_frameBufferRenderTargetView
		};
		//�����_�����O�^�[�Q�b�g�̐؂�ւ��B
		d3dDeviceContext->OMSetRenderTargets(1, rtTbl, m_frameBufferDepthStencilView);
		if (&m_frameBufferViewports != nullptr) {
			//�r���[�|�[�g���w�肳��Ă�����A�r���[�|�[�g���ύX����B
			d3dDeviceContext->RSSetViewports(1, &m_frameBufferViewports);
		}
		m_frameBufferRenderTargetView->Release();
		m_frameBufferDepthStencilView->Release();
		float clearColor[] = { 0.0f, 0.0f, 0.0f, 1.0f };
		Target.ClearRenderTarget(clearColor);
	}
private:
	D3D_FEATURE_LEVEL		m_featureLevel;				//Direct3D �f�o�C�X�̃^�[�Q�b�g�ƂȂ�@�\�Z�b�g�B
	ID3D11Device*			m_pd3dDevice = NULL;		//D3D11�f�o�C�X�B
	IDXGISwapChain*			m_pSwapChain = NULL;		//�X���b�v�`�F�C���B
	ID3D11DeviceContext*	m_pd3dDeviceContext = NULL;	//D3D11�f�o�C�X�R���e�L�X�g�B
	ID3D11RenderTargetView* m_backBuffer = NULL;		//�o�b�N�o�b�t�@�B
	ID3D11RasterizerState*	m_rasterizerState = NULL;	//���X�^���C�U�X�e�[�g�B
	ID3D11RasterizerState*  m_rasterizer = NULL;
	ID3D11Texture2D*		m_depthStencil = NULL;		//�f�v�X�X�e���V���B
	ID3D11DepthStencilView* m_depthStencilView = NULL;	//�f�v�X�X�e���V���r���[�B
	DirectX::SpriteFont*    m_SpriteFont = NULL;
	DirectX::SpriteBatch*   m_SpriteBatch = NULL;
	ShadowMap* m_shadowmap = NULL;
	RenderTarget Target;	
	D3D11_VIEWPORT m_frameBufferViewports;			//�t���[���o�b�t�@�̃r���[�|�[�g�B
	ID3D11RenderTargetView* m_frameBufferRenderTargetView = nullptr;	//�t���[���o�b�t�@�̃����_�����O�^�[�Q�b�g�r���[�B
	ID3D11DepthStencilView* m_frameBufferDepthStencilView = nullptr;	//�t���[���o�b�t�@�̃f�v�X�X�e���V���r���[�B
};

extern GraphicsEngine* g_graphicsEngine;			//�O���t�B�b�N�X�G���W��