#include"stdafx.h"
#include"Player.h"
#include"HitObjict.h"
#include"PlayerState.h"
#include"Gamecamera.h"
#include"../graphics/SkinModelEffect.h"


Player::Player()
{
}
Player::~Player()
{
	delete m_State;
	delete m_debugVector;
	delete m_plyerStatus;
	delete p_status;
}
void Player::OnDestroy()
{
	//g_objectManager->DereteGO(m_ui);
	//delete m_State;
	//delete m_debugVector;
	//g_objectManager->DereteGO(m_ui);
}
void Player::Stop()
{
	ChangeAnimation(idle);
	m_position = m_collider.Execute(GetTime().GetFrameTime(), m_movespeed);
	m_model.UpdateWorldMatrix(m_position, m_rotation, { 1.0f,1.0f,1.0f });
}
bool Player::Load()
{
	const float PLAYER_RADIUS = 40.0f;	//プレイヤーの半径。
	const float PLAYER_HEIGHT = 80.0f;	//プレイヤーの高さ。
	//cmoファイルの読み込み。
	m_model.Init(L"Assets/modelData/player.cmo");
	m_collider.Init(PLAYER_RADIUS, PLAYER_HEIGHT, m_position);
	m_debugVector = new VectorDraw(m_position);
	m_rotation.SetRotationDeg(CVector3::AxisY(), 0.0f);
	m_ui = g_objectManager->FindGO<UI>("UI");// UI > (GameObjectPriority_Default);
	InitAnimation();
	FindArm();
	UpdateFront();
	m_model.UpdateWorldMatrix(m_position, m_rotation, {1.0f,1.0f,1.0f});
	GetHitObjict().Create(
		&m_position, 
		150.0f, 
		[&](float damage)
	{ 
		Hit(damage);
	},
		HitReceive::player);
	TransitionState(State_Move);
	return true;
}
void Player::TransitionState(State m_state)
{
	delete m_State;
	switch (m_state)
	{
	case State_Attack:
		m_State = new Player_Attack(this);
		break;
	case State_Move:
		m_State = new Player_Move(this);
		break;
	case State_Guard:
		m_State = new Player_Guard(this);
		break;
	case State_Hit:
		m_State = new Player_Hit(this);
		break;
	case State_did:
		m_State = new Player_Die(this);
		break;
	default:
		break;
	}
	m_model.UpdateWorldMatrix(m_position, m_rotation, CVector3::One());
	m_animation.Update(GetTime().GetFrameTime());
}
void Player::InitAnimation()
{
	m_animationclip[ded].Load(L"Assets/animData/pla_ded1.tka");
	m_animationclip[ded].SetLoopFlag(false);
	m_animationclip[attack].Load(L"Assets/animData/pla_ateec1.tka");
	m_animationclip[attack].SetLoopFlag(false);
	m_animationclip[defens].Load(L"Assets/animData/pla_defens1.tka");
	m_animationclip[defens].SetLoopFlag(false);
	m_animationclip[walk].Load(L"Assets/animData/pla_walk1.tka");
	m_animationclip[walk].SetLoopFlag(true);	
	m_animationclip[idle].Load(L"Assets/animData/pla_idle1.tka");
	m_animationclip[idle].SetLoopFlag(true); 
	m_animationclip[run].Load(L"Assets/animData/pla_run1.tka");
	m_animationclip[run].SetLoopFlag(true);
	m_animationclip[hit].Load(L"Assets/animData/pla_hit1.tka");
	m_animationclip[hit].SetLoopFlag(false);
	m_animation.Init(m_model, m_animationclip, animnum);
	m_animation.Play(idle, 0.2f);
}

void Player::Update()
{
	UpdateFront();
	m_debugVector->Update({0.0f,0.0f,0.0f});
	m_State->Update();
	m_movespeed.x = m_Front.x * m_plyerStatus->m_Speed*m_speed;
	m_movespeed.z = m_Front.z * m_plyerStatus->m_Speed*m_speed;
	m_movespeed.y -= GRAVITY;
	if(g_pad[0].IsTrigger(enButtonA))
	{
		m_movespeed.y = 500.0f;
	}
	m_position = m_collider.Execute(GetTime().GetFrameTime(), m_movespeed);
	g_graphicsEngine->SetShadoCaster(&m_model);
	m_model.SetShadowReciever(true);
	//ここから影の処理
	auto ritpos = m_position;
	CVector3 m = { -707.0f,707.0f, 0.0f };
	ritpos.x += m.x;
	ritpos.y += m.y;
	g_graphicsEngine->GetShadowMap()->UpdateFromLightTarget(ritpos, m_position);
	m_model.UpdateWorldMatrix(m_position, m_rotation, { 1.0f,1.0f,1.0f });
	m_animation.Update(GetTime().GetFrameTime());

}
void Player::Draw()
{	
	
	
	
	m_debugVector->Draw();
	m_model.Draw(
		g_camera3D.GetViewMatrix(), 
		g_camera3D.GetProjectionMatrix()
	);
}
void Player::Hit(float damage)
{
	if (!m_Hit) {
	//ここにダメージの処理
		Damage(damage);
		if (m_plyerStatus->m_HP <= 0.0f)
		{
			TransitionState(State_did);
			m_Hit = true;
		}
		else
		{
			TransitionState(State_Hit);
		}			
	}
}
void Player::FindArm()
{
	int hoge = -1;
	int num = m_model.GetSkeleton().GetNumBones();
	for (int i = 0; i < num; i++) {
		auto bonename = m_model.GetSkeleton().GetBone(i)->GetName();
		wchar_t moveFilePath[256];
		swprintf_s(moveFilePath, L"Hand");
		//腕のボーン番号を名前で取得
		int result = wcscmp(moveFilePath, bonename);
		if (result == 0)
		{
			hoge = m_model.GetSkeleton().GetBone(i)->GetNo();
			break;
		}
	}
	m_armboneNo = hoge;
}