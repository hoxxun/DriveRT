#include <stdio.h>
#include <string.h>
#include <stdlib.h> //atoi 
#include "../include/state_machine.h"
#include "../include/actuator.h"
#include "../include/ap.h"
#include "../include/mcu.h"

int main(void)
{

    State current_state = STATE_STOP; //MCU
    Event current_event; //MCU

    Command ap_cmd;
    Command mcu_cmd;

    char buf[50];


    while(1)
    {
        //AP에서 명령어 입력
        int result = commandInput(&ap_cmd);

        if(result == -1) continue;

        //AP에서 CommandMessgae 생성
        buildCommandMessage(ap_cmd, buf);
        printf("%s\n", buf);

        //MCU에서 CommandMessgae 파싱
        parseCommandMessage(buf, &mcu_cmd);

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