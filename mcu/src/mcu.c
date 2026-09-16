//전체적으로 MCU 코드여서 STM32로 가져감
//근데 LOG를 찍는 (printf) 같은 건 수정을 해야 될 듯

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "../../common/include/command.h"
#include "../include/state_machine.h"
#include "../include/actuator.h"

#define SUCCESS 1
#define FAIL -1

Actuator actuator = {0, MOTOR_OFF};


//LOG
static const char * state_str[] = {
    "STATE_STOP",
    "STATE_RUNNING",
    "STATE_ERROR",
    "STATE_RECOVERY"
};

//LOG
static const char * motor_str[] = {
    "MOTOR_OFF",
    "MOTOR_ON"
};

//LOG
static const char * direction_str[] = {
    "FORWARD",
    "BACKWARD"
};

void receive_commandMessage();
int receive_heartbeat();

int parseCommandMessage(char * buf, Command * cmd)
{
    char * cmdType = strtok(buf, ",");
    if(cmdType == NULL)
        return FAIL;

    if(strcmp(cmdType, "MOVE")==0)
    {
        char * cmdSpeed = strtok(NULL, ",");
        if(cmdSpeed == NULL) 
            return FAIL;

        char * cmdDirection = strtok(NULL, ",");
        if(cmdDirection ==  NULL)
            return FAIL;

        cmd->type = CMD_MOVE;


        char * end;
        long speed = strtol(cmdSpeed, &end, 10);
        if(end == cmdSpeed)
            return FAIL;
        if(*end != '\0')
            return FAIL;
        cmd->speed = speed;


        if(strcmp(cmdDirection,"FORWARD")==0)
        {   
            cmd->direction = DIR_FORWARD;
            printf("\n");
            printf("[MCU] Command Message 파싱\n");
            printf("\n");

            return SUCCESS;
        }
        else if(strcmp(cmdDirection,"BACKWARD")==0)
        {
            cmd->direction = DIR_BACKWARD;
            printf("\n");
            printf("[MCU] Command Message 파싱\n");
            printf("\n");

            return SUCCESS;
        }
        else    
            return FAIL;
    }

    else if(strcmp(cmdType, "STOP")==0)
    {
        cmd->type = CMD_STOP;
        cmd->speed = 0;
        printf("\n");
        printf("[MCU] Command Message 파싱\n");
        printf("\n");

        return SUCCESS;
    }

    else 
        return FAIL;
    
}

void updateActuator(State current_state, Command cmd)
{
    switch (current_state)
    {
    case STATE_STOP:
        printf("[LOG] current state: %s\n", state_str[current_state]);

        actuator.pwm = 0;
        printf("\tpwm : %d\n", actuator.pwm);

        actuator.motor = MOTOR_OFF;
        printf("\tmotor : %s\n", motor_str[actuator.motor]);

        printf("\tdirection : %s\n", direction_str[actuator.direction]);

        printf("\n");
        break;
    
    case STATE_RUNNING:
        printf("[LOG] current state: %s\n", state_str[current_state]);  

        actuator.pwm = cmd.speed;
        printf("\tpwm : %d\n", actuator.pwm);

        actuator.motor = MOTOR_ON;
        printf("\tmotor : %s\n", motor_str[actuator.motor]);

        actuator.direction = cmd.direction;
        printf("\tdirection : %s\n", direction_str[actuator.direction]);

        printf("\n");
        break;

    case STATE_ERROR:
        printf("[LOG] current state: %s\n", state_str[current_state]);  

        actuator.pwm = 0;
        printf("\tpwm : %d\n", actuator.pwm);

        actuator.motor = MOTOR_OFF;
        printf("\tmotor : %s\n", motor_str[actuator.motor]);

        printf("\tdirection : %s\n", direction_str[actuator.direction]);

        printf("\t오류 원인 확인중...\n");
        printf("\t오류 원인 확인\n");

        printf("\n");
        break;
    
    case STATE_RECOVERY:
        printf("[LOG] current state: %s\n", state_str[current_state]);  

        actuator.pwm = 0;
        printf("\tpwm : %d\n", actuator.pwm);

        actuator.motor = MOTOR_OFF;
        printf("\tmotor : %s\n", motor_str[actuator.motor]);

        printf("\tdirection : %s\n", direction_str[actuator.direction]);

        printf("\t오류 복구 시작\n");

        printf("\n");
        break;
    }
}

int processCommandMessage(char * rx_buf, Command * mcu_cmd, State * current_state)
{
    int heartbeat_timeout = 5;

    //MCU에서 CommandMessgae 파싱 후 mcu_cmd 구조체 초기화
    int result = parseCommandMessage(rx_buf, mcu_cmd);
    if(result == FAIL)
        return FAIL;

    //MCU가 Command 기준으로 Event 결정 및 StateMachine 상태 변환
    if (mcu_cmd->type == CMD_MOVE)
    {
        *current_state = getNextState(*current_state, EVENT_RUN);
    }
    else if (mcu_cmd->type == CMD_STOP)
    {
        *current_state = getNextState(*current_state, EVENT_STOP);
    }
    else    
        return FAIL;

    //MCU가 Actuator의 상태를 변환
    updateActuator(*current_state, *mcu_cmd);
    return SUCCESS;
}



