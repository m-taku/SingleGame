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
	/// <summary>
	/// ゲームでデフォルトのフォントを取得
	/// </summary>
	/// <returns>
	/// フォントデータ（DirectX::SpriteFont*）
	/// </returns>
	DirectX::SpriteFont* GetSpriteFont()
	{
		return m_SpriteFont;
	}
	/// <summary>
	/// フォント表示に必要なクラスを取得
	/// </summary>
	/// <returns>
	/// フォント表示に必要なクラス（DirectX::SpriteBatch*）
	/// </returns>
	DirectX::SpriteBatch* GetSpriteBatch()
	{
		return m_SpriteBatch;
	}
	/// <summary>
	/// シャドーキャスターのセット
	/// </summary>
	/// <param name="model">
	/// シャドーキャスターにしたいモデルデータ
	/// </param>
	/// <returns>
	/// 確実にtrue
	/// </returns>
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
	/// <summary>
	/// エフェクトのマネージャークラスの取得
	/// </summary>
	/// <returns>
	/// エフェクトのマネージャークラス（Effekseer::Manager*）
	/// </returns>
	Effekseer::Manager* GetEffekseerManager()
	{
		return m_effekseerManager;
	}
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
		m_effekseerManager->Update(3.0f);
		EffectDraw();
	}
	void EffectDraw()
	{
		//エフェクトは不透明オブジェクトを描画した後で描画する。
		m_effekseerRenderer->BeginRendering();
		m_effekseerManager->Draw();
		m_effekseerRenderer->EndRendering();
	}
	/// <summary>
	/// 影の更新処理
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
	/// ポストエフェクトの更新処理
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
	/// メインレンダリングターゲットのゲット
	/// </summary>
	/// <returns>
	/// メインレンダリングターゲット（RenderTarget*）
	/// </returns>
	RenderTarget* GetMainRenderTarget()
	{
		return &m_mainTarget;
	}
	/// <summary>
	/// ラスタライザステートのゲット
	/// </summary>
	/// <returns>
	/// ラスタライザステート（ID3D11RasterizerState* ）
	/// </returns>
	ID3D11RasterizerState* GetRasterizerState()
	{
		return m_rasterizerState;
	}
	/// <summary>
	/// シャドーマップのゲット
	/// </summary>
	/// <returns>
	/// シャドーマップ（ShadowMap*）
	/// </returns>
	ShadowMap* GetShadowMap()
	{
		return m_shadowmap;
	}
	/// <summary>
	///レンダリングターゲットの変更 
	/// </summary>
	/// <param name="m_frameBufferRenderTargetView">
	/// レンダーターゲットビュー（ID3D11RenderTargetView*）
	/// </param>
	/// <param name="m_frameBufferDepthStencilView">
	/// デプスステンシルビュー（ID3D11DepthStencilView*）
	/// </param>
	/// <param name="m_frameBufferViewports">
	/// ビューポート（D3D11_VIEWPORT*）
	/// </param>
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
	}
private:
	D3D_FEATURE_LEVEL		m_featureLevel;				//Direct3D デバイスのターゲットとなる機能セット。
	ID3D11Device*			m_pd3dDevice = NULL;		//D3D11デバイス。
	IDXGISwapChain*			m_pSwapChain = NULL;		//スワップチェイン。
	ID3D11DeviceContext*	m_pd3dDeviceContext = NULL;	//D3D11デバイスコンテキスト。
	ID3D11RenderTargetView* m_backBuffer = NULL;		//バックバッファ。
	ID3D11RasterizerState*	m_rasterizerState = NULL;	//ラスタライザステート。
	ID3D11RasterizerState*  m_rasterizer = NULL;		//
	ID3D11Texture2D*		m_depthStencil = NULL;		//デプスステンシル。
	ID3D11DepthStencilView* m_depthStencilView = NULL;	//デプスステンシルビュー。
	DirectX::SpriteFont*    m_SpriteFont = NULL;		//ゲームのデフォルトのフォントデータ
	DirectX::SpriteBatch*   m_SpriteBatch = NULL;		//ゲームのデフォルトのフォント表示用データ
	Effekseer::Manager*	m_effekseerManager = nullptr;					//エフェクトマネージャークラス
	EffekseerRenderer::Renderer*	m_effekseerRenderer = nullptr;		//エフェクトレンダラークラス
	ShadowMap* m_shadowmap = NULL;										//シャドーマップ
	sprite m_mainSRV;													//メインレンダリングターゲットのSRV
	PostEffect* m_posteffec = NULL;										//ポストエフェクト
	RenderTarget m_mainTarget;											//メインレンダリングターゲット
	D3D11_VIEWPORT m_frameBufferViewports;								//フレームバッファのビューポート。
	ID3D11RenderTargetView* m_frameBufferRenderTargetView = nullptr;	//フレームバッファのレンダリングターゲットビュー。
	ID3D11DepthStencilView* m_frameBufferDepthStencilView = nullptr;	//フレームバッファのデプスステンシルビュー。	
};

extern GraphicsEngine* g_graphicsEngine;			//グラフィックスエンジン