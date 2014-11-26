/*
 * quad_PIDRoll.h
 *
 *  Created on: Nov 22, 2014
 *      Author: javier
 */

#ifndef INCLUDE_QUAD_PIDROLL_H_
#define INCLUDE_QUAD_PIDROLL_H_

#include <quad_PID.h>

class PIDRoll: virtual public PID
{
public:
	PIDRoll();
	virtual ~PIDRoll();

	virtual double 	compute(double value, double dt);
	virtual void 	setTarget(double target);

private:
	virtual void 	m_init();
};

#endif /* INCLUDE_QUAD_PIDROLL_H_ */
