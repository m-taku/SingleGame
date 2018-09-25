#include "stdafx.h"
#include "constantBuffer.h"


constantBuffer::constantBuffer()
{
}


constantBuffer::~constantBuffer()
{
}
/*!
*@brief ConstantBufferを作成。
*@param[in]	pInitData		初期データ。
*@param[in]	bufferSize		バッファサイズ。
*/
bool constantBuffer::Create(const void* pInitData, int bufferSize)
{
	//ConstantBuffer用のバッファ定義を作成する。
	D3D11_BUFFER_DESC bufferDesc;
	ZeroMemory(&bufferDesc, sizeof(bufferDesc));
	bufferDesc.Usage = D3D11_USAGE_DEFAULT;
	bufferDesc.ByteWidth = (((bufferSize - 1) / 16) + 1) * 16;	//16バイトアライメントに切りあげる。
	bufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bufferDesc.CPUAccessFlags = 0;
	return GPUBuffer::Create(pInitData, bufferDesc);
}
