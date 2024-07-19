#include "Applicant.h"
#include "BMP280.h"

int main(void)
{	
	Unit_Init_All();
	while (1)
	{
		MPU_6050_DEMO();
	}
}
