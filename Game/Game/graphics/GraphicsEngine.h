#pragma once
/*!
 *@brief	グラフィックスエンジン。
 */
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
		//レンダリングターゲットの切り替え。
		d3dDeviceContext->OMSetRenderTargets(1, rtTbl, m_frameBufferDepthStencilView);
		if (&m_frameBufferViewports != nullptr) {
			//ビューポートが指定されていたら、ビューポートも変更する。
			d3dDeviceContext->RSSetViewports(1, &m_frameBufferViewports);
		}
		m_frameBufferRenderTargetView->Release();
		m_frameBufferDepthStencilView->Release();
		float clearColor[] = { 0.0f, 0.0f, 0.0f, 1.0f };
		Target.ClearRenderTarget(clearColor);
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
	ShadowMap* m_shadowmap = NULL;
	RenderTarget Target;	
	D3D11_VIEWPORT m_frameBufferViewports;			//フレームバッファのビューポート。
	ID3D11RenderTargetView* m_frameBufferRenderTargetView = nullptr;	//フレームバッファのレンダリングターゲットビュー。
	ID3D11DepthStencilView* m_frameBufferDepthStencilView = nullptr;	//フレームバッファのデプスステンシルビュー。
};

extern GraphicsEngine* g_graphicsEngine;			//グラフィックスエンジン