#include "stdafx.h"
#include "Player.h"
#include"Gamecamera.h"
Player::Player()
{
}
Player::~Player()
{
}
bool Player::Load()
{
	//cmoファイルの読み込み。
	m_model.Init(L"Assets/modelData/unityChan.cmo");
	m_collider.Init(10.0f, 10.0f, m_position);
	kasa = new VectorDraw(m_position);
	stik = new VectorDraw(m_position);
	m_rotation.SetRotationDeg(CVector3::AxisY(), 0.0f);
	mRot.MakeRotationFromQuaternion(m_rotation);
	texture.CreateFromDDSTextureFromFile(L"Resource/sprite/damage.dds");
	ka.Init(&texture,1280.0f,720.0f);
	m_Front.x = mRot.m[2][0];
	m_Front.y = mRot.m[2][1];
	m_Front.z = mRot.m[2][2];
	m_Front.Normalize();
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
		CVector3 camer_front = m_camer->Getcamerafront();
		camer_front.y = 0.0f;
		camer_front.Normalize();
		kaiten = acos(amount.Dot(CVector3::AxisZ()));
		if (amount.x < 0)
		{
			kaiten *= -1;
		}
		float camer_angle = acos(camer_front.Dot(CVector3::AxisZ()));
		CVector3 camer_jiku;
		camer_jiku.Cross(camer_front, CVector3::AxisZ());
		if (camer_jiku.y > 0)
		{
			camer_angle *= -1;
		}
		kaiten += camer_angle;
		m_rotation.SetRotation(CVector3::AxisY(), kaiten);
	}
	mRot.MakeRotationFromQuaternion(m_rotation);
	m_Front.x = mRot.m[2][0];
	m_Front.y = mRot.m[2][1];
	m_Front.z = mRot.m[2][2];
	m_Front.Normalize();
	m_movespeed.x = m_Front.x * 500.0f*m_amount.Length();
	m_movespeed.z = m_Front.z * 500.0f*m_amount.Length();
	m_movespeed.y -= GRAVITY;
	if (g_pad[0].IsTrigger(enButtonA)&& m_collider.IsOnGround())
	{
		m_movespeed.y = 2000.0f;
	}
	m_position = m_collider.Execute(1.0f / 30.0f, m_movespeed);
	static float toimei = 0.0f;
	static bool frag = true;
	if (toimei <= 1&&frag==true)
	{
		toimei += 0.01f;
	}
	else
	{
		if (frag == true) {
			frag = false;
		}
		toimei -= 0.01f;
		if (toimei <= 0.0f) {
			frag = true;
			toimei = 0.0f;
		}
	}
	static float  kaku=0.0f;
	CQuaternion kakudo;
	kakudo.SetRotationDeg(CVector3::AxisZ(), kaku);
	kaku++;
	ka.Updete({ 0.0f,0.0f,0.0f }, kakudo, CVector3::One());
	ka.SetMulColor({ 1.0f,1.0f,0.0f,0.0f });
	ka.SetclearColor(toimei);
	m_model.UpdateWorldMatrix(m_position, m_rotation, CVector3::One());
	kasa->Update(m_position, m_Front, m_amount.Length());
}
void Player::postDraw()
{	
	ka.Draw(
		g_camera2D.GetViewMatrix(),
		g_camera2D.GetProjectionMatrix()
	);
}
void Player::Draw()
{
	kasa->Draw();
	m_model.Draw(
		g_camera3D.GetViewMatrix(), 
		g_camera3D.GetProjectionMatrix()
	);
}