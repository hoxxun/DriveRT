#include <stdio.h>
#include "../include/state_machine.h"

//문자열 배열은 pointer를 쓰는구나
//값 수정 안시킬거니까 const 붙임
const char * state_buf[] = {
    "STATE_STOP",
    "STATE_RUNNING",
    "STATE_ERROR",
    "STATE_RECOVERY"
};


void stateHandler(State current_state)
{
    switch (current_state)
    {
    case STATE_STOP:
        printf("[LOG] current state: %s\n", state_buf[current_state]);  
        printf("PWM을 0으로 설정\n");
        printf("모터 정지\n");
        break;
    
    case STATE_RUNNING:
        printf("[LOG] current state: %s\n", state_buf[current_state]);  
        printf("PWM ON\n"); 
        printf("모터 구동\n");
        break;

    case STATE_ERROR:
        printf("[LOG] current state: %s\n", state_buf[current_state]);  
        printf("PWM을 0으로 설정\n");
        printf("오류 원인 확인중...\n");
        printf("오류 원인 확인\n");
        break;
    
    case STATE_RECOVERY:
        printf("[LOG] current state: %s\n", state_buf[current_state]);  
        printf("오류 복구 시작\n");
        break;
    }
}


int main(void)
{

    /*
    EVENT_RUN, 
    EVENT_STOP, 
    EVENT_FAULT, 
    EVENT_RECOVER, 
    EVENT_RECOVERY_OK, 
    EVENT_RECOVERY_FAIL
    */

    State current_state = STATE_STOP;

    current_state = getNextState(current_state, EVENT_RUN);
    stateHandler(current_state);

    current_state = getNextState(current_state, EVENT_FAULT);
    stateHandler(current_state);

    current_state = getNextState(current_state, EVENT_RECOVER);
    stateHandler(current_state);

    current_state = getNextState(current_state, EVENT_RECOVERY_OK);
    stateHandler(current_state);

    return 0;
}