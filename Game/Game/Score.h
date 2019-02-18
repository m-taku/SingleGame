#pragma once
#include"UI.h"
class Score : public Gameobject
{
public:
	Score();
	~Score();
	void SetScore()
	{
		m_num++;
	}
	//void SetUI(UI* ui)
	//{
	//	m_ui = ui;
	//}
	int Getnum()
	{
		return m_num;
	}
private:
	int m_num = 0;
	//UI* m_ui = nullptr;
};

