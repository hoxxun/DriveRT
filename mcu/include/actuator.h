//STM32로 가져갈 것
#ifndef ACTUATOR_H
#define ACTUATOR_H

#include "../../common/include/command.h"

typedef enum 
{
    MOTOR_OFF, 
    MOTOR_ON
} Motor;

typedef struct 
{
    int pwm;
    Motor motor;
    Direction direction;
} Actuator;

#endif