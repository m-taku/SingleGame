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
	//ソーステクスチャのSRVをコピー。
	m_srcTextureSRV = tex;
	//UpdateWeight関数で使用するので、ブラーの強さをメンバ変数に記憶しておく。
	m_blurIntensity = blurIntensity;
	//ソーステクスチャの情報を取得。
	ID3D11Texture2D* Tex;
	tex->GetResource((ID3D11Resource**)&Tex);
	//取得したテクスチャから、テクスチャ情報を取得する。
	D3D11_TEXTURE2D_DESC texDesc;
	Tex->GetDesc(&texDesc);
	//テクスチャ情報を取得できたので、テクスチャの参照カウンタをおろす。
	Tex->Release();
	//ソーステクスチャの幅と高さを記憶しておく。
	m_srcTextureWidth = texDesc.Width;
	m_srcTextureHeight = texDesc.Height;
	//ブラーをかけるためのダウンサンプリング用のレンダリングターゲットを作成。
	//横ブラー用。
	m_downSamplingRT[0].Create(
		texDesc.Width * 0.5f,	//横の解像度をフレームバッファの半分にする。
		texDesc.Height,
		DXGI_FORMAT_R16G16B16A16_FLOAT
	);
	//縦ブラー用。
	m_downSamplingRT[1].Create(
		texDesc.Width * 0.5f,	//横の解像度をフレームバッファの半分にする。
		texDesc.Height * 0.5f,	//縦の解像度をフレームバッファの半分にする。
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
	//ガウスフィルタの重みを更新する。
	float total = 0;
	for (int i = 0; i < NUM_WEIGHTS; i++) {
		m_blurParam.weights[i] = expf(-0.5f*(float)(i*i) / m_blurIntensity);
		total += 2.0f*m_blurParam.weights[i];
	}
	// 規格化。重みのトータルが1.0になるように、全体の重みで除算している。
	for (int i = 0; i < NUM_WEIGHTS; i++) {
		m_blurParam.weights[i] /= total;
	}
}
void GaussianBlur::Create(PostEffect& postEffect)
{

	if (m_isInited == false) {
		//初期化できてないぞ。
		return;
	}
	//ガウシアンフィルターの重みテーブルを更新する。
	UpdateWeights();
	auto deviceContext = g_graphicsEngine->GetD3DDeviceContext();
	//重みテーブルを更新したので、VRAM上の定数バッファも更新する。
	//メインメモリの内容をVRAMにコピー。
	auto d3d11CbGpu = ka.GetBody();
	deviceContext->UpdateSubresource(
		d3d11CbGpu, 0, nullptr, &m_blurParam, 0, 0);
	//レジスタb0にm_blurCbGpuのアドレスを設定する。
	deviceContext->PSSetConstantBuffers(
		0, 1, &d3d11CbGpu);

	//輝度を抽出したテクスチャにXブラーをかける。
	{
		//Xブラー用のレンダリングターゲットに変更する。
		g_graphicsEngine->ChangeRenderTarget(m_downSamplingRT[0].GetRenderTargetView(), m_downSamplingRT[0].GetDepthStensilView(), m_downSamplingRT[0].GetViewport());

		//輝度テクスチャをt0レジスタに設定する。
		auto luminanceTexSRV = m_srcTextureSRV;
		deviceContext->VSSetShaderResources(0, 1, &luminanceTexSRV);
		deviceContext->PSSetShaderResources(0, 1, &luminanceTexSRV);
		// 定数バッファを更新。
		m_blurParam.offset.x = 16.0f / m_srcTextureWidth;
		m_blurParam.offset.y = 0.0f;
		deviceContext->UpdateSubresource(d3d11CbGpu, 0, nullptr, &m_blurParam, 0, 0);
		//ブラー用の定数バッファを設定する。
		deviceContext->PSSetConstantBuffers(0, 1, &d3d11CbGpu);

		//フルスクリーン描画。
		postEffect.DrawFullScreenQuadPrimitive(deviceContext, m_vsXBlur, m_psBlur);
	}
	//XブラーをかけたテクスチャにYブラーをかける。
	{
		//Yブラー用のレンダリングターゲットに変更する。
		g_graphicsEngine->ChangeRenderTarget(m_downSamplingRT[1].GetRenderTargetView(), m_downSamplingRT[1].GetDepthStensilView(), m_downSamplingRT[1].GetViewport());
		//Xブラーをかけたテクスチャをt0レジスタに設定する。
		auto xBlurSRV = m_downSamplingRT[0].GetRenderTargetSRV();
		deviceContext->VSSetShaderResources(0, 1, &xBlurSRV);
		deviceContext->PSSetShaderResources(0, 1, &xBlurSRV);

		// 定数バッファを更新。
		m_blurParam.offset.x = 0.0f;
		m_blurParam.offset.y = 16.0f / m_srcTextureHeight;
		deviceContext->UpdateSubresource(d3d11CbGpu, 0, nullptr, &m_blurParam, 0, 0);
		//ブラー用の定数バッファを設定する。
		deviceContext->PSSetConstantBuffers(0, 1, &d3d11CbGpu);

		//フルスクリーン描画。
		postEffect.DrawFullScreenQuadPrimitive(deviceContext, m_vsYBlur, m_psBlur);
	}
}