#pragma once
#include "stdafx.h"
struct Enemy_ActionPriority : public Noncopyable{
public:
	float AttackPriority = 30.0f;
	float DefensePriority = 20.0f;
	float freedomPriority = 50.0f;
};
