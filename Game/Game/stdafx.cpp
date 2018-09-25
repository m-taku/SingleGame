#include "stdafx.h"

bool frame(CVector3 position)
{
	CVector4 posInScreen(position);
	//�J����
	CMatrix mView = g_camera3D.GetViewMatrix();
	//�v���W�F�N�V����
	CMatrix mProj = g_camera3D.GetProjectionMatrix();
	//mView*posInScreen
	//�J�����ɕϊ�
	mView.Mul(posInScreen);
	//mproj*posInScreen
	//�X�N���[���H�ɕϊ�
	mProj.Mul(posInScreen);

	//w�����Z����Ɓi1.0�`-1.0�j�͈̔͂̍��W�n�ł���
	posInScreen.x /= posInScreen.w;
	posInScreen.y /= posInScreen.w;
	posInScreen.z /= posInScreen.w;
	if (1.0f < posInScreen.x || -1.0f>posInScreen.x || 2.0f<posInScreen.y || -2.0f>posInScreen.y || posInScreen.z > 1.2f || posInScreen.z < 0.0f)
	{
		return false;
	}
	else {
		return true;
	}
}