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