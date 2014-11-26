#ifndef MOTORMANAGER_H
#define MOTORMANAGER_H

#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#ifdef BUILD_HOST
#include <linux/i2c-dev.h>
#else
#include <linux/i2c-dev-user.h>
#endif
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define NB_MOTORS		4
#define	I2C_FILENAME	"/dev/i2c-1"
#define I2C_SLAVE_ADDR	0x04
#define I2C_MOTOR_CMD	0x01
#define I2C_MOTOR_INIT	0x00
#define I2C_MOTOR_RESET	0x02
#define I2C_MOTOR_STOP	0x03

#define MOTOR_MAX_CMD	1690
#define MOTOR_MIN_CMD	1190
#define MOTOR_INIT_CMD	10
#define MOTOR_RESET_CMD	0

class MotorManager
{
	public:
	MotorManager();
	~MotorManager();
	
	bool sendCommandInit(int fl, int fr, int br, int bl);
	bool sendCommandMicro(int *motorcmd);
	bool sendCommandMicro(int fl, int fr, int br, int bl);
	
	
	private:
	int		m_motorCmd[NB_MOTORS];		// current cmd [front left, front right, back right, back left]
	int		m_motorCmd_prev[NB_MOTORS];	// previous cmd [front left, front right, back right, back left]
	bool	m_isInitialized;
	int		m_i2c_file;
	
	bool m_init();
	bool m_init_i2c();
	bool m_send_init_cmd();
	bool m_send_reset_cmd();
};

#endif /* MOTORMANAGER_H */
