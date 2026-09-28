#ifndef ACTUATOR_H
#define ACTUATOR_H

#include "state_machine.h"
#include "command.h"

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

void updateActuator(State current_state, Command cmd);

extern Actuator actuator;

#endif