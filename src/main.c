#include <stdio.h>
#include <string.h>
#include <stdlib.h> //atoi 
#include "../include/state_machine.h"
#include "../include/actuator.h"

Actuator actuator = {0, MOTOR_OFF, DIR_FORWARD};

typedef enum
{
    CMD_MOVE,
    CMD_STOP
} CommandType;

typedef struct 
{
    CommandType type;
    int speed;
    Direction direction;
} Command;

const char * commandType_str[] = {
    "MOVE",
    "STOP"
};

const char * state_str[] = {
    "STATE_STOP",
    "STATE_RUNNING",
    "STATE_ERROR",
    "STATE_RECOVERY"
};


const char * motor_str[] = {
    "MOTOR_OFF",
    "MOTOR_ON"
};

const char * direction_str[] = {
    "FORWARD",
    "BACKWARD"
};


void stateHandler(State current_state, Command cmd)
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

        break;
    
    case STATE_RUNNING:
        printf("[LOG] current state: %s\n", state_str[current_state]);  

        actuator.pwm = cmd.speed;
        printf("\tpwm : %d\n", actuator.pwm);

        actuator.motor = MOTOR_ON;
        printf("\tmotor : %s\n", motor_str[actuator.motor]);

        actuator.direction = cmd.direction;
        printf("\tdirection : %s\n", direction_str[actuator.direction]);
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
        break;
    
    case STATE_RECOVERY:
        printf("[LOG] current state: %s\n", state_str[current_state]);  

        actuator.pwm = 0;
        printf("\tpwm : %d\n", actuator.pwm);

        actuator.motor = MOTOR_OFF;
        printf("\tmotor : %s\n", motor_str[actuator.motor]);

        printf("\tdirection : %s\n", direction_str[actuator.direction]);

        printf("\t오류 복구 시작\n");

        break;
    }
}

int commandInput(Command * cmd)
{

    char command_buf[20];
    char direction_buf[20];
    printf("Command(MOVE/STOP): ");
    scanf("%s", command_buf);

    if(strcmp(command_buf, "MOVE") == 0)
    {
        cmd->type = CMD_MOVE;

        printf("Speed(0~100): ");
        scanf("%d", &cmd->speed);

        printf("Dirction(FORWARD/BACKWARD): ");
        scanf("%s", direction_buf);
            if(strcmp(direction_buf, "FORWARD") == 0)
            {   
                cmd->direction = DIR_FORWARD;
            }

            else if (strcmp(direction_buf, "BACKWARD") == 0)
            {
                cmd->direction = DIR_BACKWARD;
            }

            else 
            {
                printf("[ERROR] Invalid Direction\n");
            }
    
        return CMD_MOVE;
    }
    else if(strcmp(command_buf, "STOP") == 0)
    {
        cmd->type = CMD_STOP;
        
        cmd->speed = 0;

        printf("[LOG] Command: %s\n", command_buf);
        printf("[LOG] Speed: %d\n", cmd->speed);
        
        return CMD_STOP; 
    }
    else
    {
        printf("[ERROR] Invalid Command\n");

        return -1;
    } 
}

void buildCommandMessage(Command cmd, char * buf)
{
    if(cmd.type == CMD_MOVE)
    {
        snprintf(buf, 50, "%s,%d,%s",
        commandType_str[cmd.type],
        cmd.speed,
        direction_str[cmd.direction]); 
    }
    else if (cmd.type == CMD_STOP)
    {
        snprintf(buf,50,"%s",
                commandType_str[cmd.type]);
    }
}


void parseCommandMessage(char * buf, Command * cmd)
{
    char * cmdType = strtok(buf, ",");
    char * cmdSpeed = strtok(NULL, ",");
    char * cmdDirection = strtok(NULL, ",");

    if(strcmp(cmdType, "MOVE")==0)
    {
        cmd->type = CMD_MOVE;
        cmd->speed = atoi(cmdSpeed);
        if(strcmp(cmdDirection,"FORWARD")==0)
        {   
            cmd->direction = DIR_FORWARD;
        }
        else if(strcmp(cmdDirection,"BACKWARD")==0)
        {
            cmd->direction = DIR_BACKWARD;
        }
    }
    else if(strcmp(cmdType, "STOP")==0)
    {
        cmd->type = CMD_STOP;
        cmd->speed = 0;
    }
}


int main(void)
{

    State current_state = STATE_STOP;
    Event current_event;

    Command cmd;


    while(1)
    {
        int result = commandInput(&cmd);

        if (result == CMD_MOVE)
        {
            current_event = EVENT_RUN;
            current_state = getNextState(current_state, current_event);
        }
        else if (result == CMD_STOP)
        {
            current_event = EVENT_STOP;
            current_state = getNextState(current_state, current_event);
        }
        else    
            continue;

        stateHandler(current_state, cmd);


        char buf[50];

        buildCommandMessage(cmd, buf);
        printf("%s\n", buf);

        parseCommandMessage(buf,&cmd);
        printf("%s\n",commandType_str[cmd.type]);
        printf("%d\n", cmd.speed);
        printf("%s\n", direction_str[cmd.direction]);



    }



    return 0;
}