
#include "STD_TYPES.h"

#include "GPIO_interface.h"
#include "motor_interface.h"
#include "motor_config.h"
void HMotor_voidMotor_start(u8 motor_number, u8 status)
{
	switch(motor_number)
	{
		case 1:
			switch(status)
			{
				case ENTER:
					MGPIO_vWRITE_PIN(left_motors_port,motor_1_pin_1 ,HIGH);
					MGPIO_vWRITE_PIN(left_motors_port,motor_1_pin_2 ,LOW);
				break;

				case LEAVE:
					MGPIO_vWRITE_PIN(left_motors_port,motor_1_pin_1 ,LOW);
					MGPIO_vWRITE_PIN(left_motors_port,motor_1_pin_2 ,HIGH);
				break;
				default: break;
			}
		break;
		case 2:
			switch(status)
			{
				case ENTER:
					MGPIO_vWRITE_PIN(left_motors_port,motor_2_pin_1 ,HIGH);
					MGPIO_vWRITE_PIN(left_motors_port,motor_2_pin_2 ,LOW);
				break;

				case LEAVE:
					MGPIO_vWRITE_PIN(left_motors_port,motor_2_pin_1 ,LOW);
					MGPIO_vWRITE_PIN(left_motors_port,motor_2_pin_2 ,HIGH);
				break;
				default: break;
			}
		break;
		case 3:
			switch(status)
			{
				case ENTER:
					MGPIO_vWRITE_PIN(left_motors_port,motor_3_pin_1 ,HIGH);
					MGPIO_vWRITE_PIN(left_motors_port,motor_3_pin_2 ,LOW);
				break;

				case LEAVE:
					MGPIO_vWRITE_PIN(left_motors_port,motor_3_pin_1 ,LOW);
					MGPIO_vWRITE_PIN(left_motors_port,motor_3_pin_2 ,HIGH);
				break;
				default: break;
			}
		break;

		case 4:
			switch(status)
			{
				case ENTER:
					MGPIO_vWRITE_PIN(left_motors_port,motor_4_pin_1 ,HIGH);
					MGPIO_vWRITE_PIN(left_motors_port,motor_4_pin_2 ,LOW);
				break;

				case LEAVE:
					MGPIO_vWRITE_PIN(left_motors_port,motor_4_pin_1 ,LOW);
					MGPIO_vWRITE_PIN(left_motors_port,motor_4_pin_2 ,HIGH);
				break;
				default: break;
			}
		break;

		case 5:
			switch(status)
			{
				case ENTER:
					MGPIO_vWRITE_PIN(left_motors_port,motor_5_pin_1 ,HIGH);
					MGPIO_vWRITE_PIN(left_motors_port,motor_5_pin_2 ,LOW);
				break;

				case LEAVE:
					MGPIO_vWRITE_PIN(left_motors_port,motor_5_pin_1 ,LOW);
					MGPIO_vWRITE_PIN(left_motors_port,motor_5_pin_2 ,HIGH);
				break;
				default: break;
			}
		break;

		case 6:
			switch(status)
			{
				case ENTER:
					MGPIO_vWRITE_PIN(right_motors_port,motor_6_pin_1 ,HIGH);
					MGPIO_vWRITE_PIN(right_motors_port,motor_6_pin_2 ,LOW);
				break;

				case LEAVE:
					MGPIO_vWRITE_PIN(right_motors_port,motor_6_pin_1 ,LOW);
					MGPIO_vWRITE_PIN(right_motors_port,motor_6_pin_2 ,HIGH);
				break;
				default: break;
			}
		break;

		case 7:
			switch(status)
			{
				case ENTER:
					MGPIO_vWRITE_PIN(right_motors_port,motor_7_pin_1 ,HIGH);
					MGPIO_vWRITE_PIN(right_motors_port,motor_7_pin_2 ,LOW);
				break;

				case LEAVE:
					MGPIO_vWRITE_PIN(right_motors_port,motor_7_pin_1 ,LOW);
					MGPIO_vWRITE_PIN(right_motors_port,motor_7_pin_2 ,HIGH);
				break;
				default: break;
			}
		break;

		case 8:
			switch(status)
			{
				case ENTER:
					MGPIO_vWRITE_PIN(right_motors_port,motor_8_pin_1 ,HIGH);
					MGPIO_vWRITE_PIN(right_motors_port,motor_8_pin_2 ,LOW);
				break;

				case LEAVE:
					MGPIO_vWRITE_PIN(right_motors_port,motor_8_pin_1 ,LOW);
					MGPIO_vWRITE_PIN(right_motors_port,motor_8_pin_2 ,HIGH);
				break;
				default: break;
			}
		break;

		case 9:
			switch(status)
			{
				case ENTER:
					MGPIO_vWRITE_PIN(right_motors_port,motor_9_pin_1 ,HIGH);
					MGPIO_vWRITE_PIN(right_motors_port,motor_9_pin_2 ,LOW);
				break;

				case LEAVE:
					MGPIO_vWRITE_PIN(right_motors_port,motor_9_pin_1 ,LOW);
					MGPIO_vWRITE_PIN(right_motors_port,motor_9_pin_2 ,HIGH);
				break;
				default: break;
			}
		break;

		case 10:
			switch(status)
			{
				case ENTER:
					MGPIO_vWRITE_PIN(right_motors_port,motor_10_pin_1 ,HIGH);
					MGPIO_vWRITE_PIN(right_motors_port,motor_10_pin_2 ,LOW);
				break;
				case LEAVE:
					MGPIO_vWRITE_PIN(right_motors_port,motor_10_pin_1 ,LOW);
					MGPIO_vWRITE_PIN(right_motors_port,motor_10_pin_2 ,HIGH);
				break;
				default: break;
			}
		break;
		default: break;
	}
}
void HMotor_voidMotor_stop(u8 motor_number)
{
	switch(motor_number)
	{
		case 1:
			MGPIO_vWRITE_PIN(left_motors_port,motor_1_pin_1 ,LOW);
			MGPIO_vWRITE_PIN(left_motors_port,motor_1_pin_2 ,LOW);
		break;

		case 2:
			MGPIO_vWRITE_PIN(left_motors_port,motor_2_pin_1 ,LOW);
			MGPIO_vWRITE_PIN(left_motors_port,motor_2_pin_2 ,LOW);
		break;

		case 3:
			MGPIO_vWRITE_PIN(left_motors_port,motor_3_pin_1 ,LOW);
			MGPIO_vWRITE_PIN(left_motors_port,motor_3_pin_2 ,LOW);
		break;

		case 4:
			MGPIO_vWRITE_PIN(left_motors_port,motor_4_pin_1 ,LOW);
			MGPIO_vWRITE_PIN(left_motors_port,motor_4_pin_2 ,LOW);
		break;

		case 5:
			MGPIO_vWRITE_PIN(left_motors_port,motor_5_pin_1 ,LOW);
			MGPIO_vWRITE_PIN(left_motors_port,motor_5_pin_2 ,LOW);
		break;

		case 6:
			MGPIO_vWRITE_PIN(right_motors_port,motor_6_pin_1 ,LOW);
			MGPIO_vWRITE_PIN(right_motors_port,motor_6_pin_2 ,LOW);
		break;

		case 7:
			MGPIO_vWRITE_PIN(right_motors_port,motor_7_pin_1 ,LOW);
			MGPIO_vWRITE_PIN(right_motors_port,motor_7_pin_2 ,LOW);
		break;

		case 8:
			MGPIO_vWRITE_PIN(right_motors_port,motor_8_pin_1 ,LOW);
			MGPIO_vWRITE_PIN(right_motors_port,motor_8_pin_2 ,LOW);
		break;

		case 9:
			MGPIO_vWRITE_PIN(right_motors_port,motor_9_pin_1 ,LOW);
			MGPIO_vWRITE_PIN(right_motors_port,motor_9_pin_2 ,LOW);
		break;

		case 10:
			MGPIO_vWRITE_PIN(right_motors_port,motor_10_pin_1 ,LOW);
			MGPIO_vWRITE_PIN(right_motors_port,motor_10_pin_2 ,LOW);
		break;

		default: break;
	}
}
