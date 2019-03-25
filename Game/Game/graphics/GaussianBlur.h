#pragma once

class PostEffect;
class GaussianBlur:public Noncopyable
{
public:
	GaussianBlur();
	~GaussianBlur();
	/// <summary>
	/// 初期化
	/// </summary>
	void Init(ID3D11ShaderResourceView* tex,float blurIntensity);
	/// <summary>
	/// ガウスブラーをかける
	/// </summary>
	void Create(PostEffect& postEffect);
	/// <summary>
	/// ガウスフィルタの重みを更新
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
	Shader m_vsXBlur;							//Xブラー用の頂点シェーダー。
	Shader m_vsYBlur;							//Yブラー用の頂点シェーダー。
	Shader m_psBlur;							//ブラー用のピクセルシェーダー。
	float m_srcTextureWidth;
	float m_srcTextureHeight;
	float m_blurIntensity;
	bool m_isInited;
	constantBuffer ka;
	RenderTarget m_downSamplingRT[2];			//ブラーをかけるためのダウンサンプリング用のレンダリングターゲット。
};

