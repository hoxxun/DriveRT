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

int main(void)
{
    State current_state = STATE_STOP;
    Event current_event = EVENT_FAULT;

    printf("[LOG] current state: %s\n", state_buf[current_state]);

    current_state = getNextState(current_state, current_event);
    
    printf("[LOG] current state: %s\n", state_buf[current_state]);

    return 0;
}