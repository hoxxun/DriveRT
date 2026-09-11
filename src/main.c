#include <stdio.h>
#include "../include/state_machine.h"
#include "../include/actuator.h"

Actuator actuator = {0, MOTOR_OFF};

const char * state_buf[] = {
    "STATE_STOP",
    "STATE_RUNNING",
    "STATE_ERROR",
    "STATE_RECOVERY"
};

const char * motor_buf[] = {
    "MOTOR_OFF",
    "MOTOR_ON"
};


void stateHandler(State current_state)
{
    switch (current_state)
    {
    case STATE_STOP:
        printf("[LOG] current state: %s\n", state_buf[current_state]);

        actuator.pwm = 0;
        printf("\tpwm : %d\n", actuator.pwm);

        actuator.motor = MOTOR_OFF;
        printf("\tmotor : %s\n", motor_buf[actuator.motor]);
        break;
    
    case STATE_RUNNING:
        printf("[LOG] current state: %s\n", state_buf[current_state]);  

        actuator.pwm = 70;
        printf("\tpwm : %d\n", actuator.pwm);

        actuator.motor = MOTOR_ON;
        printf("\tmotor : %s\n", motor_buf[actuator.motor]);
        break;

    case STATE_ERROR:
        printf("[LOG] current state: %s\n", state_buf[current_state]);  

        actuator.pwm = 0;
        printf("\tpwm : %d\n", actuator.pwm);

        actuator.motor = MOTOR_OFF;
        printf("\tmotor : %s\n", motor_buf[actuator.motor]);

        printf("\t오류 원인 확인중...\n");
        printf("\t오류 원인 확인\n");
        break;
    
    case STATE_RECOVERY:
        printf("[LOG] current state: %s\n", state_buf[current_state]);  

        actuator.pwm = 0;
        printf("\tpwm : %d\n", actuator.pwm);

        actuator.motor = MOTOR_OFF;
        printf("\tmotor : %s\n", motor_buf[actuator.motor]);
        printf("\t오류 복구 시작\n");
        break;
    }
}


int main(void)
{
    State current_state = STATE_STOP;

    current_state = getNextState(current_state, EVENT_RUN);
    stateHandler(current_state);

    current_state = getNextState(current_state, EVENT_FAULT);
    stateHandler(current_state);

    current_state = getNextState(current_state, EVENT_RECOVER);
    stateHandler(current_state);

    current_state = getNextState(current_state, EVENT_RECOVERY_OK);
    stateHandler(current_state);

    return 0;
}