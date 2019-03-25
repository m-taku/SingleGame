#pragma once
/*!
 *@brief	グラフィックスエンジン。
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
	 *@brief	初期化。
	 *@param[in]	hWnd		ウィンドウハンドル。
	 */
	void Init(HWND hWnd);
	/*!
	 *@brief	解放。
	 */
	void Release();
	/*!
	 *@brief	D3D11デバイスを取得。
	 */
	ID3D11Device* GetD3DDevice()
	{
		return m_pd3dDevice;
	}
	/*!
	 *@brief	D3D11デバイスコンテキストを取得。
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
	 *@brief	描画開始。
	 */
	void BegineRender();
	/*!
	 *@brief	描画終了。
	 */
	void EndRender();
	//確認したいため絶対直せ
	ID3D11RasterizerState* mrasterizerState()
	{
		return m_rasterizerState;
	}
	Effekseer::Manager* GeteffekseerManager()
	{
		return m_effekseerManager;
	}
	//ID3D11RasterizerState* terizerState()
	//{
	//	return m_rasterizer;
	//}
	void EffectUpdate()
	{
		//まずはEffeseerの行列型の変数に、カメラ行列とプロジェクション行列をコピー。
		Effekseer::Matrix44 efCameraMat;
		g_camera3D.GetViewMatrix().CopyTo(efCameraMat);
		Effekseer::Matrix44 efProjMat;
		g_camera3D.GetProjectionMatrix().CopyTo(efProjMat);
		//カメラ行列とプロジェクション行列を設定。
		m_effekseerRenderer->SetCameraMatrix(efCameraMat);
		m_effekseerRenderer->SetProjectionMatrix(efProjMat);
		//Effekseerを更新。
		m_effekseerManager->Update();
		EffectDraw();
	}
	void EffectDraw()
	{
		//エフェクトは不透明オブジェクトを描画した後で描画する。
		m_effekseerRenderer->BeginRendering();
		m_effekseerManager->Draw();
		m_effekseerRenderer->EndRendering();
	}
	void shadoUpdate()
	{
		m_shadowmap->RenderToShadowMap();
		ChangeRenderTarget(
			mainTarget.GetRenderTargetView(),
			mainTarget.GetDepthStensilView(),
			mainTarget.GetViewport());
		float clearColor[] = { 0.0f, 0.0f, 0.0f, 1.0f };
		mainTarget.ClearRenderTarget(clearColor);
	}
	void PostEffectUpdate()
	{
		m_posteffec->Update();
		m_posteffec->Draw();
		ChangeRenderTarget(
			m_frameBufferRenderTargetView,
			m_frameBufferDepthStencilView,
			&m_frameBufferViewports);
		mainSRV.Draw(
			g_camera2D.GetViewMatrix(),
			g_camera2D.GetProjectionMatrix()
		);
	}
	RenderTarget* GetMainRenderTarget()
	{
		return &mainTarget;
	}
	ShadowMap* GetShadowMap()
	{
		return m_shadowmap;
	}
	void ChangeRenderTarget(ID3D11RenderTargetView* m_frameBufferRenderTargetView,ID3D11DepthStencilView* m_frameBufferDepthStencilView,D3D11_VIEWPORT* m_frameBufferViewports)
	{
		auto d3dDeviceContext = GetD3DDeviceContext();
		ID3D11RenderTargetView* rtTbl[] = {
			m_frameBufferRenderTargetView
		};
		//レンダリングターゲットの切り替え。
		d3dDeviceContext->OMSetRenderTargets(1, rtTbl, m_frameBufferDepthStencilView);
		if (&m_frameBufferViewports != nullptr) {
			//ビューポートが指定されていたら、ビューポートも変更する。
			d3dDeviceContext->RSSetViewports(1,m_frameBufferViewports);
		}
		//m_frameBufferRenderTargetView->Release();
		//m_frameBufferDepthStencilView->Release();
		//float clearColor[] = { 0.0f, 0.0f, 0.0f, 1.0f };
		//Target.ClearRenderTarget(clearColor);
	}
private:
	D3D_FEATURE_LEVEL		m_featureLevel;				//Direct3D デバイスのターゲットとなる機能セット。
	ID3D11Device*			m_pd3dDevice = NULL;		//D3D11デバイス。
	IDXGISwapChain*			m_pSwapChain = NULL;		//スワップチェイン。
	ID3D11DeviceContext*	m_pd3dDeviceContext = NULL;	//D3D11デバイスコンテキスト。
	ID3D11RenderTargetView* m_backBuffer = NULL;		//バックバッファ。
	ID3D11RasterizerState*	m_rasterizerState = NULL;	//ラスタライザステート。
	ID3D11RasterizerState*  m_rasterizer = NULL;
	ID3D11Texture2D*		m_depthStencil = NULL;		//デプスステンシル。
	ID3D11DepthStencilView* m_depthStencilView = NULL;	//デプスステンシルビュー。
	DirectX::SpriteFont*    m_SpriteFont = NULL;
	DirectX::SpriteBatch*   m_SpriteBatch = NULL;


	Effekseer::Manager*	m_effekseerManager = nullptr;
	EffekseerRenderer::Renderer*	m_effekseerRenderer = nullptr;
	
	ShadowMap* m_shadowmap = NULL;
	sprite mainSRV;
	PostEffect* m_posteffec = NULL;
	RenderTarget mainTarget;	
	D3D11_VIEWPORT m_frameBufferViewports;			//フレームバッファのビューポート。
	ID3D11RenderTargetView* m_frameBufferRenderTargetView = nullptr;	//フレームバッファのレンダリングターゲットビュー。
	ID3D11DepthStencilView* m_frameBufferDepthStencilView = nullptr;	//フレームバッファのデプスステンシルビュー。
	ID3D11BlendState* BlendState;  //かかか
};

extern GraphicsEngine* g_graphicsEngine;			//グラフィックスエンジン