#include "state_machine.h"
#include "actuator.h"

Actuator actuator = {0, MOTOR_OFF, 0};

void updateActuator(State current_state, Command cmd)
{
    switch (current_state)
    {
    case STATE_STOP:
        actuator.pwm = 0;
        actuator.motor = MOTOR_OFF;
        break;
    
    case STATE_RUNNING:
        actuator.pwm = cmd.speed;
        actuator.motor = MOTOR_ON;
        actuator.direction = cmd.direction;
        break;

    case STATE_ERROR:
        actuator.pwm = 0;
        actuator.motor = MOTOR_OFF;
        break;
    
    case STATE_RECOVERY:
        actuator.pwm = 0;
        actuator.motor = MOTOR_OFF;
        break;
    }
}