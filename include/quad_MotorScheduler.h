#ifndef MOTOR_SCHEDULER_H
#define MOTOR_SCHEDULER_H

#include "quad_Motor.h"

#define NB_MOTORS 4

class Motor_scheduler
{
	public:
	Motor_scheduler();
	~Motor_scheduler();
	
	bool sendCommand();
	
	
	private:
	Motor*  m_motors[NB_MOTORS];	// [front left, front right, back left, back right]
	bool	m_isInitialized;
	
	bool m_init();
};

#endif /* MOTOR_SCHEDULER_H */
