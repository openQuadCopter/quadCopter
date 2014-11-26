#ifndef QUAD_MOTOR_H
#define QUAD_MOTOR_H

#define		MIN_SPEED	60
#define		MAX_SPEED	117

class Motor
{
	public:
	Motor();
	~Motor();
	
	void setSpeed(unsigned int speed);
	unsigned int getSpeed();
	bool hasPendingCmd();
	bool isReady();
	bool reset();
	
	
	private:
	unsigned int	m_speed;
	bool	m_isInitialized;
	bool	m_pendingCmd;
	
	bool	m_init();
	
};

#endif /* QUAD_MOTOR_H */
