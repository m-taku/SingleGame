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
	delete kasa;
}
bool Enemy::Load()
{
	//cmoファイルの読み込み。
	m_model.Init(L"Assets/modelData/ToonRTS_demo_Knight.cmo");
	m_collider.Init(30.0f, 50.0f, m_position);
	texture_hp.CreateFromDDSTextureFromFile(L"Resource/sprite/HP.dds");
	texture_fram.CreateFromDDSTextureFromFile(L"Resource/sprite/HP_waku.dds");
	Sprite_hp.Init(&texture_hp, 100.0f, 25.0f);
	Sprite_fram.Init(&texture_fram, 100.0f, 25.0f);
	kasa = new VectorDraw(m_position); 

	mRot.MakeRotationFromQuaternion(m_angle);
	m_Front.x = mRot.m[2][0];
	m_Front.y = mRot.m[2][1];
	m_Front.z = mRot.m[2][2];
	m_Front.Normalize();
	TransitionState(State_Tracking);
	m_position.y = 0.0f;
	Leader->CopySkinModel().UpdateInstancingData(m_position, CQuaternion::Identity(), CVector3::One());
	return true;
}
void Enemy::TransitionState(State state)
{
	delete m_enemystate;
	switch (state)
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
	mRot.MakeRotationFromQuaternion(m_angle);
	m_Front.x = mRot.m[2][0];
	m_Front.y = mRot.m[2][1];
	m_Front.z = mRot.m[2][2];
	m_Front.y = 0.0f;
	m_Front.Normalize();
	m_moveVector = m_Front;
	m_moveVector *= m_speed;
	m_moveVector.y -= 9.8*10.0f;
	m_position += m_moveVector * 1.0 / 30.0f;
	m_position = m_collider.Execute(1.0f / 30.0f, m_moveVector);
	m_model.UpdateWorldMatrix(m_position, m_angle, CVector3::One());
	//Leader->GetSkinmdel().UpdateInstancingData(m_position, m_angle, CVector3::One());
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

	Vectordraw();
	HP_Draw();
}
void Enemy::Draw()
{
	//m_position.y += 120.0f;
	//kasa->Draw();	
	//m_position.x -= Sprite_fram.Gethalf_sizeX();
	//if (DrewFragu) {
	//}
	m_model.Draw(
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix()
	);
}
void Enemy::Vectordraw()
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
	CVector3 kakaa = CVector3::AxisZ()*-1;
	m_Sprite_angle.Multiply(kakaa);

	kasa->Update(m_position, kakaa, 1.0);
}
void Enemy::HP_Draw()
{
	if (g_pad[0].IsPress(enButtonRB1))
	{
		m_HP -= 0.01;
	}
	auto la = m_position;
	la.y += 300.0f;
	//Sprite_fram.Updete(la, m_Sprite_angle, { 1.0f,1.0f,1.0f });
	//Sprite_fram.Draw(
	//	g_camera3D.GetViewMatrix(),
	//	g_camera3D.GetProjectionMatrix());
	Sprite_hp.Updete(la, m_Sprite_angle, { m_HP,1.0f ,1.0f });
	Sprite_hp.Draw(
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
