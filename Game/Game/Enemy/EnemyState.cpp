#include "stdafx.h"
#include "EnemyState.h"
#include"../Player/Player.h"
#include"Enemy.h"

EnemyState::EnemyState(Enemy* enemy_point,Player* pla)
{
	enemy = enemy_point;
	player = pla;
}
EnemyState::~EnemyState()
{
}

void EnemyState::Findangle(CVector3 Front)
{
	auto debag = enemy->Get2DFront();
	auto Angle = acos(debag.Dot(Front));
	if (Angle >= CMath::DegToRad(5.0f))
	{
		auto ka5 = CVector3::Zero();
		ka5.Cross(debag, Front);
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
			ma3.SetRotationDeg(ka5, kaku);
		}
		enemy->AddAngle(ma3);
	}
}