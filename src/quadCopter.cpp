#include <quadCopter.h>
#include <RTIMUMPU9250.h>

#include <stdio.h>

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
	m_imu = new quadIMU();

	if( m_i2c_moduleCheck() )
		m_motorManager = new MotorManager(m_imu->getMutex());
	else
		printf("[QuadCopter] Failed to load i2c module");

	m_PID[0] = new PIDRoll();
	m_PID[1] = new PIDPitch();
	m_PID[2] = new PIDYaw();

	m_readData[0] = 0.0;
	m_readData[1] = 0.0;
	m_readData[2] = 0.0;

	for(int i = 0; i<3; i++)
		m_PID[i]->setTarget(0.0);



	while(1)
	{
		compute();
	}

}

void quadCopter::compute()
{
	m_imu->getData(m_readData);

	double output = m_PID[0]->compute(m_readData[0], 0.1);

	int throttle = 1300;
	int cmd[4] = {0, 0, 0, 0};
	cmd[0] = throttle - output;
	cmd[1] = throttle + output;
	cmd[2] = throttle + output;
	cmd[3] = throttle - output;

	sendCommand(cmd);
}

void quadCopter::sendCommand(int *cmd)
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
