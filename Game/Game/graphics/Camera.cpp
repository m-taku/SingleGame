#include "stdafx.h"
#include "Camera.h"

Camera g_camera3D;		//3Dカメラ。
Camera g_camera2D;		//2Dカメラ。
void Camera::Update()
{
	//ビュー行列を計算。
	m_viewMatrix.MakeLookAt(
		m_position,
		m_target,
		m_up
	);

	//プロジェクション行列を計算。
	if (camera2D) {
		m_projMatrix.MakeOrthoProjectionMatrix(FRAME_BUFFER_W, FRAME_BUFFER_H,m_near,m_far);
	}
	else {
		m_projMatrix.MakeProjectionMatrix(
			m_viewAngle,					//画角。
			FRAME_BUFFER_W / FRAME_BUFFER_H,	//アスペクト比。
			m_near,
			m_far
		);

		auto lo = m_target - m_position;
		m_view_rotation_Matrix.MakeLookAt(
			CVector3::Zero(),
			lo,
			m_up
		);
	}
	//ビュープロジェクション行列の作成。
	m_viewProjectionMatrix.Mul(m_viewMatrix, m_projMatrix);
}