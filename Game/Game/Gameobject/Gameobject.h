#pragma once
class Gameobject : Noncopyable
{
public:
	Gameobject();
	virtual ~Gameobject();
	virtual bool Load() { return true; };		//データのロード
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
	/*
	*@brief	ロードが完了したか
	*@return bool
	*/
	void SetLoadfrag(bool frag)
	{
		Loadfrag = frag;
	}
	/*
	*@brief	表示するかしないか
	*@return bool
	*/
	bool GetDrewfragu()
	{
		return Drewfragu;
	}
private:
	int priority = 0;
protected:
	bool Loadfrag = false;			//ロード完了したか
	bool Drewfragu = true;			//表示したいか（）
};

