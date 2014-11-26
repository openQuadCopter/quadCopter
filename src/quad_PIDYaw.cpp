/*
 * quad_PIDYaw.cpp
 *
 *  Created on: Nov 22, 2014
 *      Author: javier
 */

#include <quad_PIDYaw.h>

#include <stdio.h>

PIDYaw::PIDYaw() : PID()
{
	m_init();
}

PIDYaw::~PIDYaw()
{

}

void PIDYaw::m_init()
{
	m_error_prev = m_error = m_error_sum = 0.0;
	m_Kp = 1.0;
	m_Ki = 0.01;
	m_Kd = 0.001;
	m_value = m_target = m_output = m_dt = 0.0;
}

void PIDYaw::setTarget(double target)
{
	m_target = target;
}

double PIDYaw::compute(double value, double dt)
{
	m_value = value;
	m_dt = dt;
	m_error_prev = m_error;

	m_error = m_target - m_value;
	m_error_sum += m_error * m_dt;

	double P = m_Kp * m_error;
	double I = m_Ki * m_error_sum;
	double D = m_Kd * ((m_error - m_error_prev) / m_dt);

	m_output = P + I + D;
	printf("PIDYaw : %f\n", m_output);

	return m_output;
}
