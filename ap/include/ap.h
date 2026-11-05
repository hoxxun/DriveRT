//이건 PC에 남길 것. AP에서 쓰이니까

#ifndef AP_H
#define AP_H

int initSerialPort(void);
void sendMessage(int fd, char * message);
void sendHeartbeat(int fd);

/*
int commandInput(Command * cmd);
void buildCommandMessage(Command cmd, char * buf);
*/

#endif