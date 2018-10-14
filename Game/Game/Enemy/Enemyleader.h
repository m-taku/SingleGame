#pragma once
#include"../Player.h"
#include "character/CharacterController.h"
class Enemy;
class Enemyleader:public Gameobject
{
public:
	Enemyleader();
	~Enemyleader();

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
	
private:
	CVector3 haiti[5] = { { 70.0f,0.0f,70.0f },{ -70.0f,0.0f,70.0f },{ -70.0f,0.0f,-70.0f },{ 70.0f,0.0f,0.0f } };
	CVector3 position = { 0.0f,100.0f,0.0f };
	CharacterController m_collider;
	SkinModel m_model;
	static const int SOLDIER = 2;
	Player* player;
	std::vector<Enemy*> enemy;
	int remaining = SOLDIER;
};

