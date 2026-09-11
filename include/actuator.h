typedef enum 
{
    MOTOR_OFF, 
    MOTOR_ON
} Motor;

typedef struct 
{
    int pwm;
    Motor motor;
} Actuator;