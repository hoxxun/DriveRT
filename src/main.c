#include <stdio.h>
#include <string.h>
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
    "DIR_FORWARD",
    "DIR_BACKWARD"
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


int main(void)
{

    State current_state = STATE_STOP;
    Event current_event;

    Command cmd;

    char command_buf[20];
    char direction_buf[20];

    while(1)
    {
        printf("Command(MOVE/STOP): ");
        scanf("%s", command_buf);

        if(strcmp(command_buf, "MOVE") == 0)
        {
            cmd.type = CMD_MOVE;

            printf("Speed(0~100): ");
            scanf("%d", &cmd.speed);

            printf("Dirction(FORWARD/BACKWARD): ");
            scanf("%s", direction_buf);
            if(strcmp(direction_buf, "FORWARD") == 0)
            {   
                cmd.direction = DIR_FORWARD;
            }

            else if (strcmp(direction_buf, "BACKWARD") == 0)
            {
                cmd.direction = DIR_BACKWARD;
            }

            else 
            {
                printf("[ERROR] Invalid Direction\n");
                continue;
            }

            current_event = EVENT_RUN;
            current_state = getNextState(current_state, current_event);

            printf("[LOG] Command: %s\n", command_buf);
            printf("[LOG] Speed: %d\n", cmd.speed);
            printf("[LOG] direction: %s\n", direction_buf);

            stateHandler(current_state, cmd);
        }

        else if(strcmp(command_buf, "STOP") == 0)
        {
            cmd.type = CMD_STOP;

            current_event = EVENT_STOP;
            current_state = getNextState(current_state, current_event);

            cmd.speed = 0;  

            printf("[LOG] Command: %s\n", command_buf);
            printf("[LOG] Speed: %d\n", cmd.speed);

            stateHandler(current_state, cmd);
        }

        else 
            printf("[ERROR] Invalid Command\n");
        }

    return 0;
}