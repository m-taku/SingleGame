#include "stdafx.h"
#include "EnemyStateAttack.h"
#include"../../Player/Player.h"
#include "Physics/CollisionAttr.h"
#include"Enemy.h"
namespace {
	//���̃T�C�Y�iaabb�p�j(�c�A���A����)
	const CVector3 SWODSIZE = { 10.0f, 10.0f,80.0f };
}
EnemyStateAttack::EnemyStateAttack(Enemy* enamy, Player* player) :EnemyState(enamy, player)
{
	m_boneNo = m_enemy->GetNo();
	CMatrix ka = m_enemy->CopyModel().GetSkeleton().GetBone(m_boneNo)->GetWorldMatrix();
	CVector3 Up;
	center.x = ka.m[3][0];
	center.y = ka.m[3][1];
	center.z = ka.m[3][2];
	Up.x = ka.m[2][0];
	Up.y = ka.m[2][1];
	Up.z = ka.m[2][2];
	Up.Normalize();
	swodaabb2.x = center.x + Up.x*SWODSIZE.z;
	swodaabb2.y = center.y + Up.y*SWODSIZE.z;
	swodaabb2.z = center.z + Up.z*SWODSIZE.z;
	m_debugVecor = new VectorDraw(center);
	swodaabb20 = swodaabb2;
	m_center = center;
	m_enemy->ChangeAnimation(Enemy::attack);
	m_rigidBody = new RigidBody;
}
EnemyStateAttack::~EnemyStateAttack()
{
	delete m_debugVecor;
}
void EnemyStateAttack::Update()
{
	m_enemy->ChangeAnimation(Enemy::attack);
	CMatrix ka = m_enemy->CopyModel().GetSkeleton().GetBone(m_boneNo)->GetWorldMatrix();
	CVector3 Up;
	center.x = ka.m[3][0];
	center.y = ka.m[3][1];
	center.z = ka.m[3][2];
	Up.x = ka.m[2][0];
	Up.y = ka.m[2][1];
	Up.z = ka.m[2][2];
	Up.Normalize();
	CVector3 swodaabb1 = CVector3::Zero();
	swodaabb1.x = center.x + SWODSIZE.x* Up.x;
	swodaabb1.z = center.z + 1 * Up.z;
	swodaabb1.y = center.y + SWODSIZE.y * Up.y;
	swodaabb2.x = center.x + Up.x*SWODSIZE.z/2;
	swodaabb2.y = center.y + Up.y*SWODSIZE.z/2;
	swodaabb2.z = center.z + Up.z*SWODSIZE.z/2;
	//swodaabb2.x = swodaabb2.x - SWODSIZE.x* Up.x;
	//swodaabb2.y = swodaabb2.y - SWODSIZE.y* Up.z;
	auto pu = m_player->Get3Dposition();
	pu.y += 30.0f;
	m_debugVecor->Update(center, Up, 300.0f);
	auto distance = m_player->Get2Dposition() - m_enemy->Get2DPosition();
	m_debugVecor->Draw();
	CollisionTest();
	if (distance.Length() >= 200.0f)
	{
		m_enemy->SetSpeed(500.0f);
		m_enemy->TransitionState(Enemy::State_Move);
	}

}
struct Collision1 : public btCollisionWorld::ConvexResultCallback
{
	bool NextNo = false; //���̔ԍ�

						 //�Փ˂����Ƃ��ɌĂ΂��R�[���o�b�N�֐��B
	virtual	btScalar	addSingleResult(btCollisionWorld::LocalConvexResult& convexResult, bool normalInWorldSpace)
	{
		if (convexResult.m_hitCollisionObject->getUserIndex() != enCollisionAttr_Character) {
			return 0.0f;
		}
		NextNo = true;
		return 0.0f;
	}
};
bool EnemyStateAttack::CollisionTest()
{
	//�X���[�Y����ۂ̉��̓����蔻��i�Œ�l�Ȃ񂾂�Ȃ��A�A�A�A�A�j
	CapsuleCollider m_collide;
	m_collide.Create(SWODSIZE.x, SWODSIZE.z);						//�R���C�_�[�B
	CVector3 Position = center;
	auto hoge= swodaabb20 - m_center;
	auto hoge1 = swodaabb2 - center;
	//���ǂ����t�����Q�{�̃x�N�g��
	hoge.Normalize();
	hoge1.Normalize();	
	CQuaternion Rot = CQuaternion::Identity();
	CVector3 addPos = CVector3::Zero();
	addPos.Subtract(center, m_center);
	if (addPos.Length() < FLT_EPSILON) {
		//�������Ȃ��̂Œ��ׂ���Ȃ��B
		//FLT_EPSILON��1���傫���A�ŏ��̒l�Ƃ̍�����\���萔�B
		//�ƂĂ��������l�̂��Ƃł��B
		return true;
	}
	CVector3 posTmp = center;
	//���C���쐬�B
	btTransform start, end;
	start.setIdentity();
	end.setIdentity();
	//�܂��X�^�[�g�̊p�x���v�Z����B
	float lafrea1 = acos(hoge.Dot(CVector3::AxisY()));
	lafrea1 = CMath::RadToDeg(lafrea1);
	CVector3 jiku1;
	jiku1.Cross(hoge, CVector3::AxisY()*-1);
	if (jiku1.y > 0.0f || jiku1.y < -FLT_MIN)
	{
		jiku1.Normalize();
		Rot.SetRotationDeg(jiku1, lafrea1);
	}
	//�n�_�̓J�v�Z���R���C�_�[�̒��S���W.
	start.setOrigin(btVector3(swodaabb20.x, swodaabb20.y, swodaabb20.z));
	//�n�_�̊p�x��ݒ肷��B
	start.setRotation(btQuaternion(Rot.x, Rot.y, Rot.z, Rot.w));
	//���͏I�_�̈ړ���ݒ�B
	end.setOrigin(btVector3(swodaabb2.x, swodaabb2.y, swodaabb2.z));
	//�n�_�ɑ΂���ړ��p�x�����߂�
	float lafrea = acos(hoge.Dot(hoge1));
	lafrea = CMath::RadToDeg(lafrea);
	CVector3 jiku;
	jiku.Cross(hoge, hoge1);
	if (jiku.y > 0.0f || jiku.y < -FLT_MIN)
	{
		jiku.Normalize();
		CQuaternion hogehoge;
		hogehoge.SetRotationDeg(jiku, lafrea);
		Rot.Multiply(hogehoge);
	}
	//���߂��I�_�p�x��ݒ肷��B
	end.setRotation(btQuaternion(Rot.x, Rot.y, Rot.z, Rot.w));
	//end.setOrigin(btVector3(nextPosition.x, posTmp.y, nextPosition.z));
	Collision1 callback;
	//�Փˌ��o�B
	g_physics.ConvexSweepTest((const btConvexShape*)m_collide.GetBody(), start, end, callback);

	if (callback.NextNo)
	{
		m_player->Damage(1.0f);
	}
	//if (m_rigidBody->GetBody() != NULL) {
	//	g_physics.RemoveRigidBody(*m_rigidBody);
	//	delete m_rigidBody;
	//	m_rigidBody = new RigidBody;
	//}
	//RigidBodyInfo rbInfo;
	//rbInfo.collider = &m_collide;
	//rbInfo.mass = 0.0f;
	//m_rigidBody->Create(rbInfo);
	//btRigidBody* btBody = m_rigidBody->GetBody();
	//btTransform& trans = btBody->getWorldTransform();
	////���̂̈ʒu���X�V�B
	//trans.setOrigin(btVector3(swodaabb2.x, swodaabb2.y, swodaabb2.z));
	//CQuaternion jj;
	//jj.SetRotationDeg(jiku1, lafrea1);
	//trans.setRotation(btQuaternion(jj.x, jj.y, jj.z, jj.w));
	//g_physics.AddRigidBody(*m_rigidBody);
	//�Փ˂������ǂ���
	m_Rot = Rot;
	swodaabb20 = swodaabb2;
	m_center = center;
	return callback.NextNo;
}
