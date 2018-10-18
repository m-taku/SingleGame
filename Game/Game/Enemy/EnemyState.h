#pragma once
class Enemy;
class Player;
class EnemyState
{
public:
	EnemyState(Enemy* enemy_point, Player* pla);
	~EnemyState();
	virtual void Update() = 0;
	void Findangle(CVector3 Front);
protected:
	Enemy* enemy=nullptr;
	Player* player=nullptr;
	static const int kaku = 20;
	float m_margin = CMath::DegToRad(kaku);
};

