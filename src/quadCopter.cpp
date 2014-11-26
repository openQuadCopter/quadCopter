#include <quadCopter.h>
#include <RTIMUMPU9250.h>

#include <stdio.h>
#include <pthread.h>

static pthread_attr_t attr;
sched_param paramThreadProcs;
static pthread_t threadIMU;
void* thread_IMU(void* data);


quadCopter::quadCopter()
{
	m_init();
}

quadCopter::~quadCopter()
{
	delete m_motorManager;
}

void quadCopter::m_init()
{
	m_mutexI2C = PTHREAD_MUTEX_INITIALIZER;

	if( m_i2c_moduleCheck() )
		m_motorManager = new MotorManager();
	else
		printf("[QuadCopter] Failed to load i2c module");


	m_imu = new quadIMU();

	m_PID[0] = new PIDRoll();
	m_PID[1] = new PIDPitch();
	m_PID[2] = new PIDYaw();

	m_readData[0] = 0.0;
	m_readData[1] = 0.0;
	m_readData[2] = 0.0;

	for(int i = 0; i<3; i++)
		m_PID[i]->setTarget(0.0);

	pthread_attr_init(&attr);
	int newprio = -20;
	paramThreadProcs.sched_priority = newprio;
	pthread_attr_setschedparam (&attr, &paramThreadProcs);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
	pthread_attr_setschedpolicy(&attr, SCHED_FIFO);
	pthread_attr_setscope(&attr, PTHREAD_SCOPE_PROCESS);
	//sleep(6);
	pthread_create(&threadIMU, &attr, thread_IMU, this);


	double cmd[4]={1200.0, 1200.0, 1200.0, 1200.0};
	sendCommand(cmd);
	sleep(5);
	/*while(1)
	{
		compute();
		usleep(100*1000);
	}*/

}

void* thread_IMU(void* data)
{
	quadCopter *quad = (quadCopter *)data;
	while(1)
	{
		pthread_mutex_lock(quad->getMutex());

		quad->readIMU();

		pthread_mutex_unlock(quad->getMutex());
		usleep(5*1000);
	}
}

void quadCopter::readIMU()
{
	m_imu->readFIFO();
}

void quadCopter::getDataIMU()
{
	m_imu->getData(m_readData);
}

void quadCopter::compute()
{
	pthread_mutex_lock(&m_mutexI2C);

	getDataIMU();

	double output = m_PID[0]->compute(m_readData[0], 0.09); // getting output of PIDRoll

	double throttle = 1400.0;
	double cmd[4] = {0.0, 0.0, 0.0, 0.0};

	cmd[0] = throttle - output;
	cmd[1] = throttle + output;
	cmd[2] = throttle + output;
	cmd[3] = throttle - output;

	sendCommand(cmd);

	pthread_mutex_unlock(&m_mutexI2C);
}

void quadCopter::sendCommand(double *cmd)
{
	m_motorManager->sendCommandMicro(cmd);
}

bool quadCopter::m_i2c_moduleCheck()
{
	bool val = false;
	FILE *file = fopen("/proc/modules", "r");
	char temp[512] = "";
	char i2c[] = "i2c_dev";

	while(fgets(temp, 512, file) != NULL) {
		if((strstr(temp, i2c)) != NULL)
			return val = true;
	}
	// TODO: i2c Module is not loaded, then we have to load it
	return val;
}
