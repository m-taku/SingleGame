#pragma once
#include "Shader.h"
#include"SpriteData.h"
#include"Buffer/constantBuffer.h"
class sprite:Noncopyable
{
public:
	struct SpriteCB
	{
		CMatrix S_WVP;
		CVector4 S_mulColor;
	};
	sprite();
	~sprite();
	/*!
	*@brief	初期化
	*@param[in]	texFilePath		ＤＤＳファイルのパス
	*@param[in]	w				横方向の長さ（1280）
	*@param[in]	h				縦方向の長さ（720）
	*/
	void Init(ShaderResourceView* texture, float w, float h);

	float Gethalf_sizeX()
	{
		return half_size.x;
	}
	float Gethalf_sizeY()
	{
		return half_size.y;
	}
	/*
	*@brief	    アップデート
	*@param[in]	position		ポジション		    
	*@param[in]	rot				回転
	*@param[in]	scale			拡大率
	*@param[in] pivot			ピボット「｛0.5ｆ,0.5ｆ}(中央）」変えたければ書く
										「{1.0f,0.0f}(右下)」
										「{0.0f,0.0f}(左下)」
										「{1.0f,1.0f}(右上)」		
										「{0.0f,1.0f}(左上)」
	*/
	void Updete(const CVector3& position, const CQuaternion& rot, const CVector3& scale, const CVector2& pivot = {0.5f,0.5f});
	/*!
	*@brief	描画
	*@param[in]	viewMatrix		ビュー行列。
	*@param[in]	projMatrix		プロジェクション行列。
	*/
	void Draw( const CMatrix& viewMatrix, const CMatrix& projMatrix);
	/*!
	*@brief	色合いを変更
	*@param[in]	clear		　色(Ｒ,Ｇ,Ｂ,透明度)
	*/
	void SetMulColor(CVector4 color)
	{
		m_mulColor = color;
	}
	/*!
	*@brief	透明度だけいじる
	*@param[in]	clear		　透明度（0.0ｆ～1.0ｆ）
	*/
	void SetclearColor(float clear)
	{
		m_mulColor.w = clear;
	}
private:
	Shader m_ps;															//!<ピクセルシェーダー。
	Shader m_vs;															//!<頂点シェーダー。
	SpriteData m_date;
	CVector2 sprite_size;													//!スプライトのサイズ（ｘ、ｙ）
	CVector2 half_size;														//!スプライトのハーフサイズ（ｘ*0.5、ｙ*0.5）
	CVector3				m_position = CVector3::Zero();					//!<座標。
	CQuaternion				m_rotation = CQuaternion::Identity();			//!<回転
	CVector3				m_scale = CVector3::One();
	CMatrix					m_world = CMatrix::Identity();					//!<ワールド行列。					
	CVector4				m_mulColor = CVector4::White();					//!<乗算カラー。
	ShaderResourceView*	    m_textureSRV = nullptr;							//!<テクスチャ。
	constantBuffer			m_cb;

	CVector2				m_size = CVector2::Zero();						//!<サイズ。
};

