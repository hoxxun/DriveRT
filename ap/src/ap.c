#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <termios.h>

/*
ttyACM0
*/

int send_heartbeat();

int initSerialPort(void)
{
    int fd = open("/dev/ttyACM0", O_RDWR | O_NOCTTY);
    if(fd < 0)
    {
        printf("[AP LOG] STM32 통신 시리얼 장치 연결 실패\n");
        return -1;
    }

    struct termios config;
    if(tcgetattr(fd, &config) < 0)
    {
        printf("[AP LOG] STM32 통신 시리얼 장치 설정 정보 가져오기 실패\n");
        close(fd);
        return -1;
    }

    cfsetispeed(&config, B115200);
    cfsetospeed(&config, B115200);

    config.c_cflag &= ~CSIZE;   // 기존 데이터 비트 수 설정 지우기
    config.c_cflag |= CS8;      // 데이터 8비트 설정
    config.c_cflag &= ~PARENB;  // 패리티 사용 안 함
    config.c_cflag &= ~CSTOPB;  // 정지 비트 1개 사용

    config.c_cflag |= (CREAD | CLOCAL);
    config.c_cflag &= ~CRTSCTS;
    config.c_iflag &= ~(IXON | IXOFF | IXANY);

    cfmakeraw(&config);

    if(tcsetattr(fd, TCSANOW, &config) < 0)
    {
        printf("[AP LOG] STM32 통신 시리얼 장치 설정 정보 업데이트 실패\n");
        close(fd);
        return -1;
    }

    return fd;
}

void sendMessage(HANDLE handler, char * message)
{
    DWORD bytesWritten = 0;
    BOOL result = WriteFile(handler, message, (DWORD)strlen(message), &bytesWritten, NULL);

    if ((result != 0) && (bytesWritten == (DWORD)strlen(message)))
    {
        WriteFile(handler, "\r", 1, &bytesWritten, NULL);
    }
}

void sendHeartbeat(HANDLE handler)
{
    sendMessage(handler, "HEARTBEAT");   
}
/*

static const char * commandType_str[] = {
    "MOVE",
    "STOP"
};

static const char * direction_str[] = {
    "FORWARD",
    "BACKWARD"
};


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

*/
