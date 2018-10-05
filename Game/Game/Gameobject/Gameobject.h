#pragma once
class Gameobject : Noncopyable
{
public:
	Gameobject();
	virtual ~Gameobject();
	virtual bool Load() { return true; };		//�f�[�^�̃��[�h
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
	*@brief	���[�h������������
	*@return bool
	*/
	void SetLoadfrag(bool frag)
	{
		Loadfrag = frag;
	}
	/*
	*@brief	�\�����邩���Ȃ���
	*@return bool
	*/
	bool GetDrewfragu()
	{
		return Drewfragu;
	}
private:
	int priority = 0;
protected:
	bool Loadfrag = false;			//���[�h����������
	bool Drewfragu = true;			//�\�����������i�j
};

