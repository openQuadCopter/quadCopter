/*
 * quadIMU.h
 *
 *  Created on: Nov 25, 2014
 *      Author: javier
 */

#ifndef INCLUDE_QUADIMU_H_
#define INCLUDE_QUADIMU_H_

#include <RTIMUMPU9250.h>

#define _PI_	3.14159265

class quadIMU
{
public:
	quadIMU()
	{
		m_init();
	};
	virtual ~quadIMU();
	void getData(double *pose);
	void readFIFO();

private:
	bool m_init();
	RTIMUSettings 	*m_settings;
	RTIMU		 	*m_imu;
	RTIMU_DATA 		 m_data;

};

#endif /* INCLUDE_QUADIMU_H_ */
