#include "stdafx.h"
#include "Camera.h"

Camera g_camera3D;		//3D�J�����B
Camera g_camera2D;		//2D�J�����B
void Camera::Update()
{
	//�r���[�s����v�Z�B
	m_viewMatrix.MakeLookAt(
		m_position,
		m_target,
		m_up
	);

	//�v���W�F�N�V�����s����v�Z�B
	if (camera2D) {
		m_projMatrix.MakeOrthoProjectionMatrix(FRAME_BUFFER_W, FRAME_BUFFER_H,m_near,m_far);
	}
	else {
		m_projMatrix.MakeProjectionMatrix(
			m_viewAngle,					//��p�B
			FRAME_BUFFER_W / FRAME_BUFFER_H,	//�A�X�y�N�g��B
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
	//�r���[�v���W�F�N�V�����s��̍쐬�B
	m_viewProjectionMatrix.Mul(m_viewMatrix, m_projMatrix);
}