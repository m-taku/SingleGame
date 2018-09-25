#include "stdafx.h"

bool frame(CVector3 position)
{
	CVector4 posInScreen(position);
	//カメラ
	CMatrix mView = g_camera3D.GetViewMatrix();
	//プロジェクション
	CMatrix mProj = g_camera3D.GetProjectionMatrix();
	//mView*posInScreen
	//カメラに変換
	mView.Mul(posInScreen);
	//mproj*posInScreen
	//スクリーン？に変換
	mProj.Mul(posInScreen);

	//wを除算すると（1.0～-1.0）の範囲の座標系できる
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