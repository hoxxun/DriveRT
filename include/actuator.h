typedef enum 
{
    MOTOR_OFF, 
    MOTOR_ON
} Motor;

typedef enum
{
    DIR_FORWARD,
    DIR_BACKWARD
} Direction;

typedef struct 
{
    int pwm;
    Motor motor;
    Direction direction;
} Actuator;