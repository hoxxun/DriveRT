#include <stdio.h>
#include <string.h>
#include <windows.h>

/* Command */
#include "../../common/include/command.h"

//PC에 남길 것

int send_heartbeat();

static const char * commandType_str[] = {
    "MOVE",
    "STOP"
};

static const char * direction_str[] = {
    "FORWARD",
    "BACKWARD"
};

void sendMessage(char * message)
{
    HANDLE messageHandler =  CreateFileA("COM3", GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);
    if(messageHandler == INVALID_HANDLE_VALUE)
    {
        printf("[AP LOG] 포트 연결 실패\n");
        return;
    }

    DCB config = {0};
    config.DCBlength = sizeof(config);

    if (GetCommState(messageHandler, &config) == 0)
    {
        printf("[AP LOG] 설정 정보 가져오기 실패\n");
        CloseHandle(messageHandler);
        return;
    }

    config.BaudRate = CBR_115200;
    config.ByteSize = 8;
    config.Parity = NOPARITY;
    config.StopBits = ONESTOPBIT;

    config.fOutxCtsFlow = FALSE;
    config.fOutxDsrFlow = FALSE;
    config.fOutX = FALSE;
    config.fInX = FALSE;

    if (SetCommState(messageHandler, &config) == 0)
    {
        printf("[AP LOG] 설정 정보 업데이트 실패\n");
        CloseHandle(messageHandler);
        return;
    }

    DWORD bytesWritten = 0;
    BOOL result = WriteFile(messageHandler, message, (DWORD)strlen(message), &bytesWritten, NULL);

    if ((result != 0) && (bytesWritten == (DWORD)strlen(message)))
    {
        WriteFile(messageHandler, "\r", 1, &bytesWritten, NULL);
    }

    CloseHandle(messageHandler);
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