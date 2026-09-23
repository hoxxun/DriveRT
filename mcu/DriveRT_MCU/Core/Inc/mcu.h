#ifndef MCU_H
#define MCU_H

#include "command.h"

#define SUCCESS 1
#define FAIL -1

int parseCommandMessage(char * buf, Command * cmd);

#endif