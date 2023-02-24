


#include "STD_TYPES.h"
#include "sensor_config.h"
#include "sensor_interface.h"
#include "GPIO_interface.h"

u8 HSENSOR_u8SensorStatus(u8 sensor_number)
{
	u8 L_u8Sensor_Status = 0;

	switch(sensor_number)
	{
		case 0:
			L_u8Sensor_Status = MGPIO_u8READ_PIN(sensors_port,sensor_entry);
		break;
		case 1:
			L_u8Sensor_Status = MGPIO_u8READ_PIN(sensors_port,sensor1_pin);
		break;

		case 2:
			L_u8Sensor_Status = MGPIO_u8READ_PIN(sensors_port,sensor2_pin);
		break;

		case 3:
			L_u8Sensor_Status = MGPIO_u8READ_PIN(sensors_port,sensor3_pin);
		break;

		case 4:
			L_u8Sensor_Status = MGPIO_u8READ_PIN(sensors_port,sensor4_pin);
		break;

		case 5:
			L_u8Sensor_Status = MGPIO_u8READ_PIN(sensors_port,sensor5_pin);
		break;

		case 6:
			L_u8Sensor_Status = MGPIO_u8READ_PIN(sensors_port,sensor6_pin);
		break;

		case 7:
			L_u8Sensor_Status = MGPIO_u8READ_PIN(sensors_port,sensor7_pin);
		break;
		case 8:
			L_u8Sensor_Status = MGPIO_u8READ_PIN(sensors_port,sensor8_pin);
		break;

		case 9:
			L_u8Sensor_Status = MGPIO_u8READ_PIN(sensors_port,sensor9_pin);
		break;

		case 10:
			L_u8Sensor_Status = MGPIO_u8READ_PIN(sensors_port,sensor10_pin);
		break;


		default: break;
	}

	return L_u8Sensor_Status;

}
