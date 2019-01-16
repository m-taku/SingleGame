#include "stdafx.h"
#include "sprite.h"


sprite::sprite()
{
}


sprite::~sprite()
{
	//m_textureSRV->Release();
	
}	

struct SSimpleVertex {
	CVector4 pos;
	CVector2 tex;
};
void sprite::Init(ID3D11ShaderResourceView* texture, float w, float h)
{
	m_ps.Load("Assets/shader/sprite.fx", "PSMain", Shader::EnType::PS);
	m_vs.Load("Assets/shader/sprite.fx", "VSMain", Shader::EnType::VS);
	sprite_size.x = w;
	sprite_size.y = h;
	half_size.x = sprite_size.x / 2.0f;
	half_size.y = sprite_size.y / 2.0f;
	SSimpleVertex vertex[] = {
		{
			{-half_size.x,half_size.y, 0.0f, 1.0f },{ 0.0f,0.0f }//左上（原点）
		},
        {
			{half_size.x,half_size.y, 0.0f, 1.0f },{ 1.0f,0.0f }//右上
		},
		{
			{half_size.x, -half_size.y, 0.0f, 1.0f },{ 1.0f,1.0f}//右下
		},
		{
			{-half_size.x, -half_size.y, 0.0f, 1.0f},{0.0f,1.0f}//左下
		}
	};


	short indices[] = { 0,2,1,0,3,2 };
	m_date.Create(
		//D3D_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP,
		D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST,
		4,
		sizeof(SSimpleVertex),
		vertex,
		6,
		indexBuffer::enIndexType_16,
		indices
	);

	m_textureSRV = texture;
	m_cb.Create(nullptr, sizeof(SpriteCB));
}
void sprite::Updete(const CVector3& position, const CQuaternion& rot, const CVector3& scale, const CVector2& pivot)
{
	CVector2 Pivot = pivot;
	Pivot.x -= 0.5f;
	Pivot.y -= 0.5f;
	Pivot.x *= -2.0f;
	Pivot.y *= -2.0f;
	CMatrix mPivotTrans;

	mPivotTrans.MakeTranslation(
		{ Pivot.x * half_size.x, Pivot.y * half_size.y, 0.0f }
	);
	CMatrix mTrans, mRot, mScale;
	mTrans.MakeTranslation(position);
	mRot.MakeRotationFromQuaternion(rot);
	mScale.MakeScaling(scale);
	m_world.Mul(mPivotTrans, mScale);
	m_world.Mul(m_world, mRot);
	m_world.Mul(m_world, mTrans);
}

void sprite::Draw(const CMatrix& viewMatrix, const CMatrix& projMatrix)
{

	ID3D11DeviceContext* d3dDeviceContext = g_graphicsEngine->GetD3DDeviceContext();
	
	if (m_textureSRV == nullptr)
	{
		throw;
		return;
	}
	SpriteCB cb;
	cb.S_WVP = m_world;
	cb.S_WVP.Mul(cb.S_WVP, viewMatrix);
	cb.S_WVP.Mul(cb.S_WVP, projMatrix);
	cb.S_mulColor = m_mulColor;
	d3dDeviceContext->UpdateSubresource(m_cb.GetBody(),0,NULL, &cb,0,0);
	d3dDeviceContext->VSSetConstantBuffers(0,1,&(m_cb.GetBody()));
	d3dDeviceContext->PSSetConstantBuffers(0, 1, &(m_cb.GetBody()));
	d3dDeviceContext->PSSetShaderResources(1,1, &m_textureSRV);
	d3dDeviceContext->PSSetShader((ID3D11PixelShader*)m_ps.GetBody(),NULL,0);
	d3dDeviceContext->VSSetShader((ID3D11VertexShader*)m_vs.GetBody(),NULL,0);
	d3dDeviceContext->IASetInputLayout(m_vs.GetInputLayout());
	m_date.Draw(*d3dDeviceContext);
}