#pragma once
class Gameobject : Noncopyable
{
public:
	Gameobject();
	~Gameobject();
	virtual bool Load() { return true; };
	virtual void Update() = 0;
	virtual void Draw() = 0;
	virtual void postDraw() {};
	int Getpriority()
	{
		return priority;
	}
	void setpriority(int No)
	{
		priority = No;
	}
	bool GetLodefrag()
	{
		return Loadfrag;
	}
	void SetLoadfrag(bool frag)
	{
		Loadfrag = frag;
	}
	bool GetDrewfragu()
	{
		return Drewfragu;
	}
private:
	int priority = 0;
protected:
	bool Loadfrag = false;
	bool Drewfragu = true;
};

