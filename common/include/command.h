//이건 PC에도 남기고 STM32로도 가져갈 것. AP랑 MCU 둘 다 의존하는 헤더파일이니까

#ifndef COMMAND_H
#define COMMAND_H
typedef enum
{
    DIR_FORWARD,
    DIR_BACKWARD
} Direction;

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
#endif