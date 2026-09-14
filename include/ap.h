#ifndef AP_H
#define AP_H

#include "command.h"

int commandInput(Command * cmd);
void buildCommandMessage(Command cmd, char * buf);

#endif