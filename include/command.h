#ifndef COMMAND_H
#define COMMAND_H

extern const char * commandType_str[];
extern const char * direction_str[];
extern const char * state_str[];
extern const char * motor_str[];

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