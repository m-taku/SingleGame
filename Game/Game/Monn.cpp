#include "stdafx.h"
#include "Monn.h"


Monn::Monn()
{
}


Monn::~Monn()
{
	g_physics.RemoveRigidBody(m_rigidBody);
}
bool Monn::Load()
{
/*	wchar_t filePath[256];
	swprintf_s(filePath, L"Assets/modelData/%s.cmo", objData.name);*/
	m_model.Init(L"Assets/modelData/monn1.cmo", 1);
	m_model.UpdateWorldMatrix(m_position, m_rotation,CVector3::One());
	//�ÓI�����I�u�W�F�N�g�����b�V���R���C�_�[����쐬����B
	//���b�V���R���C�_�[���쐬�B
	m_meshCollider.CreateFromSkinModel(m_model, nullptr);
	//���̂��쐬�A
	RigidBodyInfo rbInfo;
	rbInfo.collider = &m_meshCollider; //���̂Ɍ`��(�R���C�_�[)��ݒ肷��B
	rbInfo.mass = 0.0f;
	rbInfo.pos = m_position;
	rbInfo.rot = m_rotation;
	m_rigidBody.Create(rbInfo);
	//���̂𕨗����[���h�ɒǉ�����B
	btRigidBody* btBody = m_rigidBody.GetBody();
	//���̂𓮂����B
	//btBody->setActivationState(DISABLE_DEACTIVATION);
	btTransform& trans = btBody->getWorldTransform();
	//���̂̈ʒu���X�V�B
	trans.setOrigin(btVector3(m_position.x, m_position.y, m_position.z));
	trans.setRotation(btQuaternion(m_rotation.x, m_rotation.y, m_rotation.z, m_rotation.w));
	g_physics.AddRigidBody(m_rigidBody);
	return true;
}
void Monn::Update()
{
	//�Ƃ肠�����{�^���ŊJ��
	if (g_pad[0].IsTrigger(enButtonB)&& m_rod==0.0f)
	{
		m_rod = 2.0f;
		Setkaku();
	}
	auto rod = CQuaternion::Identity();
	rod.SetRotationDeg(CVector3::AxisY(), m_rod);
	m_rotation.Multiply(rod);
	m_model.UpdateWorldMatrix(m_position, m_rotation, CVector3::One());
	m_kaku += fabs(m_rod);
	//�J������i������j�܂ŉ������
	if (m_kaku >= 90.0f)
	{
		//��]���I������
		m_rod = 0.0f; 
		m_kaku = 0.0f;
	}
	btRigidBody* btBody = m_rigidBody.GetBody();
	//���̂𓮂����B
	btTransform& trans = btBody->getWorldTransform();
	//���̂̈ʒu���X�V�B
	trans.setOrigin(btVector3(m_position.x, m_position.y, m_position.z));
	trans.setRotation(btQuaternion(m_rotation.x, m_rotation.y, m_rotation.z, m_rotation.w));
}
void Monn::Draw()
{
	m_model.Draw(
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix()
	);
}
