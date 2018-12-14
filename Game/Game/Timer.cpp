#include "stdafx.h"
#include "Timer.h"


Timer::Timer()
{
}


Timer::~Timer()
{
}
void Timer::TimerStart()
{
	::QueryPerformanceCounter((LARGE_INTEGER*)&m_start);
	m_Allelapsed = 0.0f;
	m_elapsed = 0.0f;
}

void Timer::TimerRestart()
{
	::QueryPerformanceCounter((LARGE_INTEGER*)&m_start);
}
void Timer::TimerStop()
{
	double oldelapsed = 0.0;
	::QueryPerformanceFrequency((LARGE_INTEGER*)&m_fleam);
	::QueryPerformanceCounter((LARGE_INTEGER*)&m_stop);
	oldelapsed = m_elapsed;
	m_elapsed = double(m_stop - m_start) / m_fleam;
	m_Allelapsed += (m_elapsed - oldelapsed);
}