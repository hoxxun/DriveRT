//STM32로 가져갈 것

#ifndef MCU_H
#define MCU_H

#include "../../common/include/command.h"
#include "state_machine.h"
#include "actuator.h"
#include <time.h>

#define SUCCESS 1
#define FAIL -1

extern Actuator actuator;

int parseCommandMessage(char * buf, Command * cmd);
void updateActuator(State current_state, Command cmd);
int processCommandMessage(char * rx_buf, Command * mcu_cmd, State * current_state);

typedef struct 
{
    time_t last_heartbeat_time;
} Heartbeat;
#endif