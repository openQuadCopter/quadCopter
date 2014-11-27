/*
 * quadIMU.cpp
 *
 *  Created on: Nov 25, 2014
 *      Author: javier
 */

#include "../include/quad_IMU.h"


quadIMU::~quadIMU()
{
	// TODO Auto-generated destructor stub
}


bool quadIMU::m_init()
{
	bool val = false;
	m_settings = new RTIMUSettings((char *)"RTIMULib.ini");
	m_imu = RTIMU::createIMU(m_settings);
	m_imu->setAccelEnable(true);
	m_imu->setGyroEnable(true);
	m_imu->setCompassEnable(false);
	//m_imu->setSampleRate(500);
	val = m_imu->IMUInit();
	m_imu->setAccelEnable(true);
	m_imu->setGyroEnable(true);
	m_imu->setCompassEnable(false);

	return val;
}



void quadIMU::readFIFO()
{
	while(!m_imu->IMURead()){}
	//printf("Reading IMU\n");
}

void quadIMU::getData(double *pose)
{
	m_data	= m_imu->getIMUData();
	RTVector3 v = m_imu->getMeasuredPose();

	pose[0] = 180.0 * v.x() / _PI_;
	pose[1] = 180.0 * v.y() / _PI_;
	pose[2] = 180.0 * v.z() / _PI_;

	if(pose[0] > 0)
		pose[0] = -(pose[0] -180.0);
	else
		pose[0] = -(pose[0] + 180.0);
	printf("POSE : %f  %f  %f\n", pose[0], pose[1], pose[2]);
}
