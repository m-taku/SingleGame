#pragma once
#include"level/Level.h"
#include"Navimake.h"
#include"physics/PhysicsStaticObject.h"
class Stage: public Gameobject
{
public:
	Stage();
	~Stage();
	bool Load();
	void Update();
	void Draw();
private:
	PhysicsStaticObject Stege;
	SkinModel m_model;
	Level level; 
	Navimake* navimake;
};

