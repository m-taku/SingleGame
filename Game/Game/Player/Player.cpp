#include "stdafx.h"
#include "Player.h"
#include"../HitObjict.h"
#include"Gamecamera.h"
#include"../graphics/SkinModelEffect.h"


Player::Player()
{
	//m_collider.Init(15.0f, 80.0f, m_position);
	//m_model.Init(L"Assets/modelData/unityChan.cmo");
}
Player::~Player()
{
	delete m_hit;
	delete m_debugVector;
}
bool Player::Load()
{
	const float PLAYER_RADIUS = 40.0f;	//プレイヤーの半径。
	const float PLAYER_HEIGHT = 80.0f;	//プレイヤーの高さ。
	//cmoファイルの読み込み。
	m_collider.Init(PLAYER_RADIUS, PLAYER_HEIGHT, m_position);
	m_model.Init(L"Assets/modelData/player1fbx.cmo");
	m_debugVector = new VectorDraw(m_position);
	m_rotation.SetRotationDeg(CVector3::AxisY(), 0.0f);
	m_ui = g_objectManager->NewGO<UI>(GameObjectPriority_Default);
	m_mRot.MakeRotationFromQuaternion(m_rotation);
	m_Front.x = m_mRot.m[2][0];
	m_Front.y = m_mRot.m[2][1];
	m_Front.z = m_mRot.m[2][2];
	m_Front.Normalize();
	m_animationclip[ded].Load(L"Assets/animData/pla_ded.tka");
	m_animationclip[ded].SetLoopFlag(false);
	m_animationclip[attack].Load(L"Assets/animData/pla_ateec.tka");
	m_animationclip[attack].SetLoopFlag(true);
	//m_animationclip[walk].Load(L"Assets/animData/enemy_walk.tka");
	//m_animationclip[walk].SetLoopFlag(true);
	m_animation.Init(m_model, m_animationclip, animnum);
	m_animation.Play(attack, 0.2f);
	m_model.UpdateWorldMatrix(m_position, m_rotation, {0.1f,0.1f,0.1f});
	m_hit->Create(&m_position, 100.0f, [&]() { Hit(); }
	, HitReceive::player);
	return true;
}
void Player::Update()
{
	m_debugVector->Update({0.0f,0.0f,0.0f});
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
	if (g_pad[0].IsTrigger(enButtonX))
	{
		m_animation.Play(ded, 0.2f);
		auto ka = m_position;
		ka.y += 100.0f;
		ka += m_Front*100.0f;
		m_debugVector->Update(ka);
		m_hit->HitTest(ka, HitReceive::player);
		m_attac = true;
	}
	else
	{
		if (!m_animation.IsPlaying())
		{
			m_animation.Play(attack, 0.20f);
			m_attac = false;
		}
		if (m_attac)
		{
			auto ka = m_position;	
			ka.y += 100.0f;
			ka += m_Front * 100.0f;
			m_debugVector->Update(ka);
			m_hit->HitTest(ka, HitReceive::player);
		}
	}
	m_mRot.MakeRotationFromQuaternion(m_rotation);
	m_Front.x = m_mRot.m[2][0];
	m_Front.y = m_mRot.m[2][1];
	m_Front.z = m_mRot.m[2][2];
	m_Front.Normalize();
	m_movespeed.x = m_Front.x * m_plyerStatus.speed*m_amount.Length();
	m_movespeed.z = m_Front.z * m_plyerStatus.speed*m_amount.Length();
	m_movespeed.y -= GRAVITY;
	m_position = m_collider.Execute(1.0f / 30.0f, m_movespeed);
	if (g_pad[0].IsTrigger(enButtonA) /*&& m_collider.IsOnGround()*/)
	{
		m_movespeed.y = 5000.0f;
	}
	m_model.UpdateWorldMatrix(m_position, m_rotation, { 1.0f,1.0f,1.0f });
	g_graphicsEngine->SetShadoCaster(&m_model);
	m_model.SetShadowReciever(true);
	auto ritpos= m_position;
	CVector3 m = { -707.0f,707.0f, 0.0f };
	ritpos.x += m.x;
	ritpos.y += m.y;
	g_graphicsEngine->GetShadowMap()->UpdateFromLightTarget(ritpos, m_position);
	m_animation.Update(1.0f / 30.0f);
	//m_debugVector->Update(m_position, m_Front, m_amount.Length()*3.0f);
}
void Player::Draw()
{
	m_debugVector->Draw();
	m_model.Draw(
		g_camera3D.GetViewMatrix(), 
		g_camera3D.GetProjectionMatrix()
	);
}
void Player::Hit()
{

	Damage(20.0f);
	//ここにダメージの処理
	//m_position.y += 1000.0f;

}