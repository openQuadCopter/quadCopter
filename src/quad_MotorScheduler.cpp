#include "quad_MotorScheduler.h"

#include <stdio.h>

Motor_scheduler::Motor_scheduler()
{
	m_init();
}

Motor_scheduler::~Motor_scheduler()
{
	
}
	
bool Motor_scheduler::sendCommand()
{
	
}
	
bool Motor_scheduler::m_init()
{
	m_isInitialized = false;
	for(int i = 0 ; i < NB_MOTORS ; i++)
		m_motors[i] = new Motor();
	
	m_isInitialized = true;
	printf("[Motor_scheduler]\t Motors initialized\n");
}
