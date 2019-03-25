#include "stdafx.h"
#include "Enemy.h"
#include"Enenystate.h"
#include"Player.h"
#include"../HitObjict.h"
#include "Physics/CollisionAttr.h"

Enemy::Enemy()
{
	//体力用の2Ｄデータ(中身)				//体力用の2Ｄデータ(枠)
}


Enemy::~Enemy()
{
	delete m_enemystate;
	delete m_debugVecor;
}
bool Enemy::Load()
{
	//cmoファイルの読み込み。
	InitAnim();
	m_collider.Init(30.0f, 60.0f, m_position);
	InitTex();
	FindArm();
	m_debugVecor = new VectorDraw(m_position);
	m_debugVecor->Update({ 0.0f,0.0f,0.0f });
	m_Rot.MakeRotationFromQuaternion(m_angle);
	m_Front.x = m_Rot.m[2][0];
	m_Front.y = m_Rot.m[2][1];
	m_Front.z = m_Rot.m[2][2];
	m_Front.Normalize();
	TransitionState(State_Move);
	//m_position.y = 0.0f;
	m_model.UpdateWorldMatrix(m_position, m_angle, CVector3::One());
	m_bgmA.Init(L"Assets/sound/gameag.wav");
	m_obj = GetHitObjict().Create(&m_position, 100.0f,
		[&](int damage) 
	{
		Hit(damage);
	},
		HitReceive::enemy);
	m_Leader->CopySkinModel().UpdateInstancingData(m_position, CQuaternion::Identity(), CVector3::One());
	return true;
}
void Enemy::InitTex()
{
	m_texture_hp.CreateFromDDSTextureFromFile(L"Resource/sprite/HP.dds");
	m_texture_fram.CreateFromDDSTextureFromFile(L"Resource/sprite/HP_waku.dds");
	m_Sprite_hp.Init(m_texture_hp.GetBody(), 100.0f, 25.0f);
	m_Sprite_fram.Init(m_texture_fram.GetBody(), 100.0f, 25.0f);
}
void Enemy::InitAnim()
{
	wchar_t moveFilePath[256];
	//モデルのロード
	swprintf_s(moveFilePath, L"Assets/modelData/%s.cmo", m_Status->m_CharaName.c_str());
	m_model.Init(moveFilePath);
	swprintf_s(moveFilePath, L"Assets/animData/%s_idle.tka", m_Status->m_CharaName.c_str());
	m_animationclip[idle].Load(moveFilePath);
	m_animationclip[idle].SetLoopFlag(true);	
	swprintf_s(moveFilePath, L"Assets/animData/%s_attack.tka", m_Status->m_CharaName.c_str());
	m_animationclip[attack].Load(moveFilePath);
	m_animationclip[attack].SetLoopFlag(false);
	swprintf_s(moveFilePath, L"Assets/animData/%s_walk.tka", m_Status->m_CharaName.c_str());
	m_animationclip[walk].Load(moveFilePath);
	m_animationclip[walk].SetLoopFlag(true);
	swprintf_s(moveFilePath, L"Assets/animData/%s_hit.tka", m_Status->m_CharaName.c_str());
	m_animationclip[hit].Load(moveFilePath);
	m_animationclip[hit].SetLoopFlag(false);
	swprintf_s(moveFilePath, L"Assets/animData/%s_dead.tka", m_Status->m_CharaName.c_str());
	m_animationclip[dead].Load(moveFilePath);
	m_animationclip[dead].SetLoopFlag(false);
	m_animation.Init(m_model, m_animationclip, animnum);
	m_animation.Play(walk, 0.2f);
}
void Enemy::FindArm()
{
	int hoge = -1;
	int num = m_model.GetSkeleton().GetNumBones();
	for (int i = 0; i < num; i++) {
		auto bonename = m_model.GetSkeleton().GetBone(i)->GetName();
		wchar_t moveFilePath[256];
		//モデルから手のボーンを検索
		swprintf_s(moveFilePath, L"%sHand", m_Status->m_CharaName.c_str());
		int result = wcscmp(moveFilePath, bonename);
		if (result == 0)
		{
			hoge = m_model.GetSkeleton().GetBone(i)->GetNo();
			break;
		}
	}
	m_bolnNo = hoge;
}
void Enemy::TransitionState(State m_state)
{
	delete m_enemystate;
	switch (m_state)
	{
	case State_Move:
		m_enemystate = new EnemyStateMove(this, m_player);
		break;
	case State_Attack:
		m_enemystate = new EnemyStateAttack(this, m_player);
		break;
	case State_Gathering:
		m_enemystate = new EnemyStategathering(this, m_player);
		break;
	case State_Hit:
		m_enemystate = new EnemyStateHit(this, m_player);
		break;
	case State_Dead:
		m_enemystate = new EnemyStateDead(this, m_player);
		break;
	default:
		break;
	}
	m_model.UpdateWorldMatrix(m_position, m_angle,CVector3::One());
	m_animation.Update(GetTime().GetFrameTime());
}
void Enemy::Update()
{
	m_enemystate->Update();
	//ワールド行列の更新。	
	m_Rot.MakeRotationFromQuaternion(m_angle);
	m_Front.x = m_Rot.m[2][0];
	m_Front.y = m_Rot.m[2][1];
	m_Front.z = m_Rot.m[2][2];
	m_Front.y = 0.0f;
	m_Front.Normalize();
	m_moveVector = m_Front * m_speed;
	m_moveVector.y -= GRAVITY;
	m_position = m_collider.Execute(GetTime().GetFrameTime(), m_moveVector);
	CVector3 distance = m_player->Get2Dposition() - Get2DPosition();
	if (distance.Length() >= 1500.0f)
	{
		//プレイヤーとの距離が離れすぎたら集合する
		ChangeLeaderState(Enemyleader::gathering);
		SetLeaderPosition(Get3DPosition());
	}
	m_model.UpdateWorldMatrix(m_position, m_angle, CVector3::One());
	g_graphicsEngine->SetShadoCaster(&m_model);
	m_model.SetShadowReciever(true);
	m_mutekitaim++;
	m_Leader->CopySkinModel().UpdateInstancingData(m_position, m_angle, CVector3::One());
}
void Enemy::postDraw()
{
	DrawDebugVector();
	HP_Draw();
}
void Enemy::Draw()
{
	m_model.UpdateWorldMatrix(m_position, m_angle, CVector3::One());
	m_animation.Update(GetTime().GetFrameTime());
	m_model.Draw(
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix()
	);

	m_debugVecor->Draw();
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
}
void Enemy::HP_Draw()
{
	auto la = m_position;
	la.y += 150.0f;
	m_Sprite_hp.Updete(la, m_Sprite_angle, { m_HP/m_Status->m_HP,1.0f ,1.0f });
	m_Sprite_hp.Draw(
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix()
	);
}
void Enemy::FindAngle(const CVector3& Vector)
{
	m_Front.y = 0;
	m_Front.Normalize();
	CVector3 vector = Vector;
	vector.Normalize();
	auto debag = m_Front;
	auto Angle = acos(debag.Dot(vector));
	//目標との角度が１度以上なら回転させる
	if (Angle >= CMath::DegToRad(1.0f))
	{
		SetSpeed(1.0f/10.0f);
		auto ka5 = CVector3::Zero();
		ka5.Cross(debag, vector);
		//外積を使い軸を計算する
		CQuaternion ma3;
		if (ka5.y < 0)
		{
			ka5 = CVector3::AxisY()*-1;
		}
		else
		{
			ka5 = CVector3::AxisY();
		}
		//１フレーム当たりの最大角度と比較する
		if (Angle <= m_margin)
		{
			//きっちり角度を合わせる
			ma3.SetRotation(ka5, Angle);
		}
		else
		{
			//最大角度で回転させる
			ma3.SetRotationDeg(ka5, m_kaku);
		}
		m_angle.Multiply(ma3, m_angle);
	}
	else
	{
		if (m_speed <= m_Status->m_Speed)
		{
			m_speed += 100.0f;
		}
		else 
		{
			SetSpeed(1.0f);
		}
	}
}
void Enemy::Hit(float damage)
{
	float hidame = damage - m_Status->m_Defense;
	if (hidame > 0.0f&&m_mutekitaim >=30)
	{
		m_HP -= hidame;
		m_mutekitaim = 0;
		if (m_HP <= 0.01f)
		{
			TransitionState(State_Dead);
		}
		else {
			m_bgmA.Play(false);
			TransitionState(State_Hit);
		}
	}
}
void Enemy::DeleteHitobj()
{
	GetHitObjict().Deleteobjict(m_obj);
}
