#pragma once
#include "RenderTarget.h"
#include "graphics/Shader.h"
#include"GaussianBlur.h"

class PostEffect;
class bloom:public Noncopyable
{
public:
	bloom();
	~bloom();
	/// <summary>
	/// 更新
	/// </summary>
	void Update();
	/// <summary>
	/// 描画
	/// </summary>
	void Draw(PostEffect& postEffect);
private:
	/// <summary>
	/// アルファブレンディングのステートを初期化する。
	/// </summary>
	void InitAlphaBlendState();
	/// <summary>
	/// 定数バッファの初期化。
	/// </summary>
	void InitConstantBuffer();
	/// <summary>
	/// シェーダーを初期化。
	/// </summary>
	void InitShader();
	/// <summary>
	/// レンダリングターゲットの初期化。
	/// </summary>
	void InitRenderTarget();
	/// <summary>
	/// サンプラステートの初期化。
	/// </summary>
	void InitSamplerState();
private:
	static const int NUM_WEIGHTS = 8;
	//カウスフィルタの重みの数。
	/*!
	* @brief	ブラー用のパラメータバッファ。
	*@details
	* これを変更したら、Assets/shader/bloom.fxのCBBlurの中身も変更するように。
	*/
	/// <summary>
	///　ダウンサンプリングの回数
	/// これを変更したら、Assets/shader/bloom.fxのPSCombineに対応するテクスチャデータの数を変更する。
	/// </summary>
	static const int NUM_DOWN_SAMPLE = 4;

	struct SBlurParam {
		CVector4 offset;
		float weights[NUM_WEIGHTS];
	};
	ID3D11SamplerState* m_samplerState = nullptr;		//サンプラステート。
	ID3D11BlendState* m_disableBlendState = nullptr;	//アルファブレンディングを無効にするブレンディングステート。
	ID3D11BlendState* m_finalBlendState = nullptr;		//最終合成用のブレンディングステート。
	RenderTarget m_luminanceRT;			//輝度を抽出するレンダリングターゲット
	RenderTarget m_halfluminanceRT;		//輝度を抽出するテクスチャの半分のレンダリングターゲット。
										//川瀬式ブルームのため。
	Shader m_vs;						//何もしない頂点シェーダー。
	Shader m_psLuminance;				//輝度抽出用のピクセルシェーダー。
	//Shader m_vsXBlur;					//Xブラー用の頂点シェーダー。
	//Shader m_vsYBlur;					//Yブラー用の頂点シェーダー。
	Shader m_psBlur;					//ブラー用のピクセルシェーダー。
	Shader m_psFinal;					//最終合成用のピクセルシェーダー。
	GaussianBlur m_gausianBlur[NUM_DOWN_SAMPLE];
	SBlurParam m_blurParam;				//ブラー用のパラメータ。
	float m_blurDispersion = 50.0f;		//ブラーの分散具合。大きくするほど強く分散する。
	ID3D11Buffer* m_blurParamCB = nullptr;	//ブラーパラメータ用の定数バッファ。
};

