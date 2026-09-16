#include "../common/include/command.h"
#include "state_machine.h"
#include <time.h>

extern Actuator actuator;

int parseCommandMessage(char * buf, Command * cmd);
void updateActuator(State current_state, Command cmd);
int processCommandMessage(char * rx_buf, Command * mcu_cmd, State * current_state);

typedef struct 
{
    time_t last_heartbeat_time;
} Heartbeat;