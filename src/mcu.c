#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../include/command.h"
#include "../include/state_machine.h"
#include "../include/actuator.h"
#include "../include/mcu.h"
#include "../include/common.h"

Actuator actuator = {0, MOTOR_OFF, DIR_FORWARD};

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