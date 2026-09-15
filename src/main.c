#include <stdio.h>
#include <string.h>
#include <stdlib.h> //atoi 
#include "../include/state_machine.h"
#include "../include/actuator.h"
#include "../include/ap.h"
#include "../include/mcu.h"

void send_receive_CommandMessage(char * tx_buf, char * rx_buf)
{
    printf("[AP] Command Message 송신\n");
    printf("Tx: %s\n", tx_buf);
    
    printf("\n");

    printf("[MCU] Command Message 수신\n");
    strcpy(rx_buf, tx_buf);
    printf("RX: %s\n", rx_buf);
}

int main(void)
{

    State current_state = STATE_STOP; //MCU
    Event current_event; //MCU

    Command ap_cmd;
    Command mcu_cmd;

    char tx_buf[50];
    char rx_buf[50];

    while(1)
    {
        //AP에서 명령어 입력
        int result = commandInput(&ap_cmd);

        if(result == -1) continue;

        //AP에서 CommandMessgae 생성
        buildCommandMessage(ap_cmd, tx_buf);

        //AP에서 CommandMessgae 보내고, MCU에서 받음
        send_receive_CommandMessage(tx_buf, rx_buf);

        //MCU에서 CommandMessgae 파싱
        parseCommandMessage(rx_buf, &mcu_cmd);

        //MCU가 Command 기준으로 Event 결정 및 StateMachine 상태 변환
        if (mcu_cmd.type == CMD_MOVE)
        {
            current_event = EVENT_RUN;
            current_state = getNextState(current_state, current_event);
        }
        else if (mcu_cmd.type == CMD_STOP)
        {
            current_event = EVENT_STOP;
            current_state = getNextState(current_state, current_event);
        }
        else    
            continue;

        //MCU가 Actuator의 상태를 변환
        updateActuator(current_state, mcu_cmd);
    }
    return 0;
}