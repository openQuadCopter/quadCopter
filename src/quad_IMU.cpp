/*
 * quadIMU.cpp
 *
 *  Created on: Nov 25, 2014
 *      Author: javier
 */

#include "../include/quad_IMU.h"

static pthread_attr_t 		attr;
sched_param 				paramThreadProcs;
static pthread_t 			threadIMU;
void* thread_IMU(void* data);


quadIMU::~quadIMU()
{
	// TODO Auto-generated destructor stub
}


bool quadIMU::m_init()
{
	bool val = false;
	m_settings = new RTIMUSettings((char *)"RTIMULib.ini");
	m_imu = RTIMU::createIMU(m_settings);
	//m_imu->setAccelEnable(true);
	//m_imu->setGyroEnable(true);
	//m_imu->setSampleRate(500);
	val = m_imu->IMUInit();

	pthread_attr_init(&attr);
	int newprio = 0;
	paramThreadProcs.sched_priority = newprio;
	pthread_attr_setschedparam (&attr, &paramThreadProcs);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
	pthread_attr_setschedpolicy(&attr, SCHED_FIFO);
	pthread_attr_setscope(&attr, PTHREAD_SCOPE_PROCESS);
	pthread_create(&threadIMU, &attr, thread_IMU, this);

	return val;
}

void* thread_IMU(void* data)
{
	quadIMU *imu = (quadIMU*)data;
	while(1)
	{
		pthread_mutex_trylock(imu->getMutex());
		printf("Locking for reading data\n");
		imu->read();
		printf("Unlocking for reading data\n");
		pthread_mutex_unlock(imu->getMutex());
		usleep(10*1000);
	}
	return NULL;
}

void quadIMU::read()
{
	m_imu->IMURead();
	printf("Reading IMU\n");
}

void quadIMU::getData(double *pose)
{
	pthread_mutex_lock(getMutex());
	printf("Locking for getting data\n");
		m_data	= m_imu->getIMUData();

		pose[0] = 180.0 * m_data.fusionPose.x() / _PI_;
		pose[1] = 180.0 * m_data.fusionPose.y() / _PI_;
		pose[2] = 180.0 * m_data.fusionPose.z() / _PI_;

		if(pose[0] < 0)
			pose[0] += 180.0;
		else
			pose[0] -= 180.0;

		pose[0] *= -1;
		//printf("POSE : %f  %f  %f\n", pose[0], pose[1], pose[2]);
		printf("Unocking for getting data\n");

	pthread_mutex_unlock(getMutex());
}
