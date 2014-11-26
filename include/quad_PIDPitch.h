/*
 * quad_PIDPitch.h
 *
 *  Created on: Nov 22, 2014
 *      Author: javier
 */

#ifndef INCLUDE_QUAD_PIDPITCH_H_
#define INCLUDE_QUAD_PIDPITCH_H_

#include <quad_PID.h>

class PIDPitch: virtual public PID
{
public:
	PIDPitch();
	virtual ~PIDPitch();

	virtual double 	compute(double value, double dt);
	virtual void 	setTarget(double target);

private:
	virtual void 	m_init();
};

#endif /* INCLUDE_QUAD_PIDPITCH_H_ */
