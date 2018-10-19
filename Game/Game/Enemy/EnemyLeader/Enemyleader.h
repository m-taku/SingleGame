#pragma once
#include"../../Player/Player.h"
#include "character/CharacterController.h"
#include"../../Path.h"
class Enemy;
class Enemyleader:public Gameobject
{
public:
	Enemyleader();
	~Enemyleader();
	enum {
	};
	void Setposition(CVector3 Position)
	{
		position = Position;
	}
	SkinModel& GetSkinmdel()
	{
		return m_model;
	}
	void Setplayer(Player* pa)
	{
		player = pa;
	}
	bool Load();
	void Update();
	void Draw();
	void move();
private:
	CVector3 haiti[5] = { { 70.0f,0.0f,0.0f },{ -70.0f,0.0f,70.0f },{ -70.0f,0.0f,-70.0f },{ 70.0f,0.0f,-70.0f },{0.0f,0.0f,70.0f} };
	CVector3 position = { 0.0f,100.0f,0.0f };
	Path* path=nullptr;
	CVector3 m_nextpos = CVector3::Zero();
	CVector3 m_oldposition = CVector3::Zero();
	CharacterController m_collider;
	SkinModel m_model;
	static const int SOLDIER = 5;
	Player* player;
	std::vector<Enemy*> enemy;
	int remaining = SOLDIER;

	int m_time = 0;		//âºÅHÅH
};

