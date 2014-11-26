/*
 * quad_PID.h
 *
 *  Created on: Nov 22, 2014
 *      Author: javier
 */

#ifndef INCLUDE_QUAD_PID_H_
#define INCLUDE_QUAD_PID_H_

class PID
{
public:
	PID(){};
	virtual ~PID(){};

	virtual void 	setTarget(double target) = 0;
	virtual double 	compute(double value, double dt) = 0;

protected:
	double	m_target;
	double 	m_value;

	double	m_Kp;
	double	m_Ki;
	double	m_Kd;

	double 	m_error;
	double	m_error_prev;
	double	m_error_sum;
	double	m_dt;

	double 	m_output;

	virtual void 	m_init() = 0;
};

#endif /* INCLUDE_QUAD_PID_H_ */
