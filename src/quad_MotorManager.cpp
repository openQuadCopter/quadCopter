#include <quad_MotorManager.h>
#include <stdio.h>

MotorManager::MotorManager(pthread_mutex_t *mutex)
{
	m_mutex = mutex;
	m_init();
}

MotorManager::~MotorManager()
{
	close(m_i2c_file);
}

bool MotorManager::sendCommandInit(int fl, int fr, int br, int bl)
{
	//if( m_isInitialized )
	//{
	unsigned char cmd[NB_MOTORS];
	cmd[0] = (unsigned char)(fl);
	cmd[1] = (unsigned char)(fr);
	cmd[2] = (unsigned char)(br);
	cmd[3] = (unsigned char)(bl);
	i2c_smbus_write_i2c_block_data(m_i2c_file, I2C_MOTOR_INIT, NB_MOTORS, cmd);
	//usleep(10*1000);
	//}
	//return false;
}

bool MotorManager::sendCommandMicro(int fl, int fr, int br, int bl)
{
	//if( m_isInitialized )
	//{
	pthread_mutex_lock(m_mutex);
	unsigned char cmd[NB_MOTORS * 2];
	cmd[0] = (unsigned char)(abs(fl / 100));
	cmd[1] = (unsigned char)(abs(fl % 100));
	cmd[2] = (unsigned char)(abs(fr / 100));
	cmd[3] = (unsigned char)(abs(fr % 100));
	cmd[4] = (unsigned char)(abs(br / 100));
	cmd[5] = (unsigned char)(abs(br % 100));
	cmd[6] = (unsigned char)(abs(bl / 100));
	cmd[7] = (unsigned char)(abs(bl % 100));
	i2c_smbus_write_i2c_block_data(m_i2c_file, I2C_MOTOR_CMD, NB_MOTORS, cmd);
	pthread_mutex_unlock(m_mutex);
	//usleep(10*1000);
	//}
	//return false;
}

bool MotorManager::sendCommandMicro(int *motorcmd)
{

	pthread_mutex_lock(m_mutex);
	unsigned char cmd[NB_MOTORS * 2];
	int u = 0;
	for(int i = 0 ; i < NB_MOTORS ; i++)
	{
		if(motorcmd[i] > MOTOR_MAX_CMD)
			motorcmd[i] = MOTOR_MAX_CMD;
		if(motorcmd[i] < MOTOR_MIN_CMD)
			motorcmd[i] = MOTOR_MIN_CMD;

		cmd[u] = (unsigned char)(abs(motorcmd[i] / 100));
		cmd[u+1] = (unsigned char)(abs(motorcmd[i] % 100));;
		u += 2;
	}

	printf("sending command...\n");
	i2c_smbus_write_i2c_block_data(m_i2c_file, I2C_MOTOR_CMD, NB_MOTORS, cmd);

	pthread_mutex_unlock(m_mutex);
	//}
//return false;
}

bool MotorManager::m_init()
{
	m_isInitialized = false;

	if( m_init_i2c() )
	{
		if( m_send_init_cmd() )
		{
			printf("[Motor_manager]\t Motors initialized\n");
			m_isInitialized = true;
		}
	}

	return m_isInitialized;
}


bool MotorManager::m_init_i2c()
{
	bool val = true;

	if( (m_i2c_file = open(I2C_FILENAME, O_WRONLY|O_NONBLOCK)) < 0 )
	{
		printf("[MotorManager]\tFailed to open the i2c bus\n");
		val = false;
	}
	else
	{
		printf("[MotorManager]\tI2C file well opened\n");
		if ( ioctl(m_i2c_file, I2C_SLAVE, I2C_SLAVE_ADDR) < 0 ) {
			printf("[MotorManager]\tFailed to acquire bus access and/or talk to slave.\n");
			val = false;
		}
		else
			printf("[MotorManager]\tI2C bus well opened\n");
	}

	return val;
}


bool MotorManager::m_send_init_cmd()
{

	pthread_mutex_lock(m_mutex);
	sendCommandInit(0, 0, 0, 0);
	sleep(2);

	sendCommandInit(10, 10, 10, 10);
	sleep(2);

	sendCommandInit(60, 60, 60, 60);
	sleep(2);

	pthread_mutex_unlock(m_mutex);

	return true;
}
