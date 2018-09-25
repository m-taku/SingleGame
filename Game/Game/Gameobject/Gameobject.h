#pragma once
class Gameobject
{
private:
	virtual bool Load() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;
public:
	Gameobject();
	~Gameobject();

};

