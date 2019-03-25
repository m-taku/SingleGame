#include "stdafx.h"
#include "EnemyStateAttack.h"
#include"../../Player/Player.h"
//#include"../HitObjict.h"
#include "Physics/CollisionAttr.h"
#include"Enemy.h"
namespace {
	//���̃T�C�Y�iaabb�p�j(�c�A���A����)
	const CVector3 SWODSIZE = { 10.0f, 10.0f,80.0f };
}
EnemyStateAttack::EnemyStateAttack(Enemy* enamy, Player* player) :EnemyState(enamy, player)
{
	m_boneNo = m_enemy->GetNo();
}
EnemyStateAttack::~EnemyStateAttack()
{
}
void EnemyStateAttack::Update()
{
	auto distance = m_player->Get2Dposition() - m_enemy->Get2DPosition();
	switch (m_steat)
	{
	case Wait:
		if (distance.Length() <= 200.0f) {
			m_enemy->FindAngle(distance);
			m_enemy->SetSpeed(0.0f);
			m_enemy->ChangeAnimation(Enemy::idle);
			count++;
			if (distance.Length() <= 100.0f|| count>=30)
			{
				distance.y = 0;
				distance.Normalize();
				auto front = m_enemy->Get2DFront();
				if (acos(front.Dot(distance)) <= CMath::DegToRad(10.0f))
				{
					m_enemy->ChangeAnimation(Enemy::attack);
					FindSwordpos();
					m_oldSwordcenter = m_Swordcenter;
					m_steat = Attack;
					count = 0;
				}
			}
		}
		else
		{

			m_enemy->FindAngle(distance);
			m_enemy->ChangeAnimation(Enemy::walk);
			m_enemy->SetSpeed(1.0f / 2.0f);
			m_enemy->SetDebugPos({ 0.0f,0.0f,0.0f });
			m_steat = Chase;
		}
		break;
	case Attack:
		m_enemy->SetSpeed(0.0f);
		m_enemy->ChangeAnimation(Enemy::attack);
		FindSwordpos();
		if (!m_Hit)
		{
			if (m_enemy->GetIsEvent())
			{
				auto attackMove = (m_Swordcenter - m_oldSwordcenter) / 2;
				auto hitpoint = attackMove + m_Swordcenter;
				m_Hit = GetHitObjict().HitTest(hitpoint, attackMove.Length(), m_enemy->GetStatus()->m_Attack, HitReceive::player);
				m_enemy->SetDebugPos(hitpoint);
			}
		}
		m_oldSwordcenter = m_Swordcenter;
		if (!m_enemy->GetanimationPlaying()) {
			m_Hit = false;
			m_steat = Wait;
			m_enemy->ChangeAnimation(Enemy::idle);
		}
		break;
	case Chase:
		m_enemy->FindAngle(distance);
		m_enemy->ChangeAnimation(Enemy::walk);
		m_enemy->SetSpeed(1.0f / 2.0f);
		m_enemy->SetDebugPos({ 0.0f,0.0f,0.0f });
		if (150.0f)
		{
			m_steat = Wait;
		}
		break;
	default:
		break;
	}	
	if (distance.Length() >= 500.0f)
	{
		m_enemy->SetSpeed(1.0f);
		m_enemy->TransitionState(Enemy::State_Move);
	}
	//if (distance.Length() <= 80.0f) {
	//	m_enemy->SetSpeed(0.0f);
	//	m_enemy->ChangeAnimation(Enemy::attack);
	//	FindSwordpos();
	//	//m_debugVecor->Draw()
	//	if (!m_Hit)
	//	{
	//		if (m_enemy->GetIsEvent())
	//		{
	//			auto attackMove = (m_Swordcenter - m_oldSwordcenter) / 2;
	//			auto hitpoint = attackMove + m_Swordcenter;
	//			m_Hit = GetHitObjict().HitTest(hitpoint, attackMove.Length(), m_enemy->GetStatus()->m_Attack, HitReceive::player);
	//			m_enemy->Setdebugpos(hitpoint);
	//		}
	//	}
	//	m_oldSwordcenter = m_Swordcenter;
	//	//CollisionTest();
	//	if (!m_enemy->GetanimationPlaying()) {

	//	}
	//}
	////m_debugVecor->Update(CVector3::Zero());
	//else {
	//	if (distance.Length() <= 200.0f) {
	//		m_enemy->FindAngle(distance);
	//		m_enemy->SetSpeed(0.0f);
	//		m_enemy->ChangeAnimation(Enemy::idle);
	//		//m_debugVecor->Update(hitpoint);
	//	}
	//	else
	//	{
	//		m_enemy->ChangeAnimation(Enemy::walk);
	//		m_enemy->SetSpeed(1.0f / 2.0f);
	//		m_enemy->Setdebugpos({ 0.0f,0.0f,0.0f });
	//	}
	//}
	//if (distance.Length() >= 500.0f)
	//{
	//	m_enemy->SetSpeed(1.0f);
	//	m_enemy->TransitionState(Enemy::State_Move);
	//}
	////m_debugVecor->Draw();
	//
}
//struct Attack : public btCollisionWorld::ConvexResultCallback
//{
//	bool hit = false; //���̔ԍ�
//
//						 //�Փ˂����Ƃ��ɌĂ΂��R�[���o�b�N�֐��B
//	virtual	btScalar	addSingleResult(btCollisionWorld::LocalConvexResult& convexResult, bool normalInWorldSpace)
//	{
//		if (convexResult.m_hitCollisionObject->getUserIndex() != enCollisionAttr_Character) {
//			return 0.0f;
//		}
//		hit = true;
//		return 0.0f;
//	}
//};
//void EnemyStateAttack::CollisionTest()
//{
//	//�ړ��O�̌��̏�����׃N�g����
//	//�ړ���̃x�N�g�������߂�
//	auto Swordvector = m_Swordcenter - m_handpos;
//	auto oldSwordvector = m_oldSwordcenter - m_oldhandpos;
//	Swordvector.Normalize();
//	oldSwordvector.Normalize();
//	CVector3 addPos = CVector3::Zero();
//	addPos.Subtract(m_handpos, m_oldhandpos);
//	//�����������邩�ǂ������ׂ�
//	//�ƂĂ��������l���ƏՓ˔��肪�ł��Ȃ�
//	//FLT_EPSILON��1���傫���A�ŏ��̒l�Ƃ̍�����\���萔�B
//	//�ƂĂ��������l�̂��Ƃł��B
//	if (addPos.Length() > FLT_EPSILON) {
//		//����������̂Ȃ�
//		//�R���C�_�[����
//		CapsuleCollider m_collide;
//		m_collide.Create(SWODSIZE.x, SWODSIZE.z);						
//	    //���C���쐬�B
//		btTransform start, end;
//		start.setIdentity();
//		end.setIdentity();
//		CQuaternion Rot = CQuaternion::Identity();
//		//�܂��X�^�[�g�̊p�x���v�Z����B
//		Rot.Multiply(anglecalculation(Swordvector, CVector3::AxisY()));
//		//�n�_�̓J�v�Z���R���C�_�[�̒��S���W�i���̒��S�j
//		start.setOrigin(btVector3(m_Swordcenter.x, m_Swordcenter.y, m_Swordcenter.z));
//		//�n�_�̊p�x��ݒ肷��B
//		start.setRotation(btQuaternion(Rot.x, Rot.y, Rot.z, Rot.w));
//		//���͏I�_�̈ړ���ݒ�i���̒��S�j
//		end.setOrigin(btVector3(m_oldSwordcenter.x, m_oldSwordcenter.y, m_oldSwordcenter.z));
//		//�n�_�ɑ΂���ړ��p�x�����߂�
//		Rot.Multiply(anglecalculation(Swordvector, oldSwordvector));
//		//���߂��I�_�p�x��ݒ肷��B
//		end.setRotation(btQuaternion(Rot.x, Rot.y, Rot.z, Rot.w));
//		Attack callback;
//		//�Փˌ��o�B
//		g_physics.ConvexSweepTest((const btConvexShape*)m_collide.GetBody(), start, end, callback);
//		//�Փ˂������ǂ���
//		if (callback.hit)
//		{
//			//�Փ˂����̂Ń_���[�W����
//			m_player->Damage(30.0f);
//		}
//	}
//	//�v�Z���I������̂�
//	//�ړ���̃|�W�V������ۑ�����
//	m_oldSwordcenter = m_Swordcenter;
//	m_oldhandpos = m_handpos;
//}
//CQuaternion EnemyStateAttack::anglecalculation(CVector3 vector1,CVector3 vector2)
//{
//	float lafrea = acos(vector1.Dot(vector2));
//	lafrea = CMath::RadToDeg(lafrea);
//	CVector3 jiku;
//	jiku.Cross(vector1, vector2);
//	CQuaternion hogehoge = CQuaternion::Identity();
//	if (jiku.y > 0.0f || jiku.y < -FLT_MIN)
//	{
//		jiku.Normalize();
//		hogehoge.SetRotationDeg(jiku, lafrea);
//	}
//	return hogehoge;
//}
void EnemyStateAttack::FindSwordpos()
{
	CMatrix BoneMatrix = m_enemy->CopyModel().GetSkeleton().GetBone(m_boneNo)->GetWorldMatrix();
	m_handpos.x = BoneMatrix.m[3][0];
	m_handpos.y = BoneMatrix.m[3][1];
	m_handpos.z = BoneMatrix.m[3][2];
	m_Up.x = BoneMatrix.m[2][0];
	m_Up.y = BoneMatrix.m[2][1];
	m_Up.z = BoneMatrix.m[2][2];
	m_Up.Normalize();
	m_Swordcenter.x = m_handpos.x + m_Up.x*SWODSIZE.z / 2;
	m_Swordcenter.y = m_handpos.y + m_Up.y*SWODSIZE.z / 2;
	m_Swordcenter.z = m_handpos.z + m_Up.z*SWODSIZE.z / 2;
}