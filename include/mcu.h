#include "command.h"
#include "state_machine.h"
#include "actuator.h"
#include <time.h>

extern Actuator actuator;

int parseCommandMessage(char * buf, Command * cmd);
void updateActuator(State current_state, Command cmd);

typedef struct 
{
    time_t last_heartbeat_time;
} Heartbeat;

