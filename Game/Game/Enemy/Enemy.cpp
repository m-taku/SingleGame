#include "stdafx.h"
#include "Enemy.h"
#include"Enenystate.h"
#include"../../Player/Player.h"


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
	m_collider.Init(20.0f, 50.0f, m_position);
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
	TransitionState(State_Attack);
	m_position.y = 0.0f;
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

}
void Enemy::Update()
{
	m_enemystate->Update();

	//ワールド行列の更新。	
	//m_speed.x = g_pad->GetLStickXF()*500.0f;
	//m_speed.z = g_pad->GetLStickYF()*500.0f;
	m_Rot.MakeRotationFromQuaternion(m_angle);
	m_Front.x = m_Rot.m[2][0];
	m_Front.y = m_Rot.m[2][1];
	m_Front.z = m_Rot.m[2][2];
	m_Front.y = 0.0f;
	m_Front.Normalize();
	m_moveVector = m_Front;
	m_moveVector *= m_speed;
	m_moveVector.y -= 9.8*10.0f;
	m_position += m_moveVector * 1.0 / 30.0f;
	m_position = m_collider.Execute(1.0f / 30.0f, m_moveVector);
	m_model.UpdateWorldMatrix(m_position, m_angle, CVector3::One());
	//m_Leader->GetSkinmdel().UpdateInstancingData(m_position, m_angle, CVector3::One());
	//if ((player->Get2Dposition() - m_position).Length() <= 100.0f)
	//{
	//	m_HP -= 0.01;
	//}
	/*	DrewFragu = */
	//if (frame(m_position)) {
//	}

}
void Enemy::postDraw()
{

	DrawDebugVector();
	HP_Draw();
}
void Enemy::Draw()
{
	//m_position.y += 120.0f;
	//kasa->Draw();	
	//m_position.x -= m_Sprite_fram.Gethalf_sizeX();
	//if (DrewFragu) {
	//}
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
#endif
}
void Enemy::HP_Draw()
{
	if (g_pad[0].IsPress(enButtonRB1))
	{
		m_HP -= 0.01;
	}
	auto la = m_position;
	la.y += 300.0f;
	//m_Sprite_fram.Updete(la, m_Sprite_angle, { 1.0f,1.0f,1.0f });
	//m_Sprite_fram.Draw(
	//	g_camera3D.GetViewMatrix(),
	//	g_camera3D.GetProjectionMatrix());
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
}
