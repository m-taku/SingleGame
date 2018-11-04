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
	Enemy* enemy=nullptr;			//�G�l�~�[�̃C���X�^���X
	Player* player=nullptr;			//�v���C���[�̃C���X�^���X
};

