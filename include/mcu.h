#include "command.h"
#include "state_machine.h"
#include "actuator.h"

extern Actuator actuator;

int parseCommandMessage(char * buf, Command * cmd);
void updateActuator(State current_state, Command cmd);
