#ifndef MOTOR_INTERFACE_H
#define MOTOR_INTERFACE_H



#define ENTER		1
#define LEAVE		0

#define MOTOR_1		1
#define MOTOR_2		2
#define MOTOR_3		3
#define MOTOR_4		4
#define MOTOR_5		5
#define MOTOR_6		6
#define MOTOR_7		7
#define MOTOR_8		8
#define MOTOR_9		9
#define MOTOR_10	10


void HMotor_voidMotor_start(u8 motor_number, u8 status);
void HMotor_voidMotor_stop(u8 motor_number);

#endif
