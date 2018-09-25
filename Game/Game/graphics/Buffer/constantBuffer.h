#pragma once
#include"GPUBuffer.h"
class constantBuffer:public GPUBuffer
{
public:
	constantBuffer();
	~constantBuffer();
	/*!
	*@brief ConstantBufferを作成。
	*@param[in]	pInitData		初期データ。
	*@param[in]	bufferSize		バッファサイズ。
	*/
	bool Create(const void* pInitData, int bufferSize);
};

