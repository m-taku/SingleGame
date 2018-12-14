#include "stdafx.h"
#include "Player.h"
#include"Gamecamera.h"
#include"../graphics/SkinModelEffect.h"


Player::Player()
{
	//m_collider.Init(15.0f, 80.0f, m_position);
	//m_model.Init(L"Assets/modelData/unityChan.cmo");
}
Player::~Player()
{
	delete m_debugVector;
}
bool Player::Load()
{
	const float PLAYER_RADIUS = 15.0f;	//プレイヤーの半径。
	const float PLAYER_HEIGHT = 80.0f;	//プレイヤーの高さ。
	//cmoファイルの読み込み。
	m_collider.Init(PLAYER_RADIUS, PLAYER_HEIGHT, m_position);
	m_model.Init(L"Assets/modelData/ToonRTS_demo_Knight.cmo");
	m_debugVector = new VectorDraw(m_position);
	m_rotation.SetRotationDeg(CVector3::AxisY(), 0.0f);
	m_ui = g_objectManager->NewGO<UI>(GameObjectPriority_Default);
	m_mRot.MakeRotationFromQuaternion(m_rotation);
	m_Front.x = m_mRot.m[2][0];
	m_Front.y = m_mRot.m[2][1];
	m_Front.z = m_mRot.m[2][2];
	m_Front.Normalize();
	m_animationclip[idle].Load(L"Assets/animData/enemy_idel.tka");
	m_animationclip[idle].SetLoopFlag(true);
	m_animationclip[attack].Load(L"Assets/animData/enemy_attack.tka");
	m_animationclip[attack].SetLoopFlag(true);
	m_animationclip[walk].Load(L"Assets/animData/enemy_walk.tka");
	m_animationclip[walk].SetLoopFlag(true);
	m_animation.Init(m_model, m_animationclip, animnum);
	m_animation.Play(walk, 0.2f);
	m_model.UpdateWorldMatrix(m_position, m_rotation, {0.1f,0.1f,0.1f});
	return true;
}
void Player::Update()
{

	//ワールド行列の更新。	
	m_amount.x = g_pad->GetLStickXF();
	m_amount.z = g_pad->GetLStickYF();
	m_amount.y = 0.0f;
	if (m_amount.Length() > 0.0f)
	{
		CVector3 amount = m_amount;
		amount.Normalize();
		CVector3 camer_front = m_camera->GetCameraFront();
		camer_front.y = 0.0f;
		camer_front.Normalize();
		m_angle = acos(amount.Dot(CVector3::AxisZ()));
		if (amount.x < 0)
		{
			m_angle *= -1;
		}
		float camer_angle = acos(camer_front.Dot(CVector3::AxisZ()));
		CVector3 camer_jiku;
		camer_jiku.Cross(camer_front, CVector3::AxisZ());
		if (camer_jiku.y > 0)
		{
			camer_angle *= -1;
		}
		m_angle += camer_angle;
		m_rotation.SetRotation(CVector3::AxisY(), m_angle);
	}

	m_mRot.MakeRotationFromQuaternion(m_rotation);
	m_Front.x = m_mRot.m[2][0];
	m_Front.y = m_mRot.m[2][1];
	m_Front.z = m_mRot.m[2][2];
	m_Front.Normalize();
	m_movespeed.x = m_Front.x * m_plyerStatus.speed*m_amount.Length();
	m_movespeed.z = m_Front.z * m_plyerStatus.speed*m_amount.Length();
	m_movespeed.y -= GRAVITY;
	if (g_pad[0].IsTrigger(enButtonA)&& m_collider.IsOnGround())
	{
		m_movespeed.y = 1500.0f;
	}
	m_position = m_collider.Execute(1.0f / 30.0f, m_movespeed);
	m_model.UpdateWorldMatrix(m_position, m_rotation, {1.0f,1.0f,1.0f });
	g_graphicsEngine->SetShadoCaster(&m_model);
	m_model.SetShadowReciever(true);
	auto ka = m_position;
	ka.y += 100.0f;
	g_graphicsEngine->GetShadowMap()->UpdateFromLightTarget(ka, m_position);
	m_animation.Play(walk, 0.2f);
	m_animation.Update(1.0f / 30.0f);
	m_debugVector->Update(m_position, m_Front, m_amount.Length()*3.0f);
}
void Player::Draw()
{
	//m_debugVector->Draw();
	m_model.Draw(
		g_camera3D.GetViewMatrix(), 
		g_camera3D.GetProjectionMatrix()
	);
}