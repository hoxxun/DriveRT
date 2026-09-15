#include <stdio.h>
#include <string.h>
#include "../include/ap.h"

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
            printf("\n");
    
        return CMD_MOVE;
    }
    else if(strcmp(command_buf, "STOP") == 0)
    {
        cmd->type = CMD_STOP;
        
        cmd->speed = 0;

        printf("[LOG] Command: %s\n", command_buf);
        printf("[LOG] Speed: %d\n", cmd->speed);

        printf("\n");
        
        return CMD_STOP; 
    }
    else
    {
        printf("[ERROR] Invalid Command\n");
        printf("\n");
        return -1;
    } 
}

void buildCommandMessage(Command cmd, char * buf)
{
    if (cmd.type == CMD_MOVE)
    {
        printf("[AP] Command Message 생성\n");
        snprintf(buf, 50, "%s,%d,%s",
                commandType_str[cmd.type],
                cmd.speed,
                direction_str[cmd.direction]); 
    }
    else if (cmd.type == CMD_STOP)
    {
        printf("[AP] Command Message 생성\n");
        snprintf(buf,50,"%s",
                commandType_str[cmd.type]);
    }
}