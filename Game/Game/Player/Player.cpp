#include "stdafx.h"
#include "Player.h"
#include"../HitObjict.h"
#include"PlayerState.h"
#include"Gamecamera.h"
#include"../graphics/SkinModelEffect.h"


Player::Player()
{
	//m_collider.Init(15.0f, 80.0f, m_position);
	//m_model.Init(L"Assets/modelData/unityChan.cmo");
}
Player::~Player()
{
	//delete m_hit;
	delete m_State;
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
	InitAnimation();
	UpdateFront();
	m_model.UpdateWorldMatrix(m_position, m_rotation, {0.1f,0.1f,0.1f});
	g_HitObjict->Create(
		&m_position, 
		100.0f, 
		[&]() 
	{ 
		Hit();
	},
		HitReceive::player);
	TransitionState(State_Move);
	return true;
}
void Player::TransitionState(State m_state)
{
	//int j = 4;
	delete m_State;
	switch (m_state)
	{
	case State_Attack:
		m_State = new Player_Attack(this);
		break;
	case State_Move:
		m_State = new Player_Move(this);
	default:
		break;
	}
	m_model.UpdateWorldMatrix(m_position, m_rotation, CVector3::One());
	m_animation.Update(1.0f / 30.0f);
}
void Player::InitAnimation()
{
	m_animationclip[ded].Load(L"Assets/animData/pla_ded.tka");
	m_animationclip[ded].SetLoopFlag(false);
	m_animationclip[attack].Load(L"Assets/animData/pla_ateec.tka");
	m_animationclip[attack].SetLoopFlag(false);
	m_animationclip[defens].Load(L"Assets/animData/pla_defens.tka");
	m_animationclip[defens].SetLoopFlag(true);
	m_animationclip[walk].Load(L"Assets/animData/pla_walk.tka");
	m_animationclip[walk].SetLoopFlag(true);
	m_animation.Init(m_model, m_animationclip, animnum);
	m_animation.Play(walk, 0.2f);
}
void Player::Update()
{
	m_State->Update();
	m_debugVector->Update({0.0f,0.0f,0.0f});
	//ワールド行列の更新。	
	//ガードしたい
	{
		if (g_pad[0].IsTrigger(enButtonRB1))
		{
			m_animation.Play(defens, 0.2f);
			auto ka = m_position;
			ka.y += 100.0f;
			ka += m_Front * 100.0f;
			m_debugVector->Update(ka);
			g_HitObjict->HitTest(ka, HitReceive::enemy);
			m_attac = true;
		}
		else
		{
			if (!m_animation.IsPlaying())
			{
				m_animation.Play(walk, 0.20f);
				m_attac = false;
			}
			if (m_attac)
			{
				auto ka = m_position;
				ka.y += 100.0f;
				ka += m_Front * 100.0f;
				m_debugVector->Update(ka);
				g_HitObjict->HitTest(ka, HitReceive::enemy);
			}
		}
	}
	//死んだーーーー
	{
		if (g_pad[0].IsTrigger(enButtonRB2))
		{
			m_animation.Play(ded, 0.2f);
			auto ka = m_position;
			ka.y += 100.0f;
			ka += m_Front * 100.0f;
			m_debugVector->Update(ka);
			g_HitObjict->HitTest(ka, HitReceive::enemy);
			m_attac = true;
		}
		else
		{
			if (!m_animation.IsPlaying())
			{
				m_animation.Play(walk, 0.20f);
				m_attac = false;
			}
			if (m_attac)
			{
				auto ka = m_position;
				ka.y += 100.0f;
				ka += m_Front * 100.0f;
				m_debugVector->Update(ka);
				g_HitObjict->HitTest(ka, HitReceive::enemy);
			}
		}
	}
	if (g_pad[0].IsTrigger(enButtonX)) {
		TransitionState(State_Attack);
	}
	UpdateFront();
	m_movespeed.x = m_Front.x * m_plyerStatus.speed*m_speed;
	m_movespeed.z = m_Front.z * m_plyerStatus.speed*m_speed;
	m_movespeed.y -= GRAVITY;
	m_position = m_collider.Execute(1.0f / 30.0f, m_movespeed);
	m_model.UpdateWorldMatrix(m_position, m_rotation, { 1.0f,1.0f,1.0f });
	g_graphicsEngine->SetShadoCaster(&m_model);
	m_model.SetShadowReciever(true);
	m_animation.Update(1.0f / 30.0f);
	//ここから影の処理
	auto ritpos = m_position;
	CVector3 m = { -707.0f,707.0f, 0.0f };
	ritpos.x += m.x;
	ritpos.y += m.y;
	g_graphicsEngine->GetShadowMap()->UpdateFromLightTarget(ritpos, m_position);

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