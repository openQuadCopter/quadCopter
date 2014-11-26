/*
 * quad_PIDYaw.h
 *
 *  Created on: Nov 22, 2014
 *      Author: javier
 */

#ifndef INCLUDE_QUAD_PIDYAW_H_
#define INCLUDE_QUAD_PIDYAW_H_

#include <quad_PID.h>

class PIDYaw: virtual public PID
{
public:
	PIDYaw();
	virtual ~PIDYaw();

	virtual double 	compute(double value, double dt);
	virtual void 	setTarget(double target);

private:
	virtual void 	m_init();
};

#endif /* INCLUDE_QUAD_PIDYAW_H_ */
