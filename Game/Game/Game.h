#pragma once
class Player;
class Gamecamera;
class Game : public Gameobject
{
public:
	Game();
	~Game();
	bool Load();
	void Update();
	void Draw();

private:
	Player * player;
	Gamecamera* Camera;
};

