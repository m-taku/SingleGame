#pragma once
#include "character/CharacterController.h"
#include"Gameobject/Gameobject.h"
class Player: public Gameobject
{
public:
	Player();
	~Player();
	bool Load();
	void Update();
	void Draw();
private:
	SkinModel m_model;									//スキンモデル。
};

