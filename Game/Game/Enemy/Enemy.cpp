#include "stdafx.h"
#include "Enemy.h"
#include"Enenystate.h"
#include"../../Player/Player.h"
#include "Physics/CollisionAttr.h"

Enemy::Enemy()
{
}


Enemy::~Enemy()
{
	delete m_enemystate;
	delete m_debugVecor;
}
bool Enemy::Load()
{
	//cmoファイルの読み込み。
	m_model.Init(L"Assets/modelData/ToonRTS_demo_Knight.cmo");
	//m_collider.Init(20.0f, 50.0f, m_position);
	m_texture_hp.CreateFromDDSTextureFromFile(L"Resource/sprite/HP.dds");
	m_texture_fram.CreateFromDDSTextureFromFile(L"Resource/sprite/HP_waku.dds");
	m_Sprite_hp.Init(&m_texture_hp, 100.0f, 25.0f);
	m_Sprite_fram.Init(&m_texture_fram, 100.0f, 25.0f);
	m_debugVecor = new VectorDraw(m_position);
	m_Rot.MakeRotationFromQuaternion(m_angle);
	m_Front.x = m_Rot.m[2][0];
	m_Front.y = m_Rot.m[2][1];
	m_Front.z = m_Rot.m[2][2];
	m_Front.Normalize();
	m_position.y = 0.0f;
	static int hoge = -1;
	int num = CopyModel().GetSkeleton().GetNumBones();
	if (hoge == -1) {
		for (int i = 0; i < num; i++) {
			auto bonename = CopyModel().GetSkeleton().GetBone(i)->GetName();

			int result = wcscmp(L"Bip001 R Hand", bonename);
			if (result == 0)
			{
				
				hoge = CopyModel().GetSkeleton().GetBone(i)->GetNo();
				break;
			}
		}
	}
	m_bolnNo = hoge;
	m_animationclip[idle].Load(L"Assets/animData/enemy_idel.tka");
	m_animationclip[idle].SetLoopFlag(true); 
	m_animationclip[attack].Load(L"Assets/animData/enemy_attack.tka");
	m_animationclip[attack].SetLoopFlag(true);	
	m_animationclip[walk].Load(L"Assets/animData/enemy_walk.tka");
	m_animationclip[walk].SetLoopFlag(true);
	m_animation.Init(m_model, m_animationclip, animnum);
	m_animation.Play(walk, 0.2f);
	TransitionState(State_Attack);
	m_model.UpdateWorldMatrix(m_position, m_angle, CVector3::One());
	m_Leader->CopySkinModel().UpdateInstancingData(m_position, CQuaternion::Identity(), CVector3::One());
	return true;
}
void Enemy::TransitionState(State m_state)
{
	delete m_enemystate;
	switch (m_state)
	{
	case State_Tracking:
		m_enemystate = new EnemyStateTracking(this, m_player);
		break;
	case State_Move:
		m_enemystate = new EnemyStateMove(this, m_player);
		break;
	case State_Attack:
		m_enemystate = new EnemyStateAttack(this, m_player);
		break;
	case State_Gathering:
		m_enemystate = new EnemyStategathering(this, m_player);
		break;
	default:
		break;
	}
	m_model.UpdateWorldMatrix(m_position, m_angle,CVector3::One());
}
void Enemy::Update()
{
	if (m_HP <= 0.0f)
	{

	}
	m_enemystate->Update();
	//ワールド行列の更新。	
	m_Rot.MakeRotationFromQuaternion(m_angle);
	m_Front.x = m_Rot.m[2][0];
	m_Front.y = m_Rot.m[2][1];
	m_Front.z = m_Rot.m[2][2];
	m_Front.y = 0.0f;
	m_Front.Normalize();
	m_moveVector = m_Front*m_speed;
	//m_moveVector.y -= 9.8*10.0f;
	m_position += m_moveVector * 1.0f / 30.0f;
	//m_position= m_collider.Execute(1.0f / 30.0f, m_moveVector);
	CVector3 distance = m_player->Get2Dposition() - Get2DPosition();
	if (distance.Length() >= 600.0f)
	{
		ChangeLeaderState(Enemyleader::gathering);
		SetLeaderPosition(Get3DPosition());
	}
	m_animation.Update(1.0f / 30.0f);
	m_model.UpdateWorldMatrix(m_position, m_angle, CVector3::One());
	g_graphicsEngine->SetShadoCaster(&m_model);
	m_model.SetShadowReciever(true);
	m_Leader->CopySkinModel().UpdateInstancingData(m_position, m_angle, CVector3::One());
}
void Enemy::postDraw()
{
	DrawDebugVector();
	HP_Draw();
}
void Enemy::Draw()
{
	m_model.Draw(
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix()
	);
}
void Enemy::DrawDebugVector()
{
	
	CVector3 kakudo;
	kakudo = g_camera3D.GetPosition() - m_position;
	kakudo.y = 0;
	kakudo.Normalize();
	float kaku = acos(kakudo.Dot(m_Sprite_Front));
	kaku = CMath::RadToDeg(kaku);
	CVector3 jiku;
	jiku.Cross(m_Sprite_Front, kakudo);
	if (jiku.y > 0) {
		m_Sprite_angle.SetRotationDeg(CVector3::AxisY(), kaku);
	}
	else {
		m_Sprite_angle.SetRotationDeg(CVector3::AxisY()*-1, kaku);
	}
#ifdef _DEBUG
	//@todo m_Sprite_angleで回した結果を見るためのデバッグコード
	CVector3 hoge = CVector3::AxisZ()*-1;
	m_Sprite_angle.Multiply(hoge);
	m_debugVecor->Update(m_position, hoge, 1.0);
	m_debugVecor->Draw();
#endif
}
void Enemy::HP_Draw()
{
	if (g_pad[0].IsPress(enButtonRB1))
	{
		m_HP -= 0.01;
	}
	auto la = m_position;
	la.y += 100.0f;
	m_Sprite_hp.Updete(la, m_Sprite_angle, { m_HP,1.0f ,1.0f });
	m_Sprite_hp.Draw(
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix()
	);
}
void Enemy::FindAngle(CVector3 Vector)
{
	m_Front.y = 0;
	m_Front.Normalize();
	auto debag = m_Front;
	auto Angle = acos(debag.Dot(Vector));
	if (Angle >= CMath::DegToRad(1.0f))
	{
		SetSpeed(0.0f);
		auto ka5 = CVector3::Zero();
		ka5.Cross(debag, Vector);
		CQuaternion ma3;
		if (ka5.y < 0)
		{
			ka5 = CVector3::AxisY()*-1;
		}
		else
		{
			ka5 = CVector3::AxisY();
		}
		if (Angle <= m_margin)
		{
			ma3.SetRotation(ka5, Angle);
		}
		else
		{
			ma3.SetRotationDeg(ka5, m_kaku);
		}
		m_angle.Multiply(ma3, m_angle);
	}
	else
	{
		if (m_speed <= 300)
		{
			m_speed += 100.0f;
		}
		else 
		{
			SetSpeed(300.0f);
		}
	}
}
