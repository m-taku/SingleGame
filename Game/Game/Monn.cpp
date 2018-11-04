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
	m_model.UpdateWorldMatrix(m_position, m_rotation, CVector3::One());
	//静的物理オブジェクトをメッシュコライダーから作成する。
	//メッシュコライダーを作成。
	m_meshCollider.CreateFromSkinModel(m_model, nullptr);
	//剛体を作成、
	RigidBodyInfo rbInfo;
	rbInfo.collider = &m_meshCollider; //剛体に形状(コライダー)を設定する。
	rbInfo.mass = 0.0f;
	rbInfo.pos = m_position;
	rbInfo.rot = m_rotation;
	m_rigidBody.Create(rbInfo);
	//剛体を物理ワールドに追加する。
	btRigidBody* btBody = m_rigidBody.GetBody();
	//剛体を動かす。
	//btBody->setActivationState(DISABLE_DEACTIVATION);
	btTransform& trans = btBody->getWorldTransform();
	//剛体の位置を更新。
	trans.setOrigin(btVector3(m_position.x, m_position.y, m_position.z));
	trans.setRotation(btQuaternion(m_rotation.x, m_rotation.y, m_rotation.z, m_rotation.w));
	g_physics.AddRigidBody(m_rigidBody);
	return true;
}
void Monn::Update()
{

	auto rod = CQuaternion::Identity();
	rod.SetRotationDeg(CVector3::AxisY(), m_rod);
	m_rotation.Multiply(rod);
	m_model.UpdateWorldMatrix(m_position, m_rotation, CVector3::One());
	m_kaku += fabs(m_rod);
	if (m_kaku >= 90.0f)
	{
		Setkaku();
		m_rod = 0;
		m_kaku = 90;
	}
	btRigidBody* btBody = m_rigidBody.GetBody();
	//剛体を動かす。
	//btBody->setActivationState(DISABLE_DEACTIVATION);
	btTransform& trans = btBody->getWorldTransform();
	//剛体の位置を更新。
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
