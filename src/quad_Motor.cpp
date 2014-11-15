#include "quad_Motor.h"

#include <stdio.h>


Motor::Motor()
{
	printf("[quad_MOTOR]\t\t Creating Motor\n");
	m_init();
}

Motor::~Motor()
{
	
}

bool Motor::m_init()
{
	m_isInitialized = false;
	setSpeed(MIN_SPEED);
		
	m_isInitialized = true;
	return m_isInitialized;
}
	
void Motor::setSpeed(unsigned int speed)
{
	if(speed < MIN_SPEED)
		m_speed = MIN_SPEED;
	else if(speed > MAX_SPEED)
		m_speed = MAX_SPEED;
	else
		m_speed = speed;
		
	m_pendingCmd = true;
}

unsigned int Motor::getSpeed()
{
	return m_speed;
}

bool Motor::hasPendingCmd()
{
	return m_pendingCmd;
}

bool Motor::isReady()
{
	return m_isInitialized;
}

bool Motor::reset()
{
	
}
