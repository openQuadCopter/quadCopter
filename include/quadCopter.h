#ifndef QUADCOPTER_H
#define QUADCOPTER_H

#include <quad_MotorManager.h>
#include <quad_PID.h>
#include <quad_PIDRoll.h>
#include <quad_PIDPitch.h>
#include <quad_PIDYaw.h>
#include <quad_IMU.h>

#include <pthread.h>

#define _PI_ 3.14159265

class quadCopter
{
public:
	quadCopter();
	~quadCopter();

	void sendCommand(double *cmd);
	void compute();

	void readIMU();
	void getDataIMU();
	pthread_mutex_t *getMutex(){return &m_mutexI2C;};

private:
	void m_init();
	bool m_i2c_moduleCheck();

	MotorManager	*m_motorManager;
	quadIMU			*m_imu;
	PID 			*m_PID[3];

	pthread_mutex_t m_mutexI2C;

	double			m_readData[3];
	double 			m_throttle;
};

#endif /* QUADCOPTER_H */
