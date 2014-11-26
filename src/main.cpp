#include <stdio.h>
#include <quadCopter.h>
#include <RTIMUMPU9250.h>

int main()
{
	printf("######################################\n");
	printf("            QUADCOPTER                \n\n");
	quadCopter * test = new quadCopter();
	
	/*for(int i = -10; i < 11; i++)
	{
		test->compute(5.0);
		usleep(100*1000);
		printf("###########################\n");
	}*/

	/*RTIMUSettings *settings = new RTIMUSettings((char *)"RTIMULib.ini");
	RTIMU *imu = RTIMU::createIMU(settings);
	imu->IMUInit();

	RTIMU_DATA data;

	while(1)
	{
		imu->IMURead();
		data = imu->getIMUData();
		printf("DATA : %f %f %f \n", 180.0 * data.fusionPose.x() / _PI_, data.fusionPose.y(), data.fusionPose.z());
	}*/

	return 0;
}
