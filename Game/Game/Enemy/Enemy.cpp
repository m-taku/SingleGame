#include "stdafx.h"
#include "Enemy.h"
#include"Enenystate.h"
#include"Player.h"
#include"HitObjict.h"
#include "Physics/CollisionAttr.h"
#include <random>

Enemy::Enemy()
{
	//体力用の2Ｄデータ(中身)				//体力用の2Ｄデータ(枠)
}


Enemy::~Enemy()
{
	delete m_enemystate;
	delete m_debugVecor;
}
void Enemy::Stop()
{
	if (this->m_lood) {
		m_model.SetShadowReciever(true);
		ChangeAnimation(Enemy::idle);
	}
}
bool Enemy::Load()
{
	//cmoファイルの読み込み
	InitAnim();
	m_collider.Init(20.0f, 60.0f, m_position);
	InitTex();
	FindArm();
	m_debugVecor = new VectorDraw(m_position);
	m_debugVecor->Update({ 0.0f,0.0f,0.0f });
	m_Rot.MakeRotationFromQuaternion(m_angle);
	m_Front.x = m_Rot.m[2][0];
	m_Front.y = m_Rot.m[2][1];
	m_Front.z = m_Rot.m[2][2];
	m_Front.Normalize();
	//TransitionState(State_Move);
	//m_position.y = 0.0f;
	m_model.UpdateWorldMatrix(m_position, m_angle, CVector3::One());
	m_se.Init(L"Assets/sound/se_damage.wav");
	m_obj = GetHitObjict().Create(&m_position, 50.0f,
		[&](int damage) 
	{
		Hit(damage);
	},
		HitReceive::enemy);
	m_Leader->CopySkinModel().UpdateInstancingData(m_position, CQuaternion::Identity(), CVector3::One());
	m_lood = true;
	return m_lood;
}
void Enemy::InitTex()
{
	m_texture_hp.CreateFromDDSTextureFromFile(L"Resource/sprite/HP.dds");
	m_texture_fram.CreateFromDDSTextureFromFile(L"Resource/sprite/HP_waku.dds");
	float bai = 1.0f;
	if (GetStatus()->m_Spawnnum <=1)
	{
		bai *= 10.0f;
	}
	m_Sprite_hp.Init(m_texture_hp.GetBody(), 18.0f*bai, 8.0f);
	m_Sprite_fram.Init(m_texture_fram.GetBody(), 20.0f*bai, 10.0f);
}
void Enemy::InitAnim()
{
	wchar_t moveFilePath[256];
	//モデルのロード
	swprintf_s(moveFilePath, L"Assets/modelData/%s.cmo", m_Status->m_CharaName.c_str());
	m_model.Init(moveFilePath);
	//アニメーションのロード
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
	swprintf_s(moveFilePath, L"Assets/animData/%s_hit.tka", m_Status->m_CharaName.c_str());
	m_animationclip[defens].Load(moveFilePath);
	m_animationclip[defens].SetLoopFlag(false);
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
		m_enemystate = new EnemyStateMove(this, &m_player->Get3DPosition());
		break;
	case State_Attack:
		m_enemystate = new EnemyStateAttack(this, &m_player->Get3DPosition());
		break;
	case State_Defens:
		m_enemystate = new EnemyStateDefens(this, &m_player->Get3DPosition());
		break;
	case State_Gathering:
		m_enemystate = new EnemyStategathering(this, &m_player->Get3DPosition());
		break;
	case State_Hit:
		m_enemystate = new EnemyStateHit(this, &m_player->Get3DPosition());
		break;
	case State_Dead:
		m_enemystate = new EnemyStateDead(this, &m_player->Get3DPosition());
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
	m_Right.x = m_Rot.m[0][0];
	m_Right.y = m_Rot.m[0][1];
	m_Right.z = m_Rot.m[0][2];
	//m_Right.y = 0.0f;
	m_Front.x = m_Rot.m[2][0];
	m_Front.y = m_Rot.m[2][1];
	m_Front.z = m_Rot.m[2][2];
	//m_Front.y = 0.0f;
	m_Front.Normalize();
	m_moveVector.x = m_Front.x * m_frontspeed;
	m_moveVector.z = m_Front.z * m_frontspeed;
	m_moveVector.x += m_Right.x * m_Rightspeed;
	m_moveVector.z += m_Right.z * m_Rightspeed;
	m_moveVector.y -= GRAVITY;
	m_position = m_collider.Execute(GetTime().GetFrameTime(), m_moveVector);
	CVector3 distance = m_player->Get2DPosition() - Get2DPosition();
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
	m_animation.Update(GetTime().GetFrameTime());
	m_model.UpdateWorldMatrix(m_position, m_angle, CVector3::One());
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
	float bai = 1.0f;
	if (GetStatus()->m_Spawnnum <= 1)
	{
		bai *= 1.6f;
	}
	la.y += 100.0f*bai;
	m_Sprite_hp.Updete_2pivots(la, g_camera3D.GetView_rotation_Matrix(), { max(m_HP / m_Status->m_HP,0.0f),1.0f ,1.0f }, { 1.0f,0.5f });
	m_Sprite_fram.Updete(la, g_camera3D.GetView_rotation_Matrix(), { 1.0f,1.0f ,1.0f }, { 0.5f,0.5f });
	m_Sprite_fram.Draw(
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix()
	);
	m_Sprite_hp.Draw(
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix()
	);
}
void Enemy::AddAngle(const CVector3& Vector)
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
		SetFrontSpeed(1.0f/10.0f);
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
		if (m_frontspeed <= m_Status->m_Speed)
		{
			m_frontspeed += 100.0f;
		}
		else 
		{
			SetFrontSpeed(1.0f);
		}
	}
}
void Enemy::Hit(float damage)
{
	float hidame = damage - m_Status->m_Defense;
	if (hidame > 0.0f&&m_mutekitaim >= 10)
	{
		m_HP -= hidame;
		m_mutekitaim = 0;
		if (m_HP <= 0.01f)
		{
			m_moveVector.y = 600.0f;
			m_se.Play(false);
			TransitionState(State_Dead);
			m_mutekitaim = -1000000.0f;
		}
		else {
			m_player->AddMp(1.0f);
			m_se.Play(false);
			if (GetStatus()->m_Spawnnum <= 1)
			{
				if (hidame > 5)
				{
					m_moveVector.y = 200.0f;
					TransitionState(State_Hit);
				}
			}
			else {
				m_moveVector.y = 200.0f;
				TransitionState(State_Hit);
			}
		}
	}
}

void Enemy::DeleteHitobj()
{
	GetHitObjict().Deleteobjict(m_obj);
}
void Enemy::AIDecision()
{
	auto distance = m_player->Get2DPosition() - Get2DPosition();
	if (distance.Length() >= 300.0f)
	{
		SetFrontSpeed(1.0f);
		TransitionState(Enemy::State_Move);
	}
	else {
		std::random_device rnd;     // 非決定的な乱数生成器を生成
		std::mt19937 mt(rnd());     //  メルセンヌ・ツイスタの32ビット版、引数は初期シード値
		std::uniform_int_distribution<> rand100(0, 99);        // [0, 99] 範囲の一様乱数
		int wariai = rand100(mt) + 1;
		if (wariai > GetStatus()->m_Enemy_Priority->AttackPriority)
		{
			TransitionState(Enemy::State_Defens);
		}
		else
		{
			TransitionState(Enemy::State_Attack);

		}
	}
}
void Enemy::AIDefens(int kakudo)
{
	auto playerFront = m_player->GetFront();
	if (CMath::DegToRad(kakudo) >= acos(playerFront.Dot(m_Front)))
	{
		TransitionState(Enemy::State_Attack);
	}
}
void Enemy::AI(int& muki,int& kaku)
{
	std::random_device rnd;     // 非決定的な乱数生成器を生成
	std::mt19937 mt(rnd());     //  メルセンヌ・ツイスタの32ビット版、引数は初期シード値
	std::uniform_int_distribution<> rand2(10, 30);        // [0, 99] 範囲の一様乱数
	auto playerFront = m_player->GetFront();
	if (CMath::DegToRad(1.0) <= acos(playerFront.Dot(m_Front))) {
		CVector3 jiku;
		jiku.Cross(m_Front, playerFront);
		if (jiku.y < 0)
		{
			muki = 2.0;
		}
		else
		{
			muki = -2.0;
		}
	}
	kaku = rand2(mt);
}