#pragma once
class Enemy;
class Player;
class EnemyState
{
public:
	EnemyState(Enemy* enemy_point, Player* pla);
	virtual ~EnemyState();
	virtual void Update() = 0;
protected:
	Enemy* enemy=nullptr;			//エネミーのインスタンス
	Player* player=nullptr;			//プレイヤーのインスタンス
};

