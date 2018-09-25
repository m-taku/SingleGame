#pragma once
#include"GPUBuffer.h"
class constantBuffer:public GPUBuffer
{
public:
	constantBuffer();
	~constantBuffer();
	/*!
	*@brief ConstantBuffer���쐬�B
	*@param[in]	pInitData		�����f�[�^�B
	*@param[in]	bufferSize		�o�b�t�@�T�C�Y�B
	*/
	bool Create(const void* pInitData, int bufferSize);
};

