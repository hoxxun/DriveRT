#include <stdio.h>
#include <string.h>
#include <stdlib.h> //atoi 
#include <time.h>
#include "../include/state_machine.h"
#include "../include/actuator.h"
#include "../include/ap.h"
#include "../include/mcu.h"
#include "../include/common.h"

void send_receive_CommandMessage(char * tx_buf, char * rx_buf)
{
    printf("[AP] Command Message 송신\n");
    printf("Tx: %s\n", tx_buf);
    
    printf("\n");

    printf("[MCU] Command Message 수신\n");
    strcpy(rx_buf, tx_buf);
    printf("RX: %s\n", rx_buf);
}

int processCommandMessage(char * rx_buf, Command * mcu_cmd, State * current_state)
{
    int heartbeat_timeout = 5;


    //MCU에서 CommandMessgae 파싱 후 mcu_cmd 구조체 초기화
    int result = parseCommandMessage(rx_buf, mcu_cmd);
    if(result == FAIL)
        return FAIL;

    //MCU가 Command 기준으로 Event 결정 및 StateMachine 상태 변환
    if (mcu_cmd->type == CMD_MOVE)
    {
        *current_state = getNextState(*current_state, EVENT_RUN);
    }
    else if (mcu_cmd->type == CMD_STOP)
    {
        *current_state = getNextState(*current_state, EVENT_STOP);
    }
    else    
        return FAIL;

    //MCU가 Actuator의 상태를 변환
    updateActuator(*current_state, *mcu_cmd);
    return SUCCESS;
}

int send_receive_heartbeat(char * heartbeat_tx_buf, char * heartbeat_rx_buf, Heartbeat * heartbeat)
{
    printf("[AP] Hearbeat 송신: %s\n", heartbeat_tx_buf);
    
    printf("\n");

    strcpy(heartbeat_rx_buf, heartbeat_tx_buf);
    if(strcmp(heartbeat_rx_buf, "HeartBeat") != 0)
    {
        return FAIL;
    }
    time_t t = time(NULL);
    heartbeat->last_heartbeat_time = t;
    printf("[MCU] Heartbeat 수신: %s\n", heartbeat_rx_buf);
    printf("%lu\n", heartbeat->last_heartbeat_time);
    printf("\n");


    return SUCCESS;
}


int main(void)
{
    State current_state = STATE_STOP; //MCU

    Command ap_cmd;
    Command mcu_cmd;

    char tx_buf[50];
    char rx_buf[50];

    Heartbeat heartbeat;
    char heartbeat_tx_buf[50] = {"HeartBeat"};
    char heartbeat_rx_buf[50];

    while(1)
    {   
        //HEARTBEAT
        int result1 = send_receive_heartbeat(heartbeat_tx_buf, heartbeat_rx_buf, &heartbeat);
        if(result1 == FAIL) continue;

        //AP에서 명령어 입력 후 ap_cmd 구조체 초기화
        int result2 = commandInput(&ap_cmd);
        if(result2 == FAIL) continue;

        //AP에서 ap_cmd 구조체를 보고 CommandMessgae 생성
        buildCommandMessage(ap_cmd, tx_buf);

        //AP에서 CommandMessgae 보내고, MCU에서 받음
        send_receive_CommandMessage(tx_buf, rx_buf);

        int result = processCommandMessage(rx_buf, &mcu_cmd, &current_state);

        if (result == FAIL) continue;
        
    }
    return 0;
}